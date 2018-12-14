#include <iostream>

using namespace std;

string sort(string s)
{
	return s;
}

void substringIndex(string s, int index, int length)
{
	cout << s[index];
}

void substring(string s, int length)
{
	substringIndex(s, 0, length);
}

int main(int argc, char const *argv[])
{
	string s;
	int i;
	cin >> s >> i;
	substring(s,i);
	return 0;
}