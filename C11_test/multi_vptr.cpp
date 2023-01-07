//base基类A
class A {
protected:
	int m_a;
};
//派生基类B
class B : virtual public A {
protected:
	int m_b;
};
//派生基类C
class C :  public A {
protected:
	int m_c;
};
//派生类D
class D :  public B,  public C {
public:
	void Set_a(int a) { 
	}
private:
	int m_d;
};

int main_vptr()
{
	D d;
	return 0;
}
