#pragma once
#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <map>
#include "Book.h"
#include "date.h"
#include "Person.h"

struct stbt
{
	Book book;
	int LeaseDate;
};

class Process 
{
public:
	Process();
	~Process() {}
	BorrowBook(const Person &person);
	ReturnBook()

private:
	std::map<int,Book> stbooks;
	int CurrentDate;
};

Process::Process()
{

}


#endif // !PROCESS_H

