#include <iostream>
#include <windows.h>

//� ��������� �����������
//-finput-charset=CP1251 -fexec-charset=UTF-8

#define VLC_WIDTH                                     500
#define VLC_HEIGHT                                    300

#define CLASS_NAME_MAX_LENGTH                         256

#define CLASS_NAME                      L"Qt5QWindowIcon"
#define WINDOW_TEXT                                L"VLC"

using namespace std;

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
		
		//�������� ��������� �� ��������� ������ - �
		//������
		WCHAR *bText = wcsrchr(wText, L'-');
		
		if (bText != NULL) {
			//������� ������ ���������� ������� � �� 
			//�������� ��� ������ ����� �������� -
			int bLength = bText - wText - 1;
			
			for (int i = 0; i < bLength; i++) {
				wcout << wText[i];
			}
			
			wcout << endl;
		}
	}
	
	delete [] cName;
	delete [] wText;
	
	return true;
}

int main() {
	setlocale(LC_ALL, "Russian");
	
	EnumWindows(&EnumWindowsProc, 0);
	
	return 0;
}
