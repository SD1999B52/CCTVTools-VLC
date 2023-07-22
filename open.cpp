#include <iostream>
#include <windows.h>
#include <math.h>
#include <shlwapi.h>

//в параметры компилятора 
//-finput-charset=CP1251 -fexec-charset=UTF-8

//в параметры линкера 
//-lshlwapi

#define VLC_WIDTH                                            500
#define VLC_HEIGHT                                           300

#define VLC_APP                                       L"vlc.exe"

#define VLC_PARAMETERS   L"--no-qt-video-autoresize --autoscale\
 --no-playlist-autostart --no-start-paused"

#define VLC_PLAYLIST_OPEN   L"<?xml version=\"1.0\" encoding=\"\
UTF-8\"?>\n<playlist xmlns=\"http://xspf.org/ns/0/\" xmlns:vlc=\
\"http://www.videolan.org/vlc/playlist/ns/0/\" version=\"1\">\n\
\t<title>Ïëåéëèñò</title>\n\t<trackList>\n"

#define VLC_PLAYLIST_CLOSE      L"\t</trackList>\n</playlist>\n"

#define VLC_PLAYLIST_TRACK_OPEN   L"\t\t<track>\n\t\t\t<locatio\
n>file:///"

#define VLC_PLAYLIST_TRACK_CLOSE    L"</location>\n\t\t</track>\
\n"

#define VLC_QT_INTERFACE            L"vlc\\vlc-qt-interface.ini"

#define REPARSE_POINT               FILE_ATTRIBUTE_REPARSE_POINT
#define DIRECTORY                       FILE_ATTRIBUTE_DIRECTORY

#define PLAYLIST_BUFFER                                L"buffer"
#define PLAYLIST_EXTENSION                              L".xspf"

#define RRF_SUBKEY_WOW6464KEY                         0x00010000
#define RRF_SUBKEY_WOW6432KEY                         0x00020000

#define VLC_REGISTRY_KEY              L"SOFTWARE\\VideoLAN\\VLC"
#define VLC_REGISTRY_PARAMETER                     L"InstallDir"

const int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);

const int COLUMNS_NUMBER = floor((double)SCREEN_WIDTH 
/ (double)VLC_WIDTH);
const int ROWS_NUMBER = floor((double)SCREEN_HEIGHT 
/ (double)VLC_HEIGHT);

const int VLC_NUMBER = COLUMNS_NUMBER * ROWS_NUMBER;

const WCHAR *APPDATA = _wgetenv(L"APPDATA");
const WCHAR *VLC_HOME = _wgetenv(L"VLC_HOME");

using namespace std;

//создание/нет папки буфера
void buffer() {
	if (!PathFileExistsW(PLAYLIST_BUFFER)) {
		CreateDirectoryW(PLAYLIST_BUFFER, NULL);
	}
}

//сброс настроек интерфейса VLC
void reset() {
	wstring pBuffer(APPDATA);
	pBuffer.append(L"\\");
	pBuffer.append(VLC_QT_INTERFACE);
	
	if (PathFileExistsW(pBuffer.data())) {
		DeleteFileW(pBuffer.data());
	}
}

//получить количество файлов в папке
long files(const WCHAR *fPath) {
	wstring pBuffer(fPath);
	pBuffer.append(L"\\*");
	
	long nFiles = 0L;
	
	WIN32_FIND_DATAW dFile;
	HANDLE hFile = FindFirstFileW(pBuffer.data(), &dFile);
	
	if (hFile != INVALID_HANDLE_VALUE) {
		
		do {
			if ((dFile.dwFileAttributes != REPARSE_POINT) 
			& (!(dFile.dwFileAttributes & DIRECTORY))) {
				
				nFiles++;
			}
			
		} while (FindNextFileW(hFile, &dFile) != 0);
		
		FindClose(hFile);
	}
	
	return nFiles;
}

//запись текста в файл
void write(const WCHAR *wText, const WCHAR *fPath) {
	HANDLE fHandle = CreateFileW(fPath, GENERIC_WRITE, 0, NULL, 
	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	SIZE_T sText = wcslen(wText) * sizeof(WCHAR);
	
	WriteFile(fHandle, wText, sText, NULL, NULL);
	CloseHandle(fHandle);
}

//запуск программы
void start(const WCHAR *pPath, const WCHAR *pParams) {
	ShellExecuteW(NULL, L"open", pPath, pParams, NULL, 
	SW_RESTORE);
}

//замена символов в строке
void replace(WCHAR *rText, WCHAR rWchar, WCHAR aWchar) {
	SIZE_T tLength = wcslen(rText);
	
	for (SIZE_T i = 0; i < tLength; i++) {
		if (rText[i] == rWchar) {
			rText[i] = aWchar;
		}
	}
}

void open(const WCHAR *fVlc, const WCHAR *fVideo) {
	SIZE_T fLength = wcslen(fVideo);
	
	const WCHAR *wPath = fVideo;
	WCHAR *uPath = new WCHAR[fLength + 1];
	
	wcsncpy(uPath, fVideo, fLength + 1);
	replace(uPath, L'\\', L'/');
	
	//добавляем для получения всех файлов в папке
	wstring aVideo(wPath);
	aVideo.append(L"\\*");
	
	//добавляем кавычки для командной строки 
	wstring qVlc(L"\"");
	qVlc.append(fVlc);
	qVlc.append(L"\\");
	qVlc.append(VLC_APP);
	qVlc.append(L"\"");
	
	//количество файлов в папке
	long nFiles = files(wPath);
	
	//расчет количества видео на одну форму VLC
	long nVideos = ceil((double)nFiles / (double)VLC_NUMBER);
	
	WIN32_FIND_DATAW dFile;
	HANDLE hFile = FindFirstFileW(aVideo.data(), &dFile);
	
	if (hFile != INVALID_HANDLE_VALUE) {
		
		long cVideos = 0L;
		long cFiles = 0L;
		long cVlc = 0L;
		
		wstring pVlc(VLC_PLAYLIST_OPEN);
		
		do {
			if ((dFile.dwFileAttributes != REPARSE_POINT) 
			& (!(dFile.dwFileAttributes & DIRECTORY))) {
				
				pVlc.append(VLC_PLAYLIST_TRACK_OPEN);
				pVlc.append(uPath);
				pVlc.append(L"/");
				pVlc.append(dFile.cFileName);
				pVlc.append(VLC_PLAYLIST_TRACK_CLOSE);
				
				cVideos++;
				cFiles++;
				
				if ((cVideos == nVideos) | (cFiles == nFiles)) {
					
					pVlc.append(VLC_PLAYLIST_CLOSE);
					
					//путь сохранения плейлиста
					wstring pPlaylist(PLAYLIST_BUFFER);
					pPlaylist.append(L"\\");
					pPlaylist.append(to_wstring(cVlc));
					pPlaylist.append(PLAYLIST_EXTENSION);
					
					write(pVlc.data(), pPlaylist.data());
					
					//добавляем кавычки для командной строки
					wstring qPlaylist(VLC_PARAMETERS);
					qPlaylist.append(L" \"");
					qPlaylist.append(pPlaylist.data());
					qPlaylist.append(L"\"");
					
					start(qVlc.data(), qPlaylist.data());
					
					pVlc.clear();
					pVlc.append(VLC_PLAYLIST_OPEN);
					
					cVideos = 0L;
					cVlc++;
				}
			}
			
		} while (FindNextFileW(hFile, &dFile) != 0);
		
		FindClose(hFile);
	}
	
	delete [] uPath;
}

int main() {
	int argc;
	WCHAR **argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	
	buffer();
	reset();
	
	if (argc == 2) {
		
		SIZE_T lValue = MAX_PATH;
		WCHAR *tValue = new WCHAR[MAX_PATH];
		
		//для 64 bit Windows 
		LSTATUS s64 = RegGetValueW(
			HKEY_LOCAL_MACHINE, 
			VLC_REGISTRY_KEY, 
			VLC_REGISTRY_PARAMETER, 
			RRF_RT_REG_SZ | RRF_SUBKEY_WOW6464KEY, 
			NULL, 
			tValue, 
			&lValue
		);
		
		//для 32 bit Windows 
		LSTATUS s32 = RegGetValueW(
			HKEY_LOCAL_MACHINE, 
			VLC_REGISTRY_KEY, 
			VLC_REGISTRY_PARAMETER, 
			RRF_RT_REG_SZ | RRF_SUBKEY_WOW6432KEY, 
			NULL, 
			tValue, 
			&lValue
		);
		
		if (VLC_HOME != NULL) {
			wcsncpy(tValue, VLC_HOME, MAX_PATH);
		}
		
		open(tValue, argv[1]);
		
		delete [] tValue;
	}
	
	if (argc == 3) {
		open(argv[1], argv[2]);
	}
	
	return 0;
}
