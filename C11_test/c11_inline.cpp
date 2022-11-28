#include <iostream>
using namespace std;
class Base {
public:
	virtual ~Base() {}
	inline virtual void FuncName() { cout << "this is Base " << endl; }
};

class Derived : public Base {
public:
	inline virtual void FuncName() { cout << "this is Derived" << endl; }
};

int main_inline()
{
	// 编译器具有实际对象,所以它可以是内联的.
	Base b;
	b.FuncName();

	// 编译器具有对象的指针，呈现多态性，运行时期才能确定，所以不能内联。
	Base* p = new Derived();
	p->FuncName();

	delete p;
	p = nullptr;

	system("pause");
	return 0;
}