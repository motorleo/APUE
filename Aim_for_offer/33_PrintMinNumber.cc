#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

std::string Lcompare;
std::string Rcompare;

bool compare(const std::string& num1,const std::string& num2)
{
	Lcompare.assign(num1 + num2);
	Rcompare.assign(num2 + num1);
	return Lcompare < Rcompare;
}

void PrintMinNumber(int* numbers,int length)
{
	if (numbers == NULL || length <= 0) return;
	std::vector<std::string> vec;
	char num[10];
	for (int i = 0;i < length;++i)
	{
		sprintf(num,"%d",numbers[i]);
		std::string str(num);
		vec.push_back(str);
	}
	std::sort(vec.begin(),vec.end(),compare);
	std::vector<std::string>::iterator iter = vec.begin();
	for (;iter != vec.end();++iter)
		std::cout << *iter;
	std::cout << std::endl;
}

int main()
{
	int test[] = {3,32,321};
	PrintMinNumber(test,3);
}
