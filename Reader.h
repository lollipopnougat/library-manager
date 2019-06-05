//Reader.h
#ifndef READER_H
#define READER_H
#include <string>
#include <vector>
#include "Book.h"

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
#endif