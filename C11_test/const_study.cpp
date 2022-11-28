#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
class A {
private:
	const int a; // �������Ա��ֻ���ڳ�ʼ���б�ֵ

public:
	// ���캯��
	A() : a(0){};
	A(int x) : a(x){}; // ��ʼ���б�

	// const�����ڶ����غ���������
	int getValue();       // ��ͨ��Ա����
	int getValue() const; // ����Ա�����������޸����е��κ����ݳ�Ա��ֵ
};

void function()
{
	// ����
	A        b;      // ��ͨ���󣬿��Ե���ȫ����Ա���������³���Ա����
	const A  a;      // ������ֻ�ܵ��ó���Ա����
	const A* p = &a; // ָ�������ָ�򳣶���
	const A& q = a;  // ָ�򳣶��������

	// ָ��
	char  greeting[] = "Hello";
	char* p1         = greeting; // ָ�������ָ���ַ��������
	const char* p2 = greeting; // ָ�������ָ���ַ����鳣����const ������ char��˵��ָ����ַ���char�����ɸı䣩
	char* const p3 = greeting; // �����ǳ�����ָ�룬ָ���ַ����������const ������ p3��˵�� p3 ָ�������ɸı䣩
	const char* const p4 = greeting; // �����ǳ�����ָ�룬ָ���ַ����鳣��
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
//// ����
//void function1(const int Var);   // ���ݹ����Ĳ����ں����ڲ��ɱ�
//void function2(const char* Var); // ����ָ����ָ����Ϊ����
//void function3(char* const Var); // ����ָ��Ϊ����
//void function4(const int& Var);  // ���ò����ں�����Ϊ����
//
//// ��������ֵ
//const int  function5(); // ����һ������
//const int* function6(); // ����һ��ָ������ָ�������ʹ�ã�const int *p = function6();
//int* const function7(); // ����һ��ָ������ĳ�ָ�룬ʹ�ã�int* const p = function7();

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
		//a++;//���󣬳������������޸ĳ�Ա����
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
	////*s  = 'n';���󣬲����޸ķ���ֵ
	//cout << s << endl;
	//*p = 'n';
	//cout << p << endl;
	//Test_Class t_class; //��ͨ���󣬿��Ե���ȫ����Ա����
	//std::cout << t_class.GetValueA() << std::endl;
	//std::cout << t_class.GetValueBConst() << std::endl;

	int        a     = 10;
	int        b     = 20;
	int        e     = 40;
	const int* d_ptr = &b; //����ָ��
	cout << "d_ptr:" << d_ptr << " " << *d_ptr << " " << b << endl;
	//*d_ptr=20; ����ͨ������ָ�����޸ı�����ֵ
	b     = 30; //����ͨ���޸ĳ���ָ��ָ��Ķ���ֵ ���޸ĳ���ָ���ֵ
	d_ptr = &e; //ͬʱ����ָ�����ָ������������ַ
	cout << "after d_ptr:" << d_ptr << " " << *d_ptr << " " << b << endl;

	int* const ptr_c = &a; //ָ�볣��
	cout << "ptr_c:" << ptr_c << " " << *ptr_c << " " << a << endl;
	//ptr_c=&e; ����ָ�볣�� �����޸���ָ��ĵ�ַ
	*ptr_c = 15; //���ǿ���ͨ��ָ�����޸ı�����ֵ
	cout << "after ptr_c:" << ptr_c << " " << *ptr_c << " " << a << endl;
	return 0;
}
