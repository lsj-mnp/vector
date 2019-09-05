#include <vector>
#include "CVector.h"

int main()
{
	using std::cout;

	std::vector<int> v{};
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		*it = 1;
	}

	for (auto it = v.rbegin(); it != v.rend(); ++it)
	{
		*it = 3;
	}

	CVector a{ 1, 3, 5 };
	for (auto it = a.begin(); it != a.end(); ++it)
	{
		cout << *it;
	}
	for (auto i : a)
	{
		cout << i;
	}

	for (auto it = a.rbegin(); it != a.rend(); ++it)
	{
		cout << *it;
	}

	for (auto it = a.cbegin(); it != a.cend(); ++it)
	{
		cout << *it;
	}

	return 0;
}