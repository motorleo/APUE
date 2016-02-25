template<typename T>
class base
{
	friend T;
private:
	base() {}
	~base() {}
};

class sealed : virtual public base<sealed>
{
public:
	sealed() {}
	~sealed() {}
};

class inheritance : public sealed
{
public:
	inheritance() {}
	~inheritance() {}
};
int main()
{
}
