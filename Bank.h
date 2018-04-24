#ifndef Bank_h
#define Bank_h

#include "Transaction.h"

class Bank
{
public:
	Bank(std::string name);

	void addCustomer(std::string n, std::string sn);
	void addAccount(std::vector<int> oid, int bl);
	void addOwner(int aid, int cid);
	void addTransaction(int said, int daid, int a);
	void approveTransaction(int tid, int oid);
	void declineTransaction(int tid, int oid);
	void showAccount(int aid);

private:
	std::string name;
	std::vector<Customer*> customers;
	std::vector<Account*> accuonts;
	std::vector<Transaction*> transactions;
};

#endif
