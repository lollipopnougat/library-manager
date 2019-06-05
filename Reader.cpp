#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Book.h"
#include "Reader.h"

using namespace std;

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