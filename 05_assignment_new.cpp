#include <iostream>
#include <vector>

using namespace std;

class Function;

class Pair
{
public:
	Pair(double x, double y)
	:x(x)
	,y(y)
	{
	}
	void operator=(const double &d);
	friend ostream& operator<<(ostream& out, const Pair *p);
private:
	double x;
	double y;
	friend class Function;
};

void Pair::operator=(const double &d)
{
	y = d;
}

ostream& operator<<(ostream& out, const Pair *p)
{
    out << p->y;
    return out;
}

class Function
{
public:
	Function() {}
	Function(Function &g);
	void operator=(const Function &f);
	Function operator+(const Pair &p);
	Function operator-(const Pair &p);
	Function& operator+=(const Pair &p);
	Function& operator-=(const Pair &p);
	double& operator()(double d);
private:
	vector<Pair*> pairs;
};

Function::Function(Function &g)
{
	int count = g.pairs.size();
	for (int i = 0; i < count; ++i)
	{
		pairs.push_back(g.pairs[i]);
	}
}

void Function::operator=(const Function &f)
{
	pairs.clear();
	int count = f.pairs.size();
	for (int i = 0; i < count; ++i)
	{
		pairs.push_back(f.pairs[i]);
	}
}

Function Function::operator+(const Pair &p)
{
	int count = pairs.size();
	for (int i = 0; i < count; ++i)
	{
		if (p.x == pairs[i]->x)
		{
			throw "Invalid pair!";
		}
	}
	pairs.push_back(new Pair(p.x, p.y));
	return *this;
}

Function& Function::operator+=(const Pair &p)
{
	this->operator+(p);
	return *this;
}

Function Function::operator-(const Pair &p)
{
	int count = pairs.size();
	for (int i = 0; i < count; ++i)
	{
		if (p.x == pairs[i]->x)
		{
			pairs.erase(pairs.begin()+i);
			return *this;
		}
	}
	throw "Invalid pair!";
}

double& Function::operator()(double d)
{
	int count = pairs.size();
	for (int i = 0; i < count; ++i)
	{
		if (d == pairs[i]->x)
		{
			return (pairs[i]->y);
		}
	}
	throw "Invalid element!";
}



int main()
{
	Pair p1(1,2);
	Function f;
	f += p1;
	cout << f(1) << endl;
	f += Pair(2,3);
	cout << f(2) << endl;
	Function g;
	g = f + Pair(4,5);
	cout << g(1) << endl;
	cout << g(4) << endl;
	g(4) = 7;
	cout << g(4) << endl;
	return 0;
}