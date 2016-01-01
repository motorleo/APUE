#include <boost/shared_ptr.hpp>
#include <vector>
#include <string>
#include <deque>
//#include <list> 

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
	std::deque<T> stack;
};

class ExpTree
{
public:
	ExpTree(const std::string& str) { makeTree(str);}

	int calculate() {return root->calculate();}

private:
	int Precedence(const char op);
	NodePtr makeNode(const char op,const NodePtr& l,const NodePtr& r);
	
	void makeTree(const std::string& str);
							
	NodePtr root;
};

class Calculator
{
public:
	void loop()	{ while (true){ calculate();} }

private:
	void calculate();
};


