#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Book.h"
#include "Reader.h"
#include "Database.h"

using namespace std;


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
			if (tmp == 'N' || tmp == 'n')
			{
				cout << "已取消删除." << endl;
			}
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
	{
		cout << "姓名: " << it->second.GetName() << ends << "ID: " << it->first << endl;
	}
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
	case 2:{
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