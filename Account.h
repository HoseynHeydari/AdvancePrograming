#ifndef Account_h
#define Account_h

#include <vector>

class Bank;

class Account
{
	Account(Bank *bk, int id, int bl, std::vector<int> cids);
	
	void getOwnersId(std::vector<int> &oid);
	void addCustomer(int cid);
	void setBalance(int bl);
	
	Bank *bank;
	int id;
	int balance;
	std::vector<int> owners;
	
	friend class Bank;
};

#endif
