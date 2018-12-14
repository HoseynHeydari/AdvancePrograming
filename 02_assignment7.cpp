#include <iostream>

using namespace std;

int choise(int n, int m)
{
	int u = 1;
	int d = 1;
	for (int i = 1; i < m + 1; ++i)
	{
		u *= (n + 1 - i);
		d *= i;
	}
	return u / d;
}

void fillarray1(int mod, int *d, int v, int it)
{
	if (it == 0)
		return;
	it--;
	d[it] = v % mod;
	fillarray1(mod, d, ((v - d[it])/mod), it);
}

void fillarray(int mod, int *d, int v, int len)
{
	fillarray1(mod, d, v, len);
}

void print(int n, int *d, int ind)
{
	if (n > 0)
	{
		if (d[ind] > 0)
		{
			cout << 0;
			d[ind]--;
		}
		else
		{
			cout << 1;
			ind++;
		}
		print(--n, d, ind);
	}
	else
	{
		cout << endl;
		return;
	}
}

void strprint(int n, int m, int *d, int it)
{
	fillarray(n - m + 1, d, it, m);
	print(n, d, 0);
}

void substr(int n, int m)
{
	int chs = choise(n,m);
	int d[m];
	strprint(n, m, d, chs);
}

int main(int argc, char const *argv[])
{
	// substr(5, 2);
	int d[2];
	for (int i = 0; i < 9; ++i)
	{
		fillarray(4, d, i, 2);
		cout << d[0];
		cout << d[1] << endl;
		// print(5, d, 0);
	}
	return 0;
}