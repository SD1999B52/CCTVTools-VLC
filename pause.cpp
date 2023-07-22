#include <windows.h>

//в параметры компилятора 
//-finput-charset=CP1251 -fexec-charset=UTF-8

#define CLASS_NAME_MAX_LENGTH                          256

#define CLASS_NAME                       L"Qt5QWindowIcon"
#define WINDOW_TEXT                                 L"VLC"

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	int nLength = CLASS_NAME_MAX_LENGTH;
	int tLength = GetWindowTextLength(hwnd);
	
	WCHAR *cName = new WCHAR[nLength + 1];
	WCHAR *wText = new WCHAR[tLength + 1];
	
	GetClassNameW(hwnd, cName, nLength + 1);
	GetWindowTextW(hwnd, wText, tLength + 1);
	
	bool nFound = wcsstr(cName, CLASS_NAME);
	bool tFound = wcsstr(wText, WINDOW_TEXT);
	
	if ((nFound) & (tFound)) {
		
		SendMessage(hwnd, WM_APPCOMMAND, 0, 
		MAKELPARAM(0, APPCOMMAND_MEDIA_PAUSE));
	}
	
	delete [] cName;
	delete [] wText;
	
	return true;
}

int main() {
	EnumWindows(&EnumWindowsProc, 0);
	
	return 0;
}
