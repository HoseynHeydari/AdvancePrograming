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
	virtual void addChild(Node *n) = 0;
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
	virtual void addChild(Node *n) {}
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
	And<T>()
	:firstChild(NULL)
	,secondChild(NULL)
	{
	}
	virtual void addChild(Node *c);
	virtual int operation();
private:
	Node *firstChild;
	Node *secondChild;
};

template <class T>
void And<T>::addChild(Node *c)
{
	if (firstChild == NULL)
	{
		firstChild = c;
	}
	else if (secondChild == NULL)
	{
		secondChild = c;
	}
	else
	{
		//	TODO: handle error
	}
}

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
	Or<T>()
	:firstChild(NULL)
	,secondChild(NULL)
	{
	}
	virtual void addChild(Node *c);
	virtual int operation();
private:
	Node *firstChild;
	Node *secondChild;
};

template <class T>
void Or<T>::addChild(Node *c)
{
	if (firstChild == NULL)
	{
		firstChild = c;
	}
	else if (secondChild == NULL)
	{
		secondChild = c;
	}
	else
	{
		//	TODO: handle error
	}
}

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
	Not<T>()
	:child(NULL)
	{
	}
	virtual void addChild(Node *f);
	virtual int operation();
private:
	Node *child;
};

template <class T>
void Not<T>::addChild(Node *c)
{
	if (child == NULL)
	{
		child = c;
	}
	else
	{
		//	TODO: handle
	}
}

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
	// Xor<T>(vector<Node*> cs)
	// :childs(cs)
	// {
	// }
	virtual void addChild(Node *c);
	virtual int operation();
private:
	vector<Node*> childs;
};

template <class T>
void Xor<T>::addChild(Node *c)
{
	childs.push_back(c);
}

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
	void addNode(int pi, int base, int value);
	template <class T>
	void addNode(int pi);
private:
	int treeSize;
	Node *root;
	map<int, Node*> nodesIndex;
	map<int, int> nodesParent;
};

void ExperisionTree::addNode(int pi, int b, int v)
{
	// TODO: handle treeNode numbers.
	// TODO: handle parent type.
	int lastIndex = nodesIndex.size();
	nodesParent.insert(pair<int, int>(lastIndex, pi));
	nodesIndex.insert(pair<int, Node*>(lastIndex, new Operand(b, v)));
}

template <class T>
void ExperisionTree::addNode(int pi)
{
	// TODO: handle treeNode numbers.
	// TODO: handle parent type.
	int lastIndex = nodesIndex.size();
	nodesParent.insert(pair<int, int>(lastIndex, pi));
	nodesIndex.insert(pair<int, Node*>(lastIndex, new T()));
}

int main(int argc, char const *argv[])
{
	ExperisionTree et(3);
	et.addNode<And>(-1);
	return 0;
}