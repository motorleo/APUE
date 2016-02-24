#include <stdio.h>

const int kDicesNum = 6;

void PrintDices(int n)
{
	if (n <= 0) return;
	int NumSum[2][n*kDicesNum + 1];
	int flagCurrent = 0;
	int flagLast = 1;
	for (int i = 1;i <= kDicesNum;++i)
	{
		NumSum[flagLast][i] = 1;
		NumSum[flagCurrent][i] = 0;
	}
	for (int i = kDicesNum + 1;i <= n*kDicesNum;++i)
	{
		NumSum[flagLast][i] = 0;
		NumSum[flagCurrent][i] = 0;
	}
	for (int i = 2;i <= n;++i)//nDices
	{
		flagLast = flagCurrent ^ 1;
		for (int j = 1;j <= i*kDicesNum;++j)//current number
		{
			NumSum[flagCurrent][j] = 0;
			for (int k = 1;j - k >= 1 && k <= 6;++k)
			{
				NumSum[flagCurrent][j] += NumSum[flagLast][j - k];
			}
		}
		flagCurrent = flagLast;
	}
	//print
	flagCurrent = flagCurrent ^ 1;
	double base = 1.0;
	for (int i = 1;i <= n;++i)
		base *= kDicesNum;
	double ratio;
	for (int i = n;i <= n*kDicesNum;++i)
	{
		ratio = static_cast<double>(NumSum[flagCurrent][i]) / base;
		printf("%d:%d:%g\n",i,NumSum[flagCurrent][i],ratio);
	}
}

int main()
{
	PrintDices(11);
}
