#include<string>
#include <iostream>
using namespace std;

string itoBase(unsigned int nb, string base)
{
	const unsigned int sysNum{ base.length() };
	string result;
	unsigned int temp{ nb };
	do
	{
		int sym = temp % sysNum;
		result.insert(0, 1, base[sym]);
		temp /= sysNum;
	} while (temp > 0);

	return result;
}

string itoBase(string nb, string baseSrc, string baseDst)
{
	const unsigned int sysNum{ baseSrc.length() };
	unsigned int result{ 0 };
	unsigned int factor{ 1 };
	for (int count = (nb.length() - 1); count >= 0; --count)
	{
		if (baseSrc.find(nb[count]) == -1)
		{
			cerr << "Usage: Error of first argument" << '\n';
			string temp;
			getline(std::cin, temp);
			exit(2);
		}
		unsigned int temp{ baseSrc.find(nb[count]) };
		result += temp * factor;
		factor *= sysNum;
	}
	return itoBase(result, baseDst);
}