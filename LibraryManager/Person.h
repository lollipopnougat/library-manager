#pragma once
#ifndef PERSON_H
#define PERSON_H
#include <string>

class Person
{
public:
	Person(const std::string &name, const int number) :name(name), number(number) {}
	~Person() {}
	std::string GetName() { return name; }
	int GetNum() { return number; }
private:
	std::string name;
	int number;
};







#endif // !PERSON_H

