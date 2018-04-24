#include "Transaction.h"
#include <vector>


Transaction::Transaction(Account* sac, Account* dac, int a
	, std::vector<int> oids)
	:src_account(sac)
	,des_account(dac)
	,amount(a)
	,owners(oids)
	,request(Pending)
{
}

void Transaction::approve_transaction()
{
	if (src_account->isBallanceEnough(amount))
	{
		request = Accepted;
		src_account->addBalance(-amount);
		des_account->addBalance(amount);
	}
	else
	{
		request = Rejected;
	}
}

void Transaction::decline_transaction() { request = Rejected; }

bool Transaction::is_approved()
{
	std::vector<int>::iterator it;
	for (it = owners.begin(); it != owners.end(); ++it)
	{
		if (*it > -1)
		{
			return false;
		}
	}
	return true;
}

void Transaction::approve_owner(int oid)
{
	std::vector<int>::iterator it;
	it = std::find(owners.begin(), owners.end(), oid);
	*it = -1;
	if (is_approved())
	{
		approve_transaction();
	}
}

void Transaction::decline_owner(int oid)
{
	decline_transaction();
}

void Transaction::sets_account(Account* sap)
{
	src_account = sap;
}

void Transaction::setd_account(Account* dap)
{
	des_account = dap;
}

void Transaction::showTransaction()
{
	std::cout << amount << " to ";
	std::cout << des_account->getId() << " -> ";
	switch (request)
	{
		case Pending : std::cout << "Pending";
			break;
		case Accepted : std::cout << "Accepted";
			break;
		case Rejected : std::cout << "Rejected";
			break;
		default : std::cout << "Error happend";
	}
}