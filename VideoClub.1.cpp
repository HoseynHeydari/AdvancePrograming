#include <iostream>
#include <vector>
#include <string>
#include "Date.h"
using namespace std;

#define REGULAR 	0
#define CHILDRENS 	1
#define NEW_RELEASE	2

class Movie {
public:
	Movie(string t, int pc) : title(t), price_code(pc) {}

    int get_price_code() { return price_code; }
    string get_title() { return title; }
private:
	string title;
	int price_code;
};

class Catalog {
public:
	Movie* find_movie(string title) {
		for (int i = 0; i < movies.size(); i++)
			if (movies[i]->get_title() == title)
				return movies[i];
		return NULL;
	}	
	
	void add_movie(Movie* m) {
		if (!find_movie(m->get_title()))
			movies.push_back(m);
	}
	
	vector<Movie*> find_all_available() {
		return movies;
	}
private:
	vector<Movie*> movies;
};

class RentalItem {
public:
	RentalItem(Movie* m, int d) : movie(m), days_rented(d) {}
	
	int get_renter_points() {
		int points = 1;
		if ((movie->get_price_code() == NEW_RELEASE) && (days_rented > 2))
			points++;
		return points;
	}
private:
	Movie* movie;
	int days_rented;
};

class Rental {
public:
	Rental(Date d) : date_rented(d) {}
	
	void add_item(RentalItem item) {
		items.push_back(item);
	}
	
	int get_renter_points() {
		int total = 0;
		for (int i = 0; i < items.size(); i++)
			total += items[i].get_renter_points();
		return total;
	}
private:
	Date date_rented;
	vector<RentalItem> items;
};

class Customer {
public:
	Customer(string n) : name(n), renter_points(0) {}
	
	string get_name() { return name; }
	int get_renter_points() { return renter_points; }
	
	void rent(Rental r) { 
		renter_points += r.get_renter_points();
		rentals.push_back(r); 
	}
private:
	string name;
	int renter_points;
	vector<Rental> rentals;
};

class CustomerList {
public:
	Customer* find_customer(string name) {
		for (int i = 0; i < customers.size(); i++)
			if (customers[i]->get_name() == name)
				return customers[i];
		return NULL;
	}	

	void add_customer(Customer* c) {
		if (!find_customer(c->get_name()))
			customers.push_back(c);
	}
private:
	vector<Customer*> customers;
};

int main() {
	CustomerList clist;
	clist.add_customer(new Customer("Gholam"));
	clist.add_customer(new Customer("Ghamar"));
	
	Catalog cat;
	cat.add_movie(new Movie("Ezhdehaa-ye Vahshi", REGULAR));
	cat.add_movie(new Movie("Faasele-haa Dar Ofogh", REGULAR));
	cat.add_movie(new Movie("Sara Dar Mazra'eh", CHILDRENS));
	cat.add_movie(new Movie("Jooje-ye Saboor", CHILDRENS));
	cat.add_movie(new Movie("Arre-ye Kond", NEW_RELEASE));
	cat.add_movie(new Movie("Nabard-e Zangbaar", NEW_RELEASE));

	string name;
	cout << "Enter customer's name: ";
	cin >> name;
	
	cout << endl << "Available movies to rent: " << endl;
	vector<Movie*> movies = cat.find_all_available();
	for (int i = 0; i < movies.size(); i++)
		cout << (i+1) << '\t' << movies[i]->get_title() << endl;
	
	cout << endl << "Enter the codes of the selected movies (terminate by 0): ";
	vector<int> selections;
	int sel;
	cin >> sel;
	while (sel != 0) {
		selections.push_back(sel);
		cin >> sel;
	}
	cout << endl << "How many days to rent? ";
	int days;
	cin >> days;
	
	Rental r(Date(3,2,1391));
	for (int i = 0; i < selections.size(); i++)
		r.add_item(RentalItem(movies[selections[i]-1], days));
		
}














