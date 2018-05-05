#ifndef Account_h
#define Account_h

#include "Customer.hpp"

class Account
{
public:
	Account(int id, int bl);
	
	void addOwner(Customer* owner);
	void addBalance(int amount);
	void addTransaction(int transactionId);
	void getOwnersId(std::vector<int> &oid);
	void getTransactionIds(std::vector<int> &tid);
	void showBalance();
	void showOwners();
	bool isBallanceEnough(int amount);
	int getId();
	int ownersNumber();
	bool isExists(int oid);

private:
	int id;
	int balance;
	std::vector<Customer*> owners;
	std::vector<int> transactions;
};

#endif