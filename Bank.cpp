#include "Bank.hpp"

Bank::Bank(std::string name)
	:name(name)
{
}

void Bank::addCustomer(std::string n, std::string sn)
{
	int index = customers.size();
	if (Bank::searchCustomer(n, sn, customers))
	{
		throw("This name exists.");
	}
	customers.push_back(new Customer(index, n, sn));
	std::cout << index << std::endl;
}

void Bank::addAccount(std::vector<int> oid, int bl)
{
	int index = accuonts.size();
	accuonts.push_back(new Account(index, bl));
	int size = oid.size();
	for (int i = 0; i < size; ++i)
	{
		accuonts[index]->addOwner(customers[oid[i]]);
	}
	std::cout << index << std::endl;
}

void Bank::addOwner(int aid, int cid)
{
	bool condition = (aid >= accuonts.size());
	condition |= (cid >= accuonts[aid]->ownersNumber());
	if (condition)
	{
		throw("Account or Customer index is fault.");
	}
	else if (accuonts[aid]->isExists(cid))
	{
		throw("He/She is alredy an owner.");
	}
	accuonts[aid]->addOwner(customers[cid]);
}

void Bank::addTransaction(int said, int daid, int a)
{
	int index = transactions.size();
	std::vector<int> oids;
	accuonts[said]->getOwnersId(oids);
	transactions.push_back(new Transaction(accuonts[said]
		, accuonts[daid], a, oids));
	accuonts[said]->addTransaction(index);
	std::cout << index << std::endl;
}

void Bank::approveTransaction(int tid, int oid)
{
	bool condition = (tid >= transactions.size());
	condition |= (oid >= transactions[tid]->ownersNumber());
	if (condition)
	{
		throw("Transaction or Customer index is fault.");
	}
	else if (transactions[tid]->isExists(oid))
		// TODO: need coverte vector to map.
	{
		throw("He/She is alredy an owner.");
	}
	transactions[tid]->approve_owner(oid);
}

void Bank::declineTransaction(int tid, int oid)
{
	transactions[tid]->decline_owner(oid);
}

void Bank::showAccount(int aid)
{
	accuonts[aid]->showBalance();
	accuonts[aid]->showOwners();
	std::vector<int> tids;
	accuonts[aid]->getTransactionIds(tids);
	for (int i = 0; i < tids.size(); ++i)
	{
		std::cout << "[" << i << "] ";
		transactions[tids[i]]->showTransaction();
		std::cout << std::endl;
	}
}

bool Bank::searchCustomer(std::string s1, std::string s2
		, std::vector<Customer*> customers)
{
	int size = customers.size();
	for (int i = 0; i < size; ++i)
	{
		if (customers[i]->isEqual(s1, s2) == 0)
		{
			return true;
		}
	}
	return false;
}
