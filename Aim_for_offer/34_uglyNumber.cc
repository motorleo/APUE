#include <iostream>
#include <vector>

int Min(int a,int b,int c)
{
	int min = a < b ? a:b;
	min = min < c ? min:c;
	return min;
}

int UglyNumber(int n)
{
	if (n <= 0) return 0;
	std::vector<int> vec;
	vec.reserve(n);
	vec.push_back(1);
	std::vector<int>::iterator iterMutiply2 = vec.begin();
	std::vector<int>::iterator iterMutiply3 = vec.begin();
	std::vector<int>::iterator iterMutiply5 = vec.begin();
	for (int i = 1;i < n;++i)
	{
		int min = Min(*iterMutiply2*2,*iterMutiply3*3,*iterMutiply5*5);
		vec.push_back(min);
		while (*iterMutiply2*2 <= vec.back()) ++iterMutiply2;
		while (*iterMutiply3*3 <= vec.back()) ++iterMutiply3;
		while (*iterMutiply5*5 <= vec.back()) ++iterMutiply5;
	}
	return vec.back();
}

int main()
{
	for (int i = 0;i < 100;++i)
	std::cout << UglyNumber(i) << std::endl;
}
