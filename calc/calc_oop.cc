#include <iostream>
#include <stdlib.h>
#include "calc_oop.h"

int ExpTree::Precedence(const char op)
{
	switch (op)
	{
		case '+': case '-':
			return 1;
		case '*': case '/':
			return 2;
		case ')': case '@':
		default:
			//other operator or '@'
		return 0;  
	}
}

NodePtr ExpTree::makeNode(const char op,const NodePtr& l,const NodePtr& r)
{
	switch (op)
	{
		case '+':
			{
				NodePtr temp(new AddNode(l,r));
				return temp;
			}
		case '-':
			{
				NodePtr temp(new MinusNode(l,r));
				return temp;
			}
		case '*':
			{
				NodePtr temp(new MultiplyNode(l,r));
				return temp;
			}
		case '/':
			{
				NodePtr temp(new DevideNode(l,r));
				return temp;
			}
	}
}

void ExpTree::makeTree(const std::string& str)
{
	Stack<NodePtr> nodeStack;
	Stack<char> opStack;
	opStack.push('@');
	std::string num;
	for (unsigned int i=0;i < str.size();++i)
	{
		if ('9'>=str[i] && str[i]>='0')
		{
			num+=str[i];
			continue;
		}
		if (num.size()>0)
		{
			NodePtr temp(new NumNode(atoi(num.c_str())));
			nodeStack.push(temp);
			num.clear();
		}
		if (str[i] == ' ') { continue; }

		switch (str[i])
		{
			case '(':
				opStack.push(str[i]);
				break;
			case ')':
				while (Precedence(opStack.peek())>0) 
				{
					NodePtr r=nodeStack.pop();
					NodePtr	l=nodeStack.pop();
					nodeStack.push(makeNode(opStack.pop(),l,r));
				}
				opStack.pop();
				break;
			case '+':case '-':case '*':case '/':
				while (Precedence(opStack.peek())>=Precedence(str[i]))
				{
					NodePtr r=nodeStack.pop();
					NodePtr	l=nodeStack.pop();
					nodeStack.push(makeNode(opStack.pop(),l,r));
				}
				opStack.push(str[i]);
				break;
			default:
				std::cerr << "illegal operator!\n";
				exit(1);
		}
	}

	if (num.size()>0)
	{
		NodePtr temp(new NumNode(atoi(num.c_str())));
		nodeStack.push(temp);
	}

	while (opStack.peek()!='@')
	{
		NodePtr r=nodeStack.pop();
		NodePtr	l=nodeStack.pop();
		nodeStack.push(makeNode(opStack.pop(),l,r));
	}


	if (nodeStack.size() != 1)
	{
		std::cerr << "illegal expression!\n";
		exit(2);
	}
	root=nodeStack.pop();

}

void Calculator::calculate()
{
	std::string expression;
	std::cout << "Enter the expression(q for quit): ";
	std::cin >> expression;
	if (expression == "q")
	{
		exit(0);
	}
	ExpTree expTree(expression);
	std::cout << "The result is : " << expTree.calculate() << std::endl;
}	


int main()
{
	Calculator calculator;
	calculator.loop();
}
