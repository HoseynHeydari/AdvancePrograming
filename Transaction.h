#ifndef Transaction_h
#define Transaction_h

#include <string>
#include <vector>

class Bank;

class Transaction
{
	Transaction(Bank* bk, int said, int daid, int a);

	void approve_transaction();
	void decline_transaction();
	void approve_owner(int oid);
	void decline_owner(int oid);
	
	Bank* bank;
	int src_ac_id;
	int des_ac_id;
	int amount;
	std::vector<int> wait_list_id;
	int state;
	bool is_approved();
	
	friend class Bank;
};

#endif
