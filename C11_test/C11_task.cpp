#include <functional>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>
using namespace std;
namespace {
	int AddFunc(int a, int b, int sleep)
	{
		cout << "==========================================================" << endl;
		cout << "function thread id=" << std::this_thread::get_id() << endl;
		cout << __FUNCTION__ << " sleep begin " << std::this_thread::get_id() << endl;
		this_thread::sleep_for(chrono::seconds(sleep));
		cout << __FUNCTION__ << " sleep end " << std::this_thread::get_id() << endl;
		auto ret = a + b;
		cout << "thread id=" << std::this_thread::get_id() << " ret = " << ret << endl;
		cout << "==========================================================" << endl;
		return ret;
	}
} // namespace

void TestPackagedTask()
{
	std::packaged_task<int(int, int, int)> task(AddFunc);

	auto f1 = task.get_future();
	auto start = std::chrono::high_resolution_clock::now();
	task(1, 2, 3); //执行异步任务,如果不调用，则后续的f1.get()会一直阻塞，直到获取到结果
	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << "diff time " << std::chrono::duration<float>(stop - start).count() << endl;

	std::cout << f1.get() << std::endl;
}
void TestAsync()
{
	auto ret_future1 = std::async(std::launch::deferred, AddFunc, 1, 2, 3);
	auto start       = std::chrono::high_resolution_clock::now();
	auto result      = ret_future1.get();
	auto stop        = std::chrono::high_resolution_clock::now();
	std::cout << "diff time " << std::chrono::duration<float>(stop - start).count() << endl;
	std::cout << result << std::endl;
}
int main_task()
{

	TestAsync();
	TestPackagedTask();

	return 0;
}
