#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Node
{
public:
	// TODO: decide on protecting operation() fnction.
// protected:
	virtual int operation() = 0;
};

class Operand : public Node
{
public:
	Operand(int b, int v)
	:base(b)
	,value(v)
	{
	}
private:
	int base;
	int value;
	virtual int operation() { return value; }
};

class Mode
{
private:
	virtual int _and(int , int) = 0;
	virtual int _or(int , int) = 0;
	virtual int _not(int) = 0;
	virtual int _xor(vector<int>) = 0;
};

class Arithmetic : public Mode
{
protected:
	virtual int _and(int first, int second) { return first * second; }
	virtual int _or(int first, int second) { return first + second; }
	virtual int _not(int argument) { return -argument; }
	virtual int _xor(vector<int> arguments);
};

int Arithmetic::_xor(vector<int> arguments)
{
	int median = 0;
	for (auto it = arguments.begin(); it != arguments.end(); ++it)
	{
		median += *it;
	}
	median = median / arguments.size();
	return median;
}

class Bitwise : public Mode
{
protected:
	virtual int _and(int first, int second) { return (first && second); }
	virtual int _or(int first, int second) { return (first || second); }
	virtual int _not(int argument) { return !argument; }
	virtual int _xor(vector<int> arguments);
};

int Bitwise::_xor(vector<int> arguments)
{
	int median = *(arguments.begin());
	for (auto it = arguments.begin(); it != arguments.end(); ++it)
	{
		median ^= *it;
	}
	median ^= *(arguments.begin());
	median = median / arguments.size();
	return median;
}

template <class T = Arithmetic>
class And : public Node, public T
{
public:
	And<T>(Node *f, Node *s)
	:firstChild(f)
	,secondChild(s)
	{
	}
	virtual int operation();
private:
	Node *firstChild;
	Node *secondChild;
};

template <class T>
int And<T>::operation()
{
	int firstValue = firstChild->operation();
	int secondValue = secondChild->operation();
	return T::_and(firstValue, secondValue);
}

template <class T>
class Or : public Node, public T
{
public:
	Or<T>(Node *f, Node *s)
	:firstChild(f)
	,secondChild(s)
	{
	}
	virtual int operation();
private:
	Node *firstChild;
	Node *secondChild;
};

template <class T>
int Or<T>::operation()
{
	int firstValue = firstChild->operation();
	int secondValue = secondChild->operation();
	return T::_or(firstValue, secondValue);
}

template <class T>
class Not : public Node, public T
{
public:
	Not<T>(Node *c)
	:child(c)
	{
	}
	virtual int operation();
private:
	Node *child;
};

template <class T>
int Not<T>::operation()
{
	int value = child->operation();
	return T::_not(value);
}

template <class T>
class Xor : public Node, public T
{
public:
	Xor<T>(vector<Node*> cs)
	:childs(cs)
	{
	}
	virtual int operation();
private:
	vector<Node*> childs;
};

template <class T>
int Xor<T>::operation()
{
	vector<int> values;
	for (auto it = childs.begin(); it != childs.end(); ++it)
	{
		values.push_back((*it)->operation());
	}
	return T::_xor(values);
}

class ExperisionTree
{
public:
	ExperisionTree(int ts)
	:treeSize(ts)
	{
	}
	int evaluate() { return root->operation(); }
	void addNode(int pi, int value, int base);
private:
	int treeSize;
	Node *root;
	map<int, Node*> nodesIndex;
	map<int, int> nodesParent;
};

void addNode(int pi, int v, int b)
{
	// TODO: handle treeNode numbers.
	// TODO: handle parent type.
	
}

int main(int argc, char const *argv[])
{
	
	return 0;
}