#ifndef Customer_h
#define Customer_h

#include <string>
#include <vector>
#include <iostream>

class Customer
{
public:
	Customer(int id, std::string n, std::string sn);

	int getId();
	void print();
	bool isEqual(std::string s1, std::string s2);

private:
	int id;
	std::string name;
	std::string surname;
};

#endif
