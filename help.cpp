#include <iostream>
#include <windows.h>

//� ��������� �����������
//-finput-charset=CP1251 -fexec-charset=UTF-8

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	
	wcout << L"help - ����� ������ ������;" << endl;
	wcout << L"close - ������� ��� ���������� VLC;" << 
	endl;
	wcout << L"current - ����� ���� ������ �������������\
 ����� ������������ VLC (�������);" << endl;
	wcout << L"hide - �������� ��� ���������� VLC;" << 
	endl;
	wcout << L"open <���� � ����� � VLC> <���� � �����\
 � �����> - ������� ���������� � ���������� �����������\
 VLC" << endl;
	wcout << L"open <���� � ����� � �����> - �� �� �����\
 ������ ��� ��������� ���� � ����� � VLC ������������\
 ������ � ������� (��� ��������� �������������), ����\
 ���������� ����� VLC_HOME (������� ������);" << endl;
	wcout << L"pause - ������������� ������������ ��\
 ���� ����������� VLC;" << endl;
	wcout << L"place - ����������� ���������� VLC ��\
 ������� � ����� ��������� �� ������ ����;" << endl;
	wcout << L"play - ���������� ���������������\
 ����������� �� ���� ����������� VLC;" << endl;
	wcout << L"show - ���������� ��� ���������� VLC." << 
	endl;
	
	return 0;
}
