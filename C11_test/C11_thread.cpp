#include<iostream>
#include <thread>
#include <mutex>
#include "signalcpp.h"
using namespace std;
class MsgInstanceServerNoGc {
public:
	static MsgInstanceServerNoGc* instance(){
		if (m_Instance == nullptr) {
			std::lock_guard<std::mutex> lck(m_Mutex);
			if (m_Instance == nullptr) {
				m_Instance = new MsgInstanceServerNoGc();
			}
		}
		return m_Instance;
	};
	const std::string GetToken()
	{
		std::cout << __FUNCTION__ << std::endl;
		return std::string("123+token");
	};

private:
	explicit MsgInstanceServerNoGc(){ 
		std::cout << __FUNCTION__ << std::endl;
	};
	//·À¿½±´
	MsgInstanceServerNoGc(MsgInstanceServerNoGc const&)         = delete;
	MsgInstanceServerNoGc& operator==(const MsgInstanceServerNoGc&) = delete;
	~MsgInstanceServerNoGc(){ 
		std::cout << __FUNCTION__ << std::endl;
	};

	static MsgInstanceServerNoGc* m_Instance; //ÀàµÄÖ¸Õë
	static std::mutex         m_Mutex;
};
MsgInstanceServerNoGc* MsgInstanceServerNoGc::m_Instance = nullptr;
std::mutex MsgInstanceServerNoGc::m_Mutex;

int main2()
{
	//auto ret = MsgInstanceServerNoGc::instance()->GetToken();
	//std::cout << ret << std::endl;

	//auto ret_ = MsgInstanceServer::instance()->GetToken();
	//std::cout << ret_ << std::endl;
	return 0;

}

//void TestFunc1(int input)
//{
//
//	mutex_.lock();
//	for (int i = 0; i < input; i++) {
//		mutex_.lock();
//		counter_++;
//		std::this_thread::sleep_for(chrono::milliseconds(10));
//		cout << "thread id=" << std::this_thread::get_id() << "counter_ =" << counter_ << endl;
//		mutex_.unlock();
//	}
//	mutex_.unlock();
//}

//int main()
//{
//	cout << "main thread id=" << std::this_thread::get_id() << endl;
//	thread thread_1 = std::thread(TestFunc1,200);
//	thread thread_2 = std::thread(TestFunc1, 200);
//	thread_1.join();
//	thread_2.join();
//	cout << "thread id=" << std::this_thread::get_id() << "counter_ =" << counter_ << endl;
//}

//int g_index = 99;
//class ClassFunc {
//public:
//	void hello() {
//		std::cout << "ClassFunc Hello  World!  "
//			  <<"thread id="<< std::this_thread::get_id()  << std::endl; 
//	}
//};
//
//void NoParamDone() 
//{
//	//cout << "thread id=" << std::this_thread::get_id() << endl;
//	//cout << "World!" << endl; 
//	std::chrono::milliseconds dura(25);
//	for (int i = 0; i <20; i++) {
//		cout << "thread id=" << std::this_thread::get_id() << "index=" << i << endl;
//		std::this_thread::sleep_for(dura);
//	}
//
//}
//void HaveParamDone(int a,int b)
//{
//	cout << "thread id=" << std::this_thread::get_id() << endl;
//	cout << "World!"<< " " << a << " " << b << endl;
//}
//int main()
//{
//	cout << "main thread id=" << std::this_thread::get_id() << endl;
//	//thread thread_lambda([] { 
//	//	cout << "thread id="<<std::this_thread::get_id()<<endl;
//	//	cout << "Hello" <<endl; 
//	//});
//	//thread thread_nor1(NoParamDone);
//	//thread thread_nor2(HaveParamDone, 66, 77);
//
//	//{
//	//	ClassFunc   class_func;
//	//	std::thread t_class(&ClassFunc::hello, &class_func);
//	//	t_class.join();
//	//}
//	//thread_lambda.join();
//	//thread_nor1.join();
//	//thread_nor2.join();
//
//	thread thread_nor1(NoParamDone);
//	thread_nor1.join();
//	std::chrono::milliseconds dura(25);
//	for (int i = 0; i < 20; i++) {
//		cout << "main thread id=" << std::this_thread::get_id() << "index=" << i << endl;
//		//std::this_thread::sleep_for(dura);
//	}
//
//	system("pause");
//}