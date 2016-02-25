#include <stdio.h>
#include <stdexcept>
#include <string.h>

bool IsContinuous(int* numbers,int length) //FIXME:extension
{
	if (numbers == NULL || length != 5) 
		throw std::invalid_argument("invalid input!");
	int Poke[14];
	memset(Poke,0,14*sizeof(int));
	for (int i = 0;i < length;++i)
	{
		if (numbers[i] > 13 || numbers[i] < 0) 
			throw std::invalid_argument("invalid input!");
		++Poke[numbers[i]];
	}
	int FirstPoke = 1;
	for (;FirstPoke <= 13;++FirstPoke)
	{
		if (Poke[FirstPoke] == 1) break;
		if (Poke[FirstPoke] > 1) return false;
	}
	if (FirstPoke == 14) 
	{
		return true;
	}
	int count = 0;
	for (int i = FirstPoke;i < FirstPoke + 5;++i)
	{
		if (Poke[i] == 0) ++count;
		else if (Poke[i] > 1) return false;
	}
	if (count == Poke[0]) return true;
	else return false;
}

int main()
{
	int test[] = {1,2,3,4,6};
	if (IsContinuous(test,5)) printf("yes\n");
	else printf("no\n");
}
