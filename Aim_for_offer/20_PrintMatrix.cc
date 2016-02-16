#include <stdio.h>

void PrintCircle(int* matrix,int rows,int columns,int start)
{
	int currentIndex = start + start * columns - 1;
	//right row
	for (int i = start;i < columns - start;++i)
	{
		++currentIndex;
		printf("%d ",matrix[currentIndex]);
	}
	//down column
	if (start + 1 >= rows - start) return;
	for (int i = start + 1;i < rows - start;++i)
	{
		currentIndex += columns;
		printf("%d ",matrix[currentIndex]);
	}
	//left row
	if (start + 1 >= columns - start) return;
	for (int i = start + 1;i < columns - start;++i)
	{
		--currentIndex;
		printf("%d ",matrix[currentIndex]);
	}
	//up column
	if (start + 2 >= rows - start) return;
	for (int i = start + 2;i < rows - start;++i)
	{
		currentIndex -= columns;
		printf("%d ",matrix[currentIndex]);
	}
}

void PrintMartix(int* matrix,int rows,int columns)
{
	if (matrix == NULL) return;
	if (rows <= 0 || columns <= 0) return;
	int start = 0;
	while (rows > start*2 && columns > start*2)
	{
		PrintCircle(matrix,rows,columns,start);
		++start;
	}
	printf("\n");
}

int main()
{
	int matrix[] = {1,2,3,4,5,6,7,8,9};
	PrintMartix(matrix,1,9);
	int matrix1[] = {1};
	PrintMartix(matrix,1,1);
	return 0;
}
