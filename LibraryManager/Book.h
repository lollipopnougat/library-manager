#pragma once
#ifndef BOOK_H
#define BOOK_H
#include <string>

class Book
{
public:
	Book(const std::string &na,const int number) :name(na), num(number) {}
	~Book() {}
	std::string GetName() { return name; }
	int GetNum() { return num; }
private:
	std::string name;
	int num;
};











#endif // !BOOK_H

