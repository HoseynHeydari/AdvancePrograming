#include <iostream>
#include <string>

using namespace std;

char downer(char cahracter)
{
	if ((cahracter < 97) && (cahracter > 64))
		return cahracter + 32;
	return cahracter;
}

int charCompair(char first, char second)
{
	if (first < second)
		return -1;
	else if (first > second)
		return 1;
	return 0;
}

int stringCompairInd(string first, string second, int Index)
{
	bool firstCond = (first.size() < Index);
	bool secondCond = (second.size() < Index);
	char firstChar;
	char secondChar;
	if (firstCond && secondCond)
		return 0;
	else if (firstCond)
		return -1;
	else if (secondCond)
		return 1;
	else
	{
		firstChar = downer(first[Index]);
		secondChar = downer(second[Index]);
		if (charCompair(firstChar, secondChar) != 0)
			return charCompair(firstChar, secondChar);
		else
			return stringCompairInd(first, second, ++Index);
	}
}

int stringCompair(string first, string second)
{
	return stringCompairInd(first, second, 0);
}

int main(int argc, char const *argv[])
{
	string a, b;
	cin >> a >> b;
	cout << stringCompair(a,b) << endl;
	return 0;
}