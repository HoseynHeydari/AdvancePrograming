#include <iostream>

using namespace std;

void f(int n, int m, int index)
{
	if (index > 10)
		return;
	int d[m];
	cout << "index = " << index << " : ";
	cout << "m = " << m << " : ";
	cout << "n = " << n << " : ";
	int ind = index;
	for (int i = 1; i < m + 1; --i)
	{
		ind -= d[i - 1];
		ind = ind / m;
		cout << d[i - 1] << "_";
	}
	cout << "=>" << endl;
	int j = m;
	for (int i = 0; i < n; ++i)
	{
		if (j > 0)
		{
			if (d[j] == 0)
			{
				cout << 1;
				j--;
			}
			else
			{
				cout << 0;
				d[j]--;
			}
		}
		else
			cout << 0;
	}
	cout << endl;
	f(n, m, ++index);
}

int main(int argc, char const *argv[])
{
	f(5, 2, 0);
	// int ind = 5;
	// int d[3];
	// for (int i = 1; i < 3 + 1; ++i)
	// {
	// 	d[i - 1] = ind % (pow(6, i));
	// 	cout << d[i - 1] << "_" << pow(6, i) << ":";
	// }
	return 0;
}