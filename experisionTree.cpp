#include <iostream>
#include <vector>

using namespace std;

enum satus
{
	BITWISE, ARITHMETIC
};

class Node
{
public:
	Node();
private:
	virtual int operation() = 0;
	Node *parent;
};

class Operator : public Node
{
public:
	Operator();
private:
	virtual int
	satus operandStatus;
};

class Operand : public Node
{
public:
	Operand();
private:
	int base;
	int data;
};

int Operand::operation()
{
	return data;
}

class Not : public Operator
{
public:
	Not();
private:
	Node *child;
};

class BiVariable : public Operator
{
public:
	BiVariable();
private:
	Node *firstChild;
	Node *secondChild;
};

class XOR
{
public:
	XOR();
private:
	vector<Node*> childs;
};

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}
