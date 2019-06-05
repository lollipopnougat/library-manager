#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int CODE = 12345;

/*
Book.h
#ifndef BOOK_H
#define BOOK_H
#include <string>
*/
class Book
{
public:
	Book(std::string &name, int id): name(name), id(id) {}
	Book() {}
	~Book() {}
	std::string GetName() {return name;}
	int GetId() {return id;}
	void OnShelf(bool fl) {onshelf = fl;}
	bool IsOnShelf() {return onshelf;}
	bool operator == (const Book &bk) {if (bk.name == this->name && bk.id == this->id) return true; else return false;}
private:
	std::string name;
	int id;
	bool onshelf = true;
};
//#endif

/*
Reader.h
#ifndef READER_H
#define READER_H
#include <string>
#include <vector>
#include "Book.h"
*/
class Reader
{
public:
	Reader(std::string &name, int id): name(name), id(id) {}
	Reader() {}
	~Reader() {}
	std::string GetName() {return name;}
	int GetId() {return id;}
	int GetBookNum() {return holdbook.size();}
	int GetBookId(int no);
	std::string GetBookName(int no);
	void BorrowBook(Book &bk);
	void RestoreBook(Book &bk);
	void ShowDetail();
private:
	std::string name;
	int id;
	std::vector<Book> holdbook;
};
//#endif

/*
Database.h
#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include <map>
#include "Book.h"
#include "Reader.h"
*/
class Database
{
public:
	Database() {}
	~Database() {}
	void StartWork();
	void ReaderUI();
	void Pre();
private:
	int BorrowNum = 0;
	std::map<int, Book> bookstore;
	std::map<int, Reader> readerlist;
	void ReaderManage();
	void BookManage();
	void BorrowAndRestore();
	void CheckBook(int id);
	void CheckReader(int id);
	void AddReader(Reader &rd);
	void AddBook(Book &bk);
	void DeleteReader(int id);
	void DeleteBook(int id);
	void BorrowBook(int RDid, int BKid);
	void RestoreBook(int RDid, int BKid);
	void ShowDataStatistics();
	void ListAllReaders();
	void ListAllBooks();
};
//#endif

/*
Reader.cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Book.h"
#include "Reader.h"

using namespace std;
*/
int Reader::GetBookId(int no)
{
	if (no > holdbook.size()) throw "参数非法";
	return holdbook.at(no).GetId();
}

string Reader::GetBookName(int no)
{
	if (no > holdbook.size()) throw "参数非法";
	return holdbook.at(no).GetName();
}

void Reader::BorrowBook(Book &bk)
{
	holdbook.push_back(bk);
	cout << "恭喜，书成功借到！" << endl << endl;
}

void Reader::RestoreBook(Book &bk)
{
	auto itt = find(holdbook.begin(), holdbook.end(), bk);
	holdbook.erase(itt);
}

void Reader::ShowDetail()
{
	cout << "姓名: " << name << ends << "读者号: " << id << endl;
	cout << "借书数量： " << holdbook.size() << endl;
	cout << "所借书: ";
	for (auto it = holdbook.begin(); it != holdbook.end(); it++)
		cout << "书名：" << it->GetName() << ends << "图书号: " << it->GetId() << endl;
	cout << endl << endl;
}

/*
Database.cpp
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Book.h"
#include "Reader.h"
#include "Database.h"

using namespace std;
*/
void Database::CheckBook(int id)
{
	if (bookstore.find(id) == bookstore.end()) throw "id非法!";
	else if (bookstore[id].IsOnShelf()) cout << bookstore[id].GetName() << " 在架." << endl << endl;
	else cout << bookstore[id].GetName() << " 已借出." << endl << endl;
}

void Database::CheckReader(int id)
{
	if (readerlist.find(id) == readerlist.end()) throw "id非法!";
	else readerlist[id].ShowDetail();
}

void Database::AddReader(Reader &rd)
{
	if (readerlist.find(rd.GetId()) != readerlist.end()) throw "该用户ID已存在!";
	readerlist.insert(make_pair(rd.GetId(), rd));
	cout << "读者添加成功." << endl;
}

void Database::AddBook(Book &bk)
{
	if (bookstore.find(bk.GetId()) != bookstore.end()) throw "该图书号已存在!";
	bookstore.insert(make_pair(bk.GetId(), bk));
	cout << "图书添加成功." << endl;
}

void Database::DeleteReader(int id)
{
	if (readerlist.find(id) == readerlist.end()) throw "查无此读者!";
	else
	{
		if (readerlist[id].GetBookNum() != 0)
		{
			cout << "此读者仍有书未还! 继续删除会把所借书从书库删除，确定删除该读者？(Y/N): ";
			char tmp;
			cin >> tmp;
			if (tmp == 'N' || tmp == 'n') cout << "已取消删除." << endl;
			else if (tmp == 'Y' || tmp == 'y')
			{
				cout << "已删除读者: " << readerlist[id].GetName() << endl << endl;
				for (int i = 0; i < readerlist[id].GetBookNum(); i++)
					DeleteBook(readerlist[id].GetBookId(i));
				readerlist.erase(id);
			}
			else throw "非法输入!";
		}
		else
		{
			cout << "已删除读者: " << readerlist[id].GetName() << endl << endl;
			readerlist.erase(id);
		}
	}
}

void Database::DeleteBook(int id)
{
	if (bookstore.find(id) == bookstore.end()) throw "查无此图书!";
	else
	{
		cout << "已删除图书: " << bookstore[id].GetName() << endl << endl;
		bookstore.erase(id);
	}
}

void Database::BorrowBook(int RDid, int BKid)
{
	if (readerlist.find(RDid) == readerlist.end()) throw "查无此读者!";
	else if (bookstore.find(BKid) == bookstore.end()) throw "查无此图书!";
	else if (readerlist[RDid].GetBookNum() == 3) throw "此读者借书已满3本!";
	bookstore[BKid].OnShelf(false);
	readerlist[RDid].BorrowBook(bookstore[BKid]);
	BorrowNum++;
	cout << "借阅成功." << endl;
}

void Database::RestoreBook(int RDid, int BKid)
{
	if (readerlist.find(RDid) == readerlist.end()) throw "查无此读者!";
	else if (bookstore.find(BKid) == bookstore.end()) throw "查无此书或该图书不能归还!";
	else if (readerlist[RDid].GetBookNum() == 0) throw "此读者未借书!";
	bookstore[BKid].OnShelf(true);
	readerlist[RDid].RestoreBook(bookstore[BKid]);
	BorrowNum--;
	cout << "还书成功." << endl;
}

void Database::ShowDataStatistics()
{
	cout << "馆藏图书量: " << bookstore.size() << endl;
	cout << "可借图书量: " << bookstore.size() - BorrowNum << endl;
	cout << "注册读者数: " << readerlist.size() << endl;
	cout << endl;
}

void Database::ListAllReaders()
{
	if (readerlist.size() == 0) cout << "没有读者记录" << endl;
	for (auto it = readerlist.begin(); it != readerlist.end(); it++)
		cout << "姓名: " << it->second.GetName() << ends << "ID: " << it->first << endl;
}

void Database::ListAllBooks()
{
	if (bookstore.size() == 0) cout << "没有图书记录" << endl;
	for (auto it = bookstore.begin(); it != bookstore.end(); it++)
	{
		cout << "书名: " << it->second.GetName() << ends << "书号: " << it->first;
		if (it->second.IsOnShelf()) cout << ends << "在架." << endl;
		else cout << ends << "已借出." << endl;
	}
}

void Database::ReaderManage()
{
	system("color 8f");
	system("title 图书馆管理程序-管理员-读者管理");
	while (true)
	{
		cout << "请选择: " << endl;
		cout << ends << "当前读者数量: " << readerlist.size() << endl;
		cout << ends << ends << "1: 添加读者" << endl;
		cout << ends << ends << "2: 删除读者" << endl;
		cout << ends << ends << "3: 列出所有读者" << endl;
		cout << ends << ends << "4: 根据ID查询读者借书情况" << endl;
		cout << ends << ends << "0: 返回" << endl;
		int tmp;
		cin >> tmp;
		switch (tmp)
		{
		case 1: {
			string name;
			int id;
			cout << "输入读者姓名、ID: " << endl;
			cin >> name >> id;
			Reader temp(name, id);
			AddReader(temp);
		} break;
		case 2: {
			int id;
			cout << "输入读者ID: " << endl;
			cin >> id;
			DeleteReader(id);
		} break;
		case 3: ListAllReaders(); break;
		case 4: {
			int id;
			cout << "输入读者ID: " << endl;
			cin >> id;
			CheckReader(id);
		} break;
		case 0: return; break;
		default: throw "非法输入!";
		}
	}
}

void Database::BookManage()
{
	system("color 2f");
	system("title 图书馆管理程序-管理员-图书管理");
	while (true)
	{
		cout << "请选择: " << endl;
		cout << ends << "当前图书数量: " << bookstore.size() << endl;
		cout << ends << ends << "1: 添加图书" << endl;
		cout << ends << ends << "2: 删除图书" << endl;
		cout << ends << ends << "3: 列出所有图书" << endl;
		cout << ends << ends << "4: 查询图书在架情况" << endl;
		cout << ends << ends << "0: 返回" << endl;
		int tmp;
		cin >> tmp;
		switch (tmp)
		{
		case 1: {
			string name;
			int id;
			cout << "输入书名、书号: " << endl;
			cin >> name >> id;
			Book temp(name, id);
			AddBook(temp);
		} break;
		case 2: {
			int id;
			cout << "输入书号: " << endl;
			cin >> id;
			DeleteBook(id);
		} break;
		case 3: ListAllBooks(); break;
		case 4: {
			int id;
			cout << "请输入图书号: " << endl;
			cin >> id;
			CheckBook(id);
		} break;
		case 0: return; break;
		default: throw "非法输入!";
		}
	}
}

void Database::BorrowAndRestore()
{
	system("color b4");
	system("title 图书馆管理程序-管理员-借还管理");
	while (true)
	{
		cout << "请选择: " << endl;
		cout << ends << ends << "1: 借书" << endl;
		cout << ends << ends << "2: 还书" << endl;
		cout << ends << ends << "0: 返回" << endl;
		int tmp;
		cin >> tmp;
		switch (tmp)
		{
		case 1: {
			int Rid, Bkid;
			cout << "输入读者ID、预借书号: " << endl;
			cin >> Rid >> Bkid;
			BorrowBook(Rid, Bkid);
		} break;
		case 2: {
			int Rid, Bkid;
			cout << "输入读者ID、待还书号: " << endl;
			cin >> Rid >> Bkid;
			RestoreBook(Rid, Bkid);
		} break;
		case 0: return; break;
		default: throw "非法输入!";
		}
	}
}

void Database::StartWork()
{
	system("color 3f");
	system("title 图书馆管理程序-管理员-菜单");
	cout << "请选择: " << endl;
	cout << ends << "1: 读者管理" << endl;
	cout << ends << "2: 图书管理" << endl;
	cout << ends << "3: 借还管理" << endl;
	cout << ends << "4: 显示图书馆数据" << endl;
	cout << ends << "5: 清除屏幕" << endl;
	cout << ends << "0: 退出系统" << endl;
	int tmp;
	cin >> tmp;
	switch (tmp)
	{
	case 1: ReaderManage(); break;
	case 2: BookManage(); break;
	case 3: BorrowAndRestore(); break;
	case 4: ShowDataStatistics(); break;
	case 5: system("cls"); break;
	case 0: exit(0); break;
	default: throw "非法输入!";
	}
}

void  Database::ReaderUI()
{
	system("color 5f");
	system("title 图书馆管理程序-读者-菜单");
	cout << "请选择: " << endl;
	cout << ends << "1: 借书" << endl;
	cout << ends << "2: 还书" << endl;
	cout << ends << "3: 列出所有图书" << endl;
	cout << ends << "4: 清除屏幕" << endl;
	cout << ends << "0: 退出系统" << endl;
	int tmp;
	cin >> tmp;
	switch (tmp)
	{
	case 1: {
		int Rid, Bkid;
		cout << "输入读者ID、预借书号: " << endl;
		cin >> Rid >> Bkid;
		BorrowBook(Rid, Bkid);
	}; break;
	case 2: {
		int Rid, Bkid;
		cout << "输入读者ID、待还书号: " << endl;
		cin >> Rid >> Bkid;
		RestoreBook(Rid, Bkid);
	}; break;
	case 3: ListAllBooks(); break;
	case 4: system("cls"); break;
	case 0: exit(0); break;
	default: throw "非法输入!";
	}
}

void Database::Pre()
{
	string name;

	name = "小明";
	Reader rd1(name, 10);
	AddReader(rd1);

	name = "小红";
	Reader rd2(name, 11);
	AddReader(rd2);

	name = "小刚";
	Reader rd3(name, 12);
	AddReader(rd3);

	name = "GoneWithWind";
	Book bk1(name, 100);
	AddBook(bk1);

	name = "活着";
	Book bk2(name, 101);
	AddBook(bk2);

	name = "C++Primer";
	Book bk3(name, 102);
	AddBook(bk3);
}

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
		while (true)
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
		while (true)
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
