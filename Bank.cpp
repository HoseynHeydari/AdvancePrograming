#include "Bank.h"

Bank::Bank(std::string name)
	:name(name)
{
}

void Bank::addCustomer(int cid, std::string n, std::string sn)
{
	customers.push_back(new Customer(this, cid, n, sn));
}

void Bank::addAccount(int aid, int bl, std::vector<int> oids)
{
	accuonts.push_back(new Account(this, aid, bl, oids));
}

void Bank::addTransaction(int said, int daid, int a)
{
	transactions.push_back(new Transaction(this, said, daid, a));
}

void Bank::approveTransaction(int tid, int oid)
{
	transactions[tid]->approve_owner(oid);
}

void Bank::declineTransaction(int tid, int oid)
{
	transactions[tid]->decline_owner(oid);
}

void Bank::showAccount(int aid)
{
	std::cout << "Balance : " << accuonts[aid]->balance << std::endl;
	std::cout << "Owners : " << customers[0].print();
	int ownNum = customers.size();
	for (int i = 1; i < ownNum; ++i)
	{
		std::cout << " ,";
		customers[i].size();
	}
}

void Bank::declareWaiters(int aid, std::vector<int> &wlid)
{
	accuonts[aid]->getOwnersId(wlid);
}

bool Bank::isBallanceEnough(int aid, int amount) 
{
	return (accuonts[aid]->balance > trade);
}

void Bank::setBalance(int aid, int am)
{
	accuonts[aid]->balance += am;
}
