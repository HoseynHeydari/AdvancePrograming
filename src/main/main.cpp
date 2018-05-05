#include <iostream>
#include "Bank.hpp"

int main()
{
	Bank mellat("mellat");
	mellat.addCustomer("Peter", "Mims");
	mellat.addCustomer("Paul", "Turnage");
	mellat.addCustomer("Elizabeth", "Sanders");;
	mellat.addCustomer("Angel", "Garces");
	std::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	std::vector<int> v2;
	v2.push_back(3);
	mellat.addAccount(v1, 2000);
	mellat.addAccount(v2, 1000);
	mellat.addTransaction(0, 1, 1800);
	mellat.addTransaction(0, 1, 1000);
	mellat.addOwner(0, 0);
	mellat.approveTransaction(0, 1);
	mellat.approveTransaction(0, 2);
	mellat.approveTransaction(1, 1);
	mellat.approveTransaction(1, 2);
	mellat.showAccount(0);
	return 0;
}
