#ifndef Bank_h
#define Bank_h

#include "Customer.h"
#include "Account.h"
#include "Transaction.h"
#include <vector>
#include <iostream>

class Bank
{
public:
	Bank(std::string name);

	void addCustomer(int cid, std::string n, std::string sn);
	void addAccount(int aid, int bl, std::vector<int> oids);
	void addTransaction(int said, int daid, int a);
	void approveTransaction(int tid, int oid);
	void declineTransaction(int tid, int oid);
	void showAccount(int aid);

private:
	void declareWaiters(int aid, std::vector<int> &wlid);
	bool isBallanceEnough(int aid, int amount);
	void setBalance(int aid, int am);
	
	std::string name;
	std::vector<Customer*> customers;
	std::vector<Account*> accuonts;
	std::vector<Transaction*> transactions;
	
	friend class Transaction;
};

#endif
