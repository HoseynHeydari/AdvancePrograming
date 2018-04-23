#include "Customer.h"

Customer::Customer(Bank* bk, int id, std::string n, std::string sn)
	:bank(bk)
	 ,id(id)
	 ,name(n)
	 ,surname(sn)
{
}

Customer::print()
{
	std::cout << " " << name << " " << surname;
}
