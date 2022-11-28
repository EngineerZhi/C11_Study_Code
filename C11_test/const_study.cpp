#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
class A {
private:
	const int a; // 常对象成员，只能在初始化列表赋值

public:
	// 构造函数
	A() : a(0){};
	A(int x) : a(x){}; // 初始化列表

	// const可用于对重载函数的区分
	int getValue();       // 普通成员函数
	int getValue() const; // 常成员函数，不得修改类中的任何数据成员的值
};

void function()
{
	// 对象
	A        b;      // 普通对象，可以调用全部成员函数、更新常成员变量
	const A  a;      // 常对象，只能调用常成员函数
	const A* p = &a; // 指针变量，指向常对象
	const A& q = a;  // 指向常对象的引用

	// 指针
	char  greeting[] = "Hello";
	char* p1         = greeting; // 指针变量，指向字符数组变量
	const char* p2 = greeting; // 指针变量，指向字符数组常量（const 后面是 char，说明指向的字符（char）不可改变）
	char* const p3 = greeting; // 自身是常量的指针，指向字符数组变量（const 后面是 p3，说明 p3 指针自身不可改变）
	const char* const p4 = greeting; // 自身是常量的指针，指向字符数组常量
}

class MyClass {
public:
	MyClass(){};
	~MyClass(){};
	void Update_const(const int& p) const
	{
		//i_data++;
	}
	void      Update(const int& p) { i_data++; }
	const int const_Update() { return i_data++; }
	int       _Update() { return i_data++; }

private:
	int i_data = 9;
};

void Update_const(const MyClass& p)
{
	int in_x = 10;
	p.Update_const(in_x);
	//std::cout << p.Update_const(in_x) << std::endl;
	std::cout << &p << std::endl;
}
void Update(MyClass& p)
{
	std::cout << p.const_Update() << std::endl;
	//std::cout << &p << std::endl;
	//p++;
	//std::cout << p << std::endl;
	std::cout << &p << std::endl;
}

const int const_g_Update()
{
	return 10;
}
int g_Update()
{
	return 10;
}
//// 函数
//void function1(const int Var);   // 传递过来的参数在函数内不可变
//void function2(const char* Var); // 参数指针所指内容为常量
//void function3(char* const Var); // 参数指针为常量
//void function4(const int& Var);  // 引用参数在函数内为常量
//
//// 函数返回值
//const int  function5(); // 返回一个常数
//const int* function6(); // 返回一个指向常量的指针变量，使用：const int *p = function6();
//int* const function7(); // 返回一个指向变量的常指针，使用：int* const p = function7();

#include <iostream>
class Test_Class {
private:
	int a = 9;

public:
	Test_Class() { std::cout << __FUNCTION__ << " a=" << a << std::endl; };
	int GetValueA()
	{
		std::cout << __FUNCTION__ << std::endl;
		a++;
		return a;
	};
	int GetValueBConst() const
	{
		std::cout << __FUNCTION__ << std::endl;
		//a++;//错误，常量函数不可修改成员变量
		return a;
	};
};

const char* Const_TestFun()
{
	char* array = new char[4];
	array[0]    = 'a';
	array[1]    = 'b';
	array[2]    = 'c';
	array[3]    = '\0';
	return array;
}

char* TestFun()
{
	char* array = new char[4];
	array[0]    = 'a';
	array[1]    = 'b';
	array[2]    = 'c';
	array[3]    = '\0';
	return array;
}

int const_main() {
	//const char* s = Const_TestFun();
	//char*       p = TestFun();
	////*s  = 'n';错误，不能修改返回值
	//cout << s << endl;
	//*p = 'n';
	//cout << p << endl;
	//Test_Class t_class; //普通对象，可以调用全部成员函数
	//std::cout << t_class.GetValueA() << std::endl;
	//std::cout << t_class.GetValueBConst() << std::endl;

	int        a     = 10;
	int        b     = 20;
	int        e     = 40;
	const int* d_ptr = &b; //常量指针
	cout << "d_ptr:" << d_ptr << " " << *d_ptr << " " << b << endl;
	//*d_ptr=20; 不能通过常量指针来修改变量的值
	b     = 30; //可以通过修改常量指针指向的对象值 来修改常量指针的值
	d_ptr = &e; //同时常量指针可以指向任意其他地址
	cout << "after d_ptr:" << d_ptr << " " << *d_ptr << " " << b << endl;

	int* const ptr_c = &a; //指针常量
	cout << "ptr_c:" << ptr_c << " " << *ptr_c << " " << a << endl;
	//ptr_c=&e; 对于指针常量 不能修改其指向的地址
	*ptr_c = 15; //但是可以通过指针来修改变量的值
	cout << "after ptr_c:" << ptr_c << " " << *ptr_c << " " << a << endl;
	return 0;
}
