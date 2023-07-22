#include <iostream>
#include <windows.h>

//в параметры компил€тора
//-finput-charset=CP1251 -fexec-charset=UTF-8

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	
	wcout << L"help - вывод списка команд;" << endl;
	wcout << L"close - зыкрыть все экземпл€ры VLC;" << 
	endl;
	wcout << L"current - вывод имен файлов проигрываемых\
 всеми экземпл€рами VLC (текущие);" << endl;
	wcout << L"hide - свернуть все экземпл€ры VLC;" << 
	endl;
	wcout << L"open <путь к папке с VLC> <путь к папке\
 с видео> - открыть видеофайлы в нескольких экземпл€рах\
 VLC" << endl;
	wcout << L"open <путь к папке с видео> - то же самое\
 только дл€ получени€ пути к папке с VLC используетс€\
 запись в реестре (при установке инсталл€тором), либо\
 переменна€ среды VLC_HOME (создать самому);" << endl;
	wcout << L"pause - приостановить проигрывание во\
 всех экземпл€рах VLC;" << endl;
	wcout << L"place - расположить экземпл€ры VLC по\
 пор€дку а также подогнать их размер форм;" << endl;
	wcout << L"play - продолжить воспроизведение\
 видеофайлов во всех экземпл€рах VLC;" << endl;
	wcout << L"show - развернуть все экземпл€ры VLC." << 
	endl;
	
	return 0;
}
