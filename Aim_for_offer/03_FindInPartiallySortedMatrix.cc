
bool find(int* matrix,int rows,int columns,int num)
{
	if (matrix == NULL || rows < 0 || columns < 0) return false;
	int row = 0;
	int column = columns - 1;
	while (row < rows && column >= 0)
	{
		current = matrix[columns*row +column]
		if (current == num)
		{
			return true;
		}
		else if (current < num)
		{
			++row;
		}
		else
		{
			--column;
		}
	}
	return false;
}
