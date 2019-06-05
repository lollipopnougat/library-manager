//Book.h
#ifndef BOOK_H
#define BOOK_H
#include <string>
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
	bool operator == (const Book &bk) {if(bk.name == this->name && bk.id == this->id) return true; else return false;}
private:
	std::string name;
	int id;
	bool onshelf = true;
};
#endif