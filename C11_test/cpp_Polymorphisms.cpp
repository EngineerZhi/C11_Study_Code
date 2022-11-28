#include <iostream>
#include <memory>
using namespace std;
class SoftWare {
public:
	SoftWare(){};
	virtual ~SoftWare() { 
		std::cout << __FUNCTION__ << std::endl; 
	};
	//运行期多态
	virtual void RunApp() { std::cout << " Interface SoftWare " << std::endl; };
};

class ChatApp : public SoftWare {
public:
	ChatApp(){};
	~ChatApp() { 
		std::cout << __FUNCTION__ << std::endl; 
	};
	void RunApp() { std::cout << " Start Chat APP " << std::endl; }
};

int main_virtual()
{
	SoftWare* app = new ChatApp();
	std::cout << "================================" << std::endl;
	app->RunApp();
	delete app;
	app = nullptr;
	std::cout << "================================" << std::endl;
	return 0;
}

#include <iostream>
#include <memory>
using namespace std;
class I_SoftWare {
public:
	virtual ~I_SoftWare(){};
	//运行期多态
	virtual void RunApp() { std::cout << " Interface SoftWare " << std::endl; };
	//编译器多态
	void BaseName() { std::cout << " I am Interface SoftWare " << std::endl; };
	//参数多态
	void RunTime(int run_time) { std::cout << __FUNCTION__ << " int= " << run_time << std::endl; }
	void RunTime(double run_time) { std::cout << __FUNCTION__ << " double= " << run_time << std::endl; }
	void RunTime(int run_time1, int run_time2)
	{
		std::cout << __FUNCTION__ << " run_time1= " << run_time1 << " run_time2= " << run_time2 << std::endl;
	}
	string RunTime(string a, string b)
	{
		std::string result(a);
		result += b;
		std::cout << __FUNCTION__ << " string= " << result << std::endl;
		return result;
	}
};
class StreamLiveApp : public I_SoftWare {
public:
	//重写
	void RunApp() { std::cout << " Start Live APP " << std::endl; }
	//重定义(隐藏父类的方法)
	void BaseName() { std::cout << " I am StreamLiveApp " << std::endl; };
};
class IMChatApp : public I_SoftWare {
public:
	//重写
	void RunApp() { std::cout << " Start Chat APP " << std::endl; }
};

int main_v()
{
	StreamLiveApp obj_live_app;
	IMChatApp     obj_chat_app;

	std::shared_ptr<I_SoftWare> live_app = std::make_shared<StreamLiveApp>();
	std::shared_ptr<I_SoftWare> chat_app = std::make_shared<IMChatApp>();
	std::cout << "================================" << std::endl;
	//1. 同名函数不同的参数列表：参数多态(编译时确定)
	live_app->RunTime(99);
	live_app->RunTime(3.14);
	live_app->RunTime(99, 1);
	std::cout << "================================" << std::endl;
	//2 .重载多态(编译时确定)
	//重定义：
	obj_live_app.BaseName();
	obj_chat_app.BaseName();
	//同一个类中重载方法，
	obj_live_app.RunTime("N", "B");
	obj_live_app.RunTime(1, 2);
	//指针不可以
	live_app->BaseName();
	chat_app->BaseName();
	std::cout << "================================" << std::endl;
	//3. 虚函数重写：子类型多态
	live_app->RunApp();
	chat_app->RunApp();
	std::cout << "================================" << std::endl;
	//4. 强制多态
	double a= 6;
	int    b = 3.14;
	cout << "a=" << a << " b=" << b << endl;
	return 0;
}