#include <future>
#include <iostream>
#include <chrono>
using namespace std;
namespace {
	
	int TestFunc(int x)
	{
		cout << "thread id=" << std::this_thread::get_id() << endl;
		int result = 0;
		for (int i = 0; i < x; i++) {
			result += 3;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		return result;
	}
} // namespace
void Test_share()
{
	std::future<int>        ret_data        = std::async([] { return 50; });
	std::shared_future<int> shared_ret_data = ret_data.share();
	try {
		// share()后，ret_data对象将变得无效,调用空指针
		std::cout << "ret_data valid: " << ret_data.valid() << endl;
		std::cout << "ret_data get: " << ret_data.get() << endl;

	} catch (const std::future_error& e) {
		// exception: std::future_error
		std::cout << "future_error : " << e.what() << std::endl;
	}
	//std::shared_future对象，get函数可以被多次访问
	std::cout << "value: " << shared_ret_data.get() << endl;
	std::cout << "its double: " << shared_ret_data.get() * 2 << endl;
}
void Test_valid_get()
{
	std::future<int> ret_data = std::async([] { return 50; });
	cout << ret_data.valid() << endl;//获取有效性
	cout << ret_data.get() << endl; //first get
	cout << ret_data.valid() << endl;//获取有效性
	try {
		std::cout << "ret_data get: " << ret_data.get() << endl; // second get
	} catch (const std::future_error& e) {
		// exception: std::future_error
		std::cout << "future_error : " << e.what() << std::endl;
	}
}
void Test_wait()
{
	cout << "thread id=" << std::this_thread::get_id() << " " << __FUNCTION__ << endl;
	std::future<int> ret_data = std::async(TestFunc, 5);
	std::cout << "wait..." << endl;
	ret_data.wait();
	std::cout << "ready..." << endl;
	std::cout << "ret_data get: " << ret_data.get() << endl; // second get
}
void Test_wait_()
{	
	/*
	enum class future_status { // names for timed wait function returns
    ready,
    timeout,
    deferred
	};
	*/
	int call_sum = 0;
	while (cin >> call_sum) {
		cout << "thread id=" << std::this_thread::get_id() << " " << __FUNCTION__ << endl;
		std::future<int> ret_data = std::async(TestFunc, call_sum);
		std::cout << "wait start" << endl;
		std::chrono::milliseconds span(200);
		std::future_status        ret_state = ret_data.wait_for(span);//获取状态
		//std::future_status        ret_state =
		//	ret_data.wait_until(std::chrono::system_clock::now() + std::chrono::milliseconds(200)); //获取状态,200ms后
		std::cout << "wait end state=" << static_cast<int>(ret_state) << endl;
		try {
			std::cout << "ret_data get: " << ret_data.get() << endl; // second get
		} catch (const std::future_error& e) {
			// exception: std::future_error
			std::cout << "future_error : " << e.what() << std::endl;
		}
	}	
}
int main_future()
{
	Test_share();
	cout << "======================================================" << endl;
	Test_valid_get();
	cout << "======================================================" << endl;
	Test_wait();
	cout << "======================================================" << endl;
	Test_wait_();
	cout << "======================================================" << endl;

	return 0;
}
