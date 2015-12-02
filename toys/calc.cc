#include<iostream>
#include<vector>
#include<string>
#include<sstream>
template<typename T>
class Stack {
public:
	void pop() {
		if (empty())
			return ;
		data.pop_back();
		--topstack;
	}
	const T& top() {
		return data[topstack];
	}
	void push(const T& item) {
		data.push_back(item);
		++topstack;
	}
	bool empty() {
		return topstack == -1 ? true : false;
	}

private:
	std::vector<T> data;
	int topstack = -1;
};

long str_to_num(const std::string& s) {  //字符串转长整形
	std::istringstream str(s);
	long num;
	str >> num;
	return num;
}

void expression(std::vector<std::string> &vec ,const std::string& s){   //构造中缀表达式
	std::string num;
	bool neg = false;               //判定是否负数
	for (auto iter = s.begin(); iter != s.end();/*空*/) {
		if (*iter >= 48 && 57 >= *iter) {
			num += *iter;
			++iter;
		}
		else if (*iter == '+' || *iter == '-' || *iter == '*' || *iter == '/') {
			if (num.size() != 0)
				vec.push_back(num);
			num = *iter;
			vec.push_back(num);
			num = "";
			++iter;
		}
		else if (*iter == '(') {                  //处理负数情况
			if (num.size() != 0) {
				vec.push_back(num);
				num = "";
			}
			if (*(++iter) == '-') {
				neg = true;
				num += '-';
				++iter;
			}
			else 
				vec.push_back("(");
		}
		else if (*iter == ')') {
			if (num.size() != 0) {
				vec.push_back(num);
				if (!neg)
					vec.push_back(")");
				num = "";
				++iter;
			}
		}
		else ++iter;
	}
	if (num.size() != 0)
		vec.push_back(num);
}

void postfix_exp(std::vector<std::string> &p_vec, std::vector<std::string> &vec) {   //构造后缀表达式
	Stack<std::string> sta;
	for (auto &oper : vec) {
		if (oper == "+" || oper == "-") {
			while (true) {
				if (sta.empty() || sta.top() == "(")
					break;
				p_vec.push_back(sta.top());
				sta.pop();
			}
			sta.push(oper);
		}
		else if (oper == "*" || oper == "/") {
			while (true) {
				if (sta.empty() || sta.top() == "+" ||
					sta.top() == "-" || sta.top() == "(")
					break;
				p_vec.push_back(sta.top());
				sta.pop();
			}
		    sta.push(oper);
		}
		else if (oper == ")") {
			while (true) {
				if (sta.top() == "(") {
					sta.pop();
					break;
				}
				p_vec.push_back(sta.top());
				sta.pop();
			}
		}
		else sta.push(oper);
	}
	while (!sta.empty()) {
		p_vec.push_back(sta.top());
		sta.pop();
	}
	std::cout << "The postfix-expression is : ";
	for (auto &row : p_vec)
		std::cout << row<<" ";
	std::cout << std::endl;
}

const long count(std::vector<std::string> &vec) {            //利用后缀表达式计算
	Stack<long> sta;
	for (auto &oper : vec) {
		long lhs = 0, rhs = 0;
		if (oper=="+") {
			rhs = sta.top();
			sta.pop();
			lhs = sta.top();
			sta.pop();
			sta.push(lhs + rhs);
		}
		else if (oper == "-") {
			rhs = sta.top();
			sta.pop();
			lhs = sta.top();
			sta.pop();
			sta.push(lhs - rhs);
		}
		else if (oper == "*") {
			rhs = sta.top();
			sta.pop();
			lhs = sta.top();
			sta.pop();
			sta.push(lhs * rhs);
		}
		else if (oper == "/") {
			rhs = sta.top();
			sta.pop();
			lhs = sta.top();
			sta.pop();
			sta.push(lhs / rhs);
		}
		else
			sta.push(str_to_num(oper));
	}
	if (!sta.empty())
		return sta.top();
	else
		return 0;
}

int main() {
	while (true) {
		std::string str;
		std::cout << "Enter the expression,or q for quit : ";
		std::cin >> str;
		if (str == "q")
			break;
		std::vector<std::string> exp;
		std::vector<std::string> p_exp;
		expression(exp, str);
		postfix_exp(p_exp, exp);
		std::cout << "The result is : " << count(p_exp) <<"."<< std::endl<<std::endl;
	}
}