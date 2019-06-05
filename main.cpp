#include <iostream>
#include <Windows.h>
#include "Database.h"
using namespace std;
const int CODE = 12345;

void showASCII();

int main(int argc, char const *argv[])
{
	system("title 图书馆管理程序 by C++");
	system("mode con cols=75 lines=38");
	int cmd, code;
	Database library;
	cout << "请选择您的身份: 1: 管理员用户\t2: 普通读者" << endl;
	while (true)
	{
		cin >> cmd;
		if (cmd == 1 || cmd == 2) break;
		else cout << "非法输入!" << endl;
	}
	
	if (cmd == 1)
	{
		while (true)
		{
			cout << "请输入管理员密码: " << endl;
			cin >> code;
			if (code == CODE) break;
			else cout << "密码错误!请输入正确的密码!" << endl;
		}
		system("cls");
		showASCII();
		MessageBox(NULL, "已经添加了3个读者和3本书", "系统提示", MB_OK);
		library.Pre();
		system("cls");
		while(true) 
		{
			try {library.StartWork();}
			catch (const char *st) 
			{
				system("title 图书馆管理程序-管理员-错误");
				system("color 4f");
				cerr << "错误!" << ends << st << endl;
				system("pause");
			}
		}
	}
	else
	{
		system("cls");
		showASCII();
		MessageBox(NULL, "欢迎使用图书馆管理系统", "系统提示", MB_OK);
		library.Pre();
		system("cls");
		while(true) 
		{
			try {library.ReaderUI();}
			catch (const char *st) 
			{
				system("title 图书馆管理程序-读者-错误");
				system("color 4f");
				cerr << "错误!" << ends << st << endl;
				system("pause");
			}
		}
	}
	
	return 0;
}

void showASCII()
{
	cout << " /$$       /$$ /$$                                             " << endl;
    cout << "| $$      |__/| $$                                             " << endl;
    cout << "| $$       /$$| $$$$$$$   /$$$$$$  /$$$$$$   /$$$$$$  /$$   /$$" << endl;
    cout << "| $$      | $$| $$__  $$ /$$__  $$|____  $$ /$$__  $$| $$  | $$" << endl;
    cout << "| $$      | $$| $$  \\ $$| $$  \\__/ /$$$$$$$| $$  \\__/| $$  | $$" << endl;
    cout << "| $$      | $$| $$  | $$| $$      /$$__  $$| $$      | $$  | $$" << endl;
    cout << "| $$$$$$$$| $$| $$$$$$$/| $$     |  $$$$$$$| $$      |  $$$$$$$" << endl;
    cout << "|________/|__/|_______/ |__/      \\_______/|__/       \\____  $$" << endl;
    cout << "                                                      /$$  | $$" << endl;
    cout << "                                                     |  $$$$$$/" << endl;
    cout << "                                                      \\______/ " << endl;
	cout << "$$\\      $$\\                                                             " << endl;
    cout << "$$$\\    $$$ |                                                            " << endl;
    cout << "$$$$\\  $$$$ | $$$$$$\\  $$$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$\\  " << endl;
    cout << "$$\\$$\\$$ $$ | \\____$$\\ $$  __$$\\  \\____$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ " << endl;
    cout << "$$ \\$$$  $$ | $$$$$$$ |$$ |  $$ | $$$$$$$ |$$ /  $$ |$$$$$$$$ |$$ |  \\__|" << endl;
    cout << "$$ |\\$  /$$ |$$  __$$ |$$ |  $$ |$$  __$$ |$$ |  $$ |$$   ____|$$ |      " << endl;
    cout << "$$ | \\_/ $$ |\\$$$$$$$ |$$ |  $$ |\\$$$$$$$ |\\$$$$$$$ |\\$$$$$$$\\ $$ |      " << endl;
    cout << "\\__|     \\__| \\_______|\\__|  \\__| \\_______| \\____$$ | \\_______|\\__|      " << endl;
    cout << "                                           $$\\   $$ |                    " << endl;
    cout << "                                           \\$$$$$$  |                    " << endl;
    cout << "                                            \\______/                     " << endl;
	cout << endl;
	cout << "$$$$$$$\\                   $$$$$$\\                   " << endl;
	cout << "$$  __$$\\                 $$  __$$\\   $$\\       $$\\    " << endl;
	cout << "$$ |  $$ |$$\\   $$\\       $$ /  \\__|  $$ |      $$ |   " << endl;
	cout << "$$$$$$$\\ |$$ |  $$ |      $$ |     $$$$$$$$\\ $$$$$$$$\\ " << endl;
	cout << "$$  __$$\\ $$ |  $$ |      $$ |     \\__$$  __|\\__$$  __|" << endl;
	cout << "$$ |  $$ |$$ |  $$ |      $$ |  $$\\   $$ |      $$ |   " << endl;
	cout << "$$$$$$$  |\\$$$$$$$ |      \\$$$$$$  |  \\__|      \\__|   " << endl;
	cout << "\\_______/  \\____$$ |       \\______/                  " << endl;
	cout << "          $$\\   $$ |                                 " << endl;
	cout << "          \\$$$$$$  |                                 " << endl;
	cout << "           \\______/                                  " << endl << endl;
	cout << "Version 1.0 Beta 1" << endl;
}
