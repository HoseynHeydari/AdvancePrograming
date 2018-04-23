#include "Account.h"

Account::Account(Bank* bk, int id, int bl, std::vector<int> cus)
	:bank(bk)
	 ,id(id)
	 ,balance(bl)
	 ,owners(cus)
{
}

void Account::setBalance(int bl) { balance = bl; }

void Account::getOwnersId(std::vector<int> &oid)
{
	for (int i = 0; i < owners.size(); i++)
	{
		oid.push_back(owners[i]);
	}	
}

void Account::addCustomer(int cid) { owners.push_back(cid); }
