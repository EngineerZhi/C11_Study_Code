#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>

void GetCalcuSum(std::vector<int>::iterator begin, std::vector<int>::iterator end,
	std::promise<int> accumulate_promise)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	int total = std::accumulate(begin, end, 0); //自动求和
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	accumulate_promise.set_value(total);        // 提醒 future
}


void SimpleThreadData() {
	// 演示用 promise<int> 在线程间传递结果。
	std::vector<int>  numbers = {1, 2, 3, 4, 5, 6};
	std::promise<int> total_promise;
	std::future<int>  accumulate_future = total_promise.get_future(); //绑定
	std::thread       work_thread(GetCalcuSum, numbers.begin(), numbers.end(), std::move(total_promise));
	//std::future::get() 将等待直至该std::promise共享状态就绪
	std::cout << "result=" << accumulate_future.get() << std::endl;
	work_thread.join(); // wait for thread completion
}

void SimpleThreadEnd()
{
	auto sum_fun_exit = [&](std::vector<int>::iterator begin, std::vector<int>::iterator end,
			   std::promise<int> &accumulate_promise) {
		std::cout << "set_value_at_thread_exit" << std::endl;
		accumulate_promise.set_value_at_thread_exit(1000); // 提醒 future
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		std::cout << "thread_exit" << std::endl;
	};
	auto sum_fun_value = [&](std::vector<int>::iterator begin, std::vector<int>::iterator end,
				std::promise<int>& accumulate_promise) {
		std::cout << "set_value" << std::endl;
		accumulate_promise.set_value(999); // 对比
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		std::cout << "thread_exit" << std::endl;
	};
	std::vector<int>  numbers = {1, 2, 3, 4, 5, 6};
	std::promise<int> total_promise;
	std::future<int>  accumulate_future = total_promise.get_future(); //绑定
	std::thread       work_thread(sum_fun_value, numbers.begin(), numbers.end(), std::ref(total_promise));
	std::cout << "result=" << accumulate_future.get() << std::endl;
	work_thread.join(); // wait for thread completion
}

void SimpleBindOnce()
{
	// 演示只能与一个future绑定。
	std::vector<int>  numbers = {1, 2, 3, 4, 5};
	std::promise<int> total_promise;
	std::future<int>  total_future1 = total_promise.get_future(); //绑定
	try {
		std::future<int> total_future2 = total_promise.get_future(); //绑定
	} catch (const std::future_error& e) {
		std::cout << "future_error : " << e.what() << std::endl;
	}
}


int main_promise()
{
	SimpleThreadEnd();

	//SimpleThreadData();

	//SimpleBindOnce();
	return 0;
}