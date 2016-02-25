#include <stdio.h>

class NSum
{
public:
	NSum()
	{
		Result += ++N;
	}

	static int GetSum()
	{
		return Result;
	}
private:
	static int N;
	static int Result;
};

int NSum::N = 0;
int NSum::Result = 0;

int nSum(int n)
{
	NSum* temp = new NSum[n];
	delete []temp;
	temp = NULL;
	return NSum::GetSum();
}

int main()
{
	printf("%d\n",nSum(5));
}
