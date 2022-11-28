#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>
using namespace std;
int AddFunc(int a, int b, int sleep)
{
	cout << "function thread id=" << std::this_thread::get_id() << endl;
	cout << __FUNCTION__ << " sleep begin " << std::this_thread::get_id() << endl;
	this_thread::sleep_for(chrono::seconds(sleep));
	cout << __FUNCTION__ << " sleep end " << std::this_thread::get_id() << endl;
	auto ret = a + b;
	cout << "thread id=" << std::this_thread::get_id() << " ret = " << ret << endl;
	return ret;
}

void TestBindRetFuture()
{
	{
		//当async返回值无绑定的future,指导执行完毕才开始新的async
		async(launch::async, AddFunc, 1, 2, 5);
		async(launch::async, AddFunc, 3, 4, 2);
		cout << "==========================================================" << endl;
	}
	{
		//绑定返回值,则多个async同时异步执行
		auto ret_future1 = async(launch::async, AddFunc, 1, 2, 5);
		auto ret_future2 = async(launch::async, AddFunc, 3, 4, 2);
		cout << "==========================================================" << endl;
	}
}

void TestLaunchPolicy()
{
	{
		//异步函数
		future<int> ret_future1 = async(launch::async, AddFunc, 1, 2, 2);
		cout << "main create async async" << endl;
		this_thread::sleep_for(chrono::seconds(1));
		cout << "main sleep_for end" << endl;
		int ret = ret_future1.get();
		cout << "async ret_future1=" << ret << endl;
		cout << "==========================================================" << endl;
	}
	{
		//同步函数,函数会在future.get()时才执行
		future<int> ret_future1 = async(launch::deferred, AddFunc, 1, 2, 2);
		cout << "main create async deferred" << endl;
		this_thread::sleep_for(chrono::seconds(1));
		cout << "main sleep_for end" << endl;
		int ret = ret_future1.get();
		cout << "deferred ret_future1=" << ret << endl;
		cout << "==========================================================" << endl;
	}
}
void TestClassFunc()
{
	class TmpClass {
	public:
		TmpClass(){};
		~TmpClass(){};
		int RetFuncAdd(int a, int b, int sleep = 0)
		{
			cout << "RetFuncAdd thread id=" << std::this_thread::get_id() << endl;
			cout << __FUNCTION__ << " sleep begin " << std::this_thread::get_id() << endl;
			this_thread::sleep_for(chrono::seconds(sleep));
			cout << __FUNCTION__ << " sleep end " << std::this_thread::get_id() << endl;
			obj_ret = a + b;
			cout << "thread id=" << std::this_thread::get_id() << " ret = " << obj_ret << endl;
			return obj_ret;
		}
		int GetObjRet() { return obj_ret; };

	private:
		int obj_ret;
	};

	TmpClass test_obj;
	//异步函数
	future<int> ret_future1 = async(launch::async, &TmpClass::RetFuncAdd, &test_obj,  1, 2, 2);
	cout << "main create async async" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "main sleep_for end" << endl;
	int ret = ret_future1.get();
	cout << "async ret_future1=" << ret << endl;
	cout << "TmpClass obj_ret=" << test_obj.GetObjRet() << endl;
	cout << "==========================================================" << endl;
}
int main_async()
{
	cout << "main thread id=" << std::this_thread::get_id() << endl;
	//TestBindRetFuture();
	//TestLaunchPolicy();
	TestClassFunc();
	return 0;
}