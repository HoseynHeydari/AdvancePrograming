#include "Customer.hpp"

Customer::Customer(int id, std::string n, std::string sn)
	:id(id)
	,name(n)
	,surname(sn)
{
}

int Customer::getId()
{
	return id;
}

void Customer::print()
{
	std::cout << " " << name << " " << surname;
}

bool Customer::isEqual(std::string s1, std::string s2)
{
	bool condition = s1.compare(name);
	condition &= s2.compare(surname);
	return condition;
}

