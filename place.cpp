#include <windows.h>
#include <math.h>
//#include <dwmapi.h>

//в параметры компилятора 
//-finput-charset=CP1251 -fexec-charset=UTF-8

//в параметры линкера
//-lshlwapi -ldwmapi

#define VLC_WIDTH                                     500
#define VLC_HEIGHT                                    300

#define CLASS_NAME_MAX_LENGTH                         256

#define CLASS_NAME                      L"Qt5QWindowIcon"
#define WINDOW_TEXT                                L"VLC"

//#define SHADOW                DWMWA_EXTENDED_FRAME_BOUNDS

const int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);

const int COLUMNS_NUMBER = floor((double)SCREEN_WIDTH 
/ (double)VLC_WIDTH);
const int ROWS_NUMBER = floor((double)SCREEN_HEIGHT 
/ (double)VLC_HEIGHT);

const int VLC_NUMBER = COLUMNS_NUMBER * ROWS_NUMBER;

int cNum = 0;
int rNum = 0;

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
		/*
		RECT sPos;
		RECT wPos;
		
		GetWindowRect(hwnd, &wPos);
		DwmGetWindowAttribute(hwnd, SHADOW, &sPos, 
		sizeof(RECT));
		
		int lWidth = wPos.left - sPos.left;
		int rWidth = wPos.right - sPos.right;
		int tWidth = wPos.top - sPos.top;
		int bWidth = wPos.bottom - sPos.bottom;
		
		int xPos = cNum * VLC_WIDTH + lWidth * 
		(cNum + 1) - rWidth * cNum;
		int yPos = rNum * VLC_HEIGHT + tWidth * 
		(rNum + 1) - bWidth * rNum;*/
		/*
		LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
		lStyle &= ~(WS_BORDER | WS_THICKFRAME);
		SetWindowLong(hwnd, GWL_STYLE, lStyle);
		*/
		int xPos = cNum * VLC_WIDTH;
		int yPos = rNum * VLC_HEIGHT;
		
		SetWindowPos(hwnd, HWND_TOP, xPos, yPos, 
		VLC_WIDTH, VLC_HEIGHT, SWP_SHOWWINDOW);
		
		if (cNum < COLUMNS_NUMBER - 1) {
			cNum++;
		} else {
			rNum++;
			cNum = 0;
		}
	}
	
	delete [] cName;
	delete [] wText;
	
	return true;
}

int main() {
	EnumWindows(&EnumWindowsProc, 0);
	
	return 0;
}
