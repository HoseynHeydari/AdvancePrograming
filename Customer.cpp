#include "Customer.h"

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
