//Database.h
#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include <map>
#include "Book.h"
#include "Reader.h"

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
#endif