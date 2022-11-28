#include <iostream>
#include <thread>
#include <future>
using namespace std;
int TestFunc(int a, int b){
	cout << "thread id=" << std::this_thread::get_id() << " " << __FUNCTION__ << endl;
	int result = 0;
	for (int i = a; i < b; i++) {
		result += 3;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return result;
}

void task_func()
{
	cout << "thread id=" << std::this_thread::get_id() << " " << __FUNCTION__ << endl;
	//包装普通函数
	//std::packaged_task<int(int, int)> task(TestFunc);
	std::packaged_task<int()>         task(std::bind(TestFunc, 33, 66));
	future<int>result = task.get_future();
	//启动任务，同步执行
	//task(33, 66);
	task();
	cout << "task_func TestFunc(33, 66) :" << result.get() << " " << __FUNCTION__ << endl;
}

void task_thread() 
{
	cout << "thread id=" << std::this_thread::get_id() << " " << __FUNCTION__ << endl;
	//构造时传递用于异步执行的函数指针add
	packaged_task<int(int, int)> ansyc_task(TestFunc);
	//future模板参数类型为函数add的返回值类型
	future<int> future = ansyc_task.get_future();
	//创建线程，同时传递函数TestAdd的运行参数
	thread exec_thread(move(ansyc_task), 33, 66);
	//获得函数packaged_task在另一个线程中的运行结果
	int ret = future.get();
	exec_thread.join();
	cout << "TestFunc(1,20)=" << ret << " " << __FUNCTION__ << endl;
}

void task_lambda()
{
	cout << "thread id=" << std::this_thread::get_id() << " " << __FUNCTION__ << endl;
	//包装目标为lambda
	packaged_task<int(int, int)> task([](int a, int b) { return a + b; });
	//仿函数形式，启动任务
	task(33, 66);
	future<int> result = task.get_future();
	cout << "task_lambda (33, 66) :" << result.get() << " " << __FUNCTION__ << endl;
}

int mainpackaged_task()
{
	//task_func();
	//task_lambda();
	task_thread();
	return 0;
}