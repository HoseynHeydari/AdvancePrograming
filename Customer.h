#ifndef Customer_h
#define Customer_h

#include <string>
#include <iostream>

class Bank;

class Customer
{
	Customer(Bank* bk, int id, std::string n, std::string sn);
	print();
	
	Bank* bank;
	int id;
	std::string name;
	std::string surname;

	friend class Bank;
};

#endif
