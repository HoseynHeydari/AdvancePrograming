#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Bank;

class Customer
{
public:
	Customer(Bank *b, string n, string sn, int id);
private:
	Bank *bank;
	string name;
	string surename;
	int id;
	friend class Bank;
};

Customer::Customer(Bank *b, string n, string sn, int id)
:bank(b)
,name(n)
,surename(sn)
,id(id)
{
}

class Account
{
public:
	Account(Bank *b, vector<int> o_id, int bl, int id);
	void add_owner(int o_id) { owner_ids.push_back(o_id); }
private:
	Bank *bank;
	vector<int> owner_ids;
	int balance;
	int id;
	friend class Bank;
	friend class Transaction;
};

Account::Account(Bank *b, vector<int> o_id, int bl, int id)
:bank(b)
,owner_ids(o_id)
,balance(bl)
,id(id)
{
}

class Transaction
{
public:
	Transaction(Bank *b, int sa_id, int da_id, int a, int id);
	string approve_transaction(int o_id);
	void decline_transaction(int o_id);
private:
	Bank *bank;
	int src_account_id;
	int dest_account_id;
	int amount;
	map<int, int> approves;
	string flag;
	int id;
	friend class Bank;
};

string Transaction::approve_transaction(int o_id)
{
	auto it = approves.find(o_id);
	if (it != approves.end())
	{
		it->second = 42;
	}
	int flag = 1;
	for (auto it = approves.begin(); it != approves.end(); ++it)
	{
		flag *= it->second;
	}
	if (flag == 1)
	{
		return "accepted";
	}
	else return this->flag;
}

void Transaction::decline_transaction(int o_id)
{
	auto it = approves.find(o_id);
	if (it != approves.end())
	{
		flag = "rejected";
	}
}

class Bank
{
public:
	Bank(string br):branch(br) {}
	void create_customer(string n, string sn);
	void create_account(vector<int> o_id, int bl);
	void add_owner(int a_id, int o_id);
	void add_transaction(int sa_id, int da_id, int a);
	void approve_transaction(int tr_id, int o_id);
	void decline_transaction(int tr_id, int o_id);
	void show_account(int ac_id);
private:
	string branch;
	vector<Customer*> customers;
	vector<Account*> accounts;
	vector<Transaction*> transactions;
	friend class Transaction;
};

Transaction::Transaction(Bank *b, int sa_id, int da_id, int a, int id)
:bank(b)
,src_account_id(sa_id)
,dest_account_id(da_id)
,amount(a)
,id(id)
,flag("pending")
{
	vector<int>* sa_ow_ids = &(b->accounts[sa_id]->owner_ids);
	int sacc_own_num = sa_ow_ids->size();
	for (int i = 0; i < sacc_own_num; ++i)
	{
		approves[(*sa_ow_ids)[i]] = -1;
	}
}

void Bank::create_customer(string n, string sn)
{
	int turn = customers.size();
	customers.push_back(new Customer(this, n, sn, turn++));
}

void Bank::create_account(vector<int> o_id, int bl)
{
	int turn = accounts.size();
	accounts.push_back(new Account(this, o_id, bl, turn++));
}

void Bank::add_owner(int a_id, int o_id)
{
	accounts[a_id]->add_owner(o_id);
}

void Bank::add_transaction(int sa_id, int da_id, int a)
{
	int turn = transactions.size();
	transactions.push_back(new Transaction(this, sa_id, da_id, a, turn++));
}

void Bank::approve_transaction(int tr_id, int o_id)
{
	string flag = transactions[tr_id]->approve_transaction(o_id);
	Transaction *tr_temp = transactions[tr_id];
	if (flag == "accepted")
	{
		if (accounts[tr_temp->src_account_id]->balance >= tr_temp->amount)
		{
			accounts[tr_temp->src_account_id]->balance -= tr_temp->amount;
			accounts[tr_temp->dest_account_id]->balance += tr_temp->amount;
			tr_temp->flag = "accepted";
		}
		else
			tr_temp->flag = "declined";
	}
}

void Bank::decline_transaction(int tr_id, int o_id)
{
	transactions[tr_id]->decline_transaction(o_id);
}

void Bank::show_account(int ac_id)
{
	cout << "Balance : " << accounts[ac_id]->balance << endl;
	cout << "Owner : ";
	auto oi_temp = accounts[ac_id]->owner_ids;
	for (auto it = oi_temp.begin(); it != oi_temp.end(); ++it)
	{
		cout << customers[*it]->name << " ";
		cout << customers[*it]->surename << ",";
	}
	cout << endl;
	int tr_num = 1;
	for (auto it = transactions.begin(); it != transactions.end(); ++it)
	{
		if (((*it)->src_account_id) == ac_id)
		{
			cout << "[" << tr_num << "] " << (*it)->amount;
			cout  << " to " << (*it)->dest_account_id;
			cout << " -> " << (*it)->flag << endl; 
			tr_num++;
		}
	}
}

// class Clerk
// {
// public:
// 	Clerk();
// private:
// 	Bank *bank;
// 	friend ostream& operator<<(ostream& out, const A& a);
// 	friend istream& operator>>(istream& in, A& a);
// };

// ostream& operator<<(ostream& out, const A& a) {
//     out << a.data;
//     return out;
// }

// istream& operator>>(istream& in, A& a) {
//     in >> a.data;
//     return in;
// }

int main()
{
	Bank melat("asli");
	string command, name, surename;
	int id;
	vector<int> argid;
	int count;
	while(cin >> command)
	{
		if (command == "create_customer")
		{
			cin >> name >> surename;
			melat.create_customer(name, surename);
		}
		if (command == "create_account")
		{
			// while(cin >> id)
			// 	argid.push_back(id);
			cin >> id;
			argid.push_back(id);
			cin >> id;
			argid.push_back(id);
			count = argid.size();
			auto first = argid.begin();
			auto last = argid.end() - 1;
			vector<int> ids(first, last);
			melat.create_account(ids, id);
		}
		if (command == "add_owner")
		{
			int a_io, o_id;
			cin >> a_io >> o_id;
			melat.add_owner(a_io, o_id);
		}
		if (command == "book_transaction")
		{
			int src_io, dest_id, amount;
			cin >> src_io >> dest_id >> amount;
			melat.add_transaction(src_io, dest_id, amount);
		}
		if (command == "approve_transaction")
		{
			int tr_id, o_id;
			cin >> tr_id >> o_id;
			melat.approve_transaction(tr_id, o_id);
		}
		if (command == "decline_transaction")
		{
			int tr_id, o_id;
			cin >> tr_id >> o_id;
			melat.decline_transaction(tr_id, o_id);
		}
		if (command == "show_account")
		{
			int a_id;
			cin >> a_id;
			melat.show_account(a_id);
		}
	}
	return 0;
}