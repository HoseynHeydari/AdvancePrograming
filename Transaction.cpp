#include "Transaction.h"
#include <vector>
#include "Bank.h"

Transaction::Transaction(Bank* bk, int said, int daid, int a)
	:bank(bk)
	 ,src_ac_id(said)
	 ,des_ac_id(daid)
	 ,amount(a)
	 ,state(0)
{
	bank->declareWaiters(said, wait_list_id);
}

void Transaction::approve_transaction()
{
	if (bank->isBallanceEnough(src_ac_id, amount))
	{
		state = 1;
		bank->setBalance(src_ac_id, -amount);
		bank->setBalance(des_ac_id, amount);
	}
	else
	{
		state = -1;
	}
}

void Transaction::decline_transaction() { state = -1; }

bool Transaction::is_approved()
{
	std::vector<int>::iterator it;
	for (it = wait_list_id.begin(); it != wait_list_id.end(); ++it)
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
	wait_list_id[oid] = -1;
	if (is_approved())
	{
		approve_transaction();
	}
}

void Transaction::decline_owner(int oid)
{
	decline_transaction();
}
