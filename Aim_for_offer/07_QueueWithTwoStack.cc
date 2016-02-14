#include <stack>
#include <stdexcept>
#include <stdio.h>

template <typename T>
class CQueue
{
public:
	//CQueue(); 
	//~CQueue();

	void appendTail(const T& node);

	T deleteHead();
private:
	std::stack<T> stack1;
	std::stack<T> stack2;
};

template <typename T>
void CQueue<T>::appendTail(const T& node)
{
	stack1.push(node);
}

template <typename T>
T CQueue<T>::deleteHead()
{
	if (stack2.empty())
	{
		while (!stack1.empty())
		{
			stack2.push(stack1.top());
			stack1.pop();
		}
	}
	if (stack2.empty())
		throw std::runtime_error("queue is empty.");
	T res = stack2.top();//top return reference.
	stack2.pop();
	return res;
}

int main()
{
	CQueue<int> test;
	test.appendTail(1);
	test.appendTail(2);

	printf("%d\n",test.deleteHead());
	printf("%d\n",test.deleteHead());
	return 0;
}
