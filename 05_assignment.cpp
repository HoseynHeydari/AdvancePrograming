#include <iostream>
#include <vector>
using namespace std;

class Function;

class Pair
{
public:
	Pair(double x, double y):x(x), y(y) {}
	friend ostream& operator<<(ostream& out, const Pair *p);
	void operator = (double d) { y = d; }
	// Pair& operator = (double d) { y = d; }
private:
	double x;
	double y;
	friend class Function;
};

ostream& operator<<(ostream& out, const Pair *p)
{
    out << p->y;
    return out;
}

class Function
{
public:
	Function() {}
	Function(Pair *p) { elements.push_back(p); }
	Function(Function &g);
	Function operator+(const Pair& p);
	Function& operator+=(const Pair& p);
	Function operator-(const Pair& p);
	Function& operator-=(const Pair& p);
	Pair* operator()(double d);
private:
	vector<Pair*> elements;
};

Function::Function(Function &g)
{
	for (int i = 0; i < g.elements.size(); ++i)
	{
		this->elements.push_back(g.elements[i]);
	}
}

Function Function::operator+(const Pair& p)
{
	for (auto it = elements.begin(); it != elements.end(); ++it)
	{
		if (((*it)->x) == p.x)
		{
			cerr << "invalid" << endl;
			return *this;
		}
	}
	elements.push_back(new Pair(p.x, p.y));
	return *this;
}

Function& Function::operator+=(const Pair& p)
{
	for (auto it = elements.begin(); it != elements.end(); ++it)
	{
		if (((*it)->x) == p.x)
		{
			cerr << "invalid" << endl;
			return *this;
		}
	}
	elements.push_back(new Pair(p.x, p.y));
	return *this;
}

Function Function::operator-(const Pair& p)
{
	for (auto it = elements.begin(); it != elements.end(); ++it)
	{
		if (((*it)->x) == p.x)
		{
			elements.erase(it);
			return *this;
		}
	}
	throw "invalid operation";
}

Function& Function::operator-=(const Pair& p)
{
	for (auto it = elements.begin(); it != elements.end(); ++it)
	{
		if (((*it)->x) == p.x)
		{
			elements.erase(it);
			return *this;
		}
	}
	throw "invalid operation";
}

Pair* Function::operator()(double d)
{
	for (auto it = elements.begin(); it != elements.end(); ++it)
	{
		if (((*it)->x) == d)
		{
			return (*it);
		}
	}
	throw "invalid operation";
}

int main()
{
	Function f(new Pair(1,10));
	cout << f(1) << endl;
	Pair p(4,3);
	f += Pair(9,0);
	cout << &p << endl;
	p = 5;
	*(f(1)) = 8;
	cout << "1" << endl;
	cout << &p << endl;
	cout << "2" << endl;
	f -= Pair(9,0);
	try
	{
		cout << f(9) << endl;
	}
	catch(const char* msg)
	{
		cerr << msg << endl;
	}
	try
	{
		f -= Pair(9,0);
	}
	catch(const char* msg)
	{
		cerr << msg << endl;
	}
	return 0;
}









