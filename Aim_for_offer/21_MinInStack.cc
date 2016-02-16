#include <stdio.h>
#include <vector>

template <typename T>
class StackWithMin
{
public:
	void push(const T& value)
	{
		DataVec.push_back(value);
		T currentMin = MinVec.back();
		if (!MinVec.empty() && currentMin < value)
		{
			MinVec.push_back(currentMin);
		}
		else
		{
			MinVec.push_back(value);
		}
	}

	void pop()
	{
		DataVec.pop();
		MinVec.pop();
	}
	
	const T& min()
	{
		return MinVec.back();
	}
private:
	std::vector<T> DataVec;
	std::vector<T> MinVec;
};
