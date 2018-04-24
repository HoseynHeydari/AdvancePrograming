#include "Account.h"

Account::Account(int id, int bl)
	:id(id)
	,balance(bl)
{
}

void Account::addOwner(Customer* owner)
{
	owners.push_back(owner);
}

void Account::addBalance(int amount)
{
	balance += amount;
}

void Account::addTransaction(int transactionId)
{
	transactions.push_back(transactionId);
}

void Account::getOwnersId(std::vector<int> &oid)
{
	for (int i = 0; i < owners.size(); i++)
	{
		oid.push_back(owners[i]->getId());
	}	
}

void Account::getTransactionIds(std::vector<int> &tid)
{
	for (int i = 0; i < transactions.size(); i++)
	{
		tid.push_back(transactions[i]);
	}	
}

void Account::showBalance()
{
	std::cout << "Balance : " << balance << std::endl;
}

void Account::showOwners()
{
	std::cout << "Owners : ";
	owners[0]->print();
	int ownNum = owners.size();
	for (int i = 1; i < ownNum; ++i)
	{
		std::cout << " ,";
		owners[i]->print();
	}
	std::cout << std::endl;
}

bool Account::isBallanceEnough(int amount)
{
	return !(balance < amount);
}

int Account::getId()
{
	return id;
}