#include <iostream>
#include <pair.h>
#include <function.h>

using namespace std;

int main()
{
	Function delta;
	delta += Pair(0, 0);
	delta(0) = 1;
	for (int i = 1; i < 10; i++)
		delta += Pair(i, i);
	cout << delta << endl;
	Function U(delta);
	for (int i = 1; i < 10; i++)
		U(i) = 1;
  cout << (delta == U ? delta + U : 2 * U) << endl;
}
