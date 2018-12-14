#include<iostream>

using namespace std;

class A
{
public:
	A() { a = 5; }
	int a;
};

class B
{
public:
	template <class T>
	void pinting();
	A* b;
};

template <class T>
void B::pinting()
{
	b = new T();
	cout << b->a << endl;
}

int main(int argc, char const *argv[])
{
	B instance;
	instance.pinting<A>();
	return 0;
}