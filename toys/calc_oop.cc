#include <boost/shared_ptr.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>


class Node
{
public:
	virtual ~Node() {}
	
	virtual int calculate() const =0;

};

typedef boost::shared_ptr<Node> NodePtr;

class NumNode : public Node
{
public:
	NumNode(int num)
		:val(num){}

	int calculate() const { return val;}
	
private:
	int val;
};

class BinaryNode : public Node
{
public:
	BinaryNode(const NodePtr& l,const NodePtr& r)
		:left(l),right(r){}


protected:
	NodePtr left;
	NodePtr right;
};

class AddNode : public BinaryNode
{
public:
	AddNode(const NodePtr& l,const NodePtr& r)
		:BinaryNode(l,r) {}
	int calculate() const { return left->calculate()+right->calculate();}
};

class MinusNode : public BinaryNode
{
public:
	MinusNode(const NodePtr& l,const NodePtr& r)
		:BinaryNode(l,r) {}
	int calculate() const { return left->calculate()-right->calculate();}
};

class MultiplyNode : public BinaryNode
{
public:
	MultiplyNode(const NodePtr& l,const NodePtr& r)
		:BinaryNode(l,r) {}
	int calculate() const { return left->calculate()*right->calculate();}
};

class DevideNode : public BinaryNode
{
public:
	DevideNode(const NodePtr& l,const NodePtr& r)
		:BinaryNode(l,r) {}
	int calculate() const { return left->calculate()/right->calculate();}
};

template <typename T>
class Stack
{
public:
	void push(const T& t) { stack.push_back(t);}

	T pop()
	{
		T temp=stack.back();
		stack.pop_back();
		return temp;
	}

	const T& peek() { return stack.back();}

	int size() { return stack.size();}

private:
	std::vector<T> stack;
};

class ExpTree
{
public:
	ExpTree(const std::string& str) { makeTree(str);}

	int calculate() {return root->calculate();}

private:
	int Precedence(const char op)
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

	NodePtr makeNode(const char op,const NodePtr& l,const NodePtr& r)
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

	void makeTree(const std::string& str)
	{
		Stack<NodePtr> nodeStack;
		Stack<char> opStack;
		opStack.push('@');
		std::string num;
		for (int i=0;i < str.size();++i)
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
					while (Precedence(opStack.peek())>0) //pop all operator
					{
						nodeStack.push(
								makeNode(opStack.pop(),nodeStack.pop(),nodeStack.pop()));
					}
					opStack.pop();
					break;
				case '+':case '-':case '*':case '/':
					while (Precedence(opStack.peek())>=Precedence(str[i]))
					{
						nodeStack.push(
								makeNode(opStack.pop(),nodeStack.pop(),nodeStack.pop()));
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
			nodeStack.push(
					makeNode(opStack.pop(),nodeStack.pop(),nodeStack.pop()));
		}


		if (nodeStack.size() != 1)
		{
			std::cerr << "illegal expression!\n";
			exit(2);
		}
		root=nodeStack.pop();
		
	}
						
	NodePtr root;
};

class Calculator
{
public:
	void loop()
	{
		while (true)
		{
			calculate();
		}
	}

private:
	void calculate()
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
};


int main()
{
	Calculator calculator;
	calculator.loop();
}
