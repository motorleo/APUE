#include <stdio.h>
#include <list>

int LeftNumber(int n,int m)
{
	if (n <= 0 || m <= 0) return -1;
	std::list<int> circle;
	for (int i = 0;i < n;++i)
		circle.push_back(i);
	std::list<int>::iterator iter = circle.begin();
	for (int i = 0;i < n -1;++i)
	{
		for (int j = 0;j < m - 1;++j)
		{
			++iter;
			if (iter == circle.end())
				iter = circle.begin();
		}
		printf("erase:%d\n",*iter);
		iter = circle.erase(iter);
		if (iter == circle.end())
			iter = circle.begin();
	}
	return circle.front();
}

int main()
{
	printf("left:%d\n",LeftNumber(1,3));
}
