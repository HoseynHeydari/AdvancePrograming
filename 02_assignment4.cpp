#include <iostream>

using namespace std;

void psus(string s, int n, int *index)
{
	for (int i = 0; i < n; ++i)
		cout << s[index[i]];
	cout << endl;
}

void indpp(int *index, int n)
{
	if(index[n - 1] < (index[n] - 1))
		index[n - 1]++;
	else if (index[n - 2] < (index[n - 1] - 1))
		index[n - 2]++;
}

void f2(string s, int n, int *index)
{
	bool condition = true;
	for (int i = 0; i < n; ++i)
	{
		condition = condition && (index[i] < n);
		if (condition)
			break;
	}
	if (condition)
		psus(s, n, index);
	indpp(index, n);
	f2(s, n, index);
}

void f(string s, int n)
{
	int index[n+1];
	for (int i = 0; i < n; ++i)
		index[i] = i;
	index[n] = n - 1;
	f2(s, n, index);
}

int main(int argc, char const *argv[])
{
	int n;
	string s;
	cin >> s >> n;

	return 0;
}