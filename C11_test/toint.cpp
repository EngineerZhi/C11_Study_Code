#include <iostream>
#include <thread>
#include <string>
using namespace std;
class People {
public:
	People(){};
	virtual ~People(){};
	virtual void OutputName() { 
		cout << __FUNCTION__ << " " << name << endl; 
	};

private:
	std::string name = "People";
};
class Student : public People{
public:
	Student(){};
	~Student(){};
	virtual void OutputName(){
		cout << __FUNCTION__ << " " << name << endl;
	};
	void StudentStudy() {
	}

private:
	std::string name = "Student";
};

class Teacher : public People {
public:
	Teacher(){};
	~Teacher(){};
	virtual void OutputName() {
		cout << __FUNCTION__ << " " << name << endl; 
	};

private:
	std::string name = "Teacher";
};


int main_to()
{
	People* p = new People();
	Student* s = new Student();
	Teacher* t = new Teacher();
	People*  pt = new Student();//基类指针指向派生类对象
	p->OutputName();
	s->OutputName();
	t->OutputName();
	pt->OutputName();
	cout << "======================================" << endl;
	People* p_1 = s;
	People* p_2 = dynamic_cast<People*>(s);
	p_1->OutputName();
	p_2->OutputName();
	cout << "======================================" << endl;
	Student* s_1 = (Student*)p;
	Student* s_2 = dynamic_cast<Student*>(p);
	Student* s_3 = dynamic_cast<Student*>(pt);
	Teacher* t_1 = dynamic_cast<Teacher*>(p);
	s_1->OutputName();
	if (s_2) {
		cout << "s_2 ptr =";
		s_2->OutputName();	
	}
	if (s_3) {
		cout << "s_3 ptr =";
		s_3->OutputName();
	}
	if (t_1) {
		cout << "t_1 ptr =";
		t_1->OutputName();
	}
	cout << "======================================" << endl;
	return 0;
}