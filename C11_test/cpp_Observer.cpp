#include <iostream>
#include <list>
#include <string>
//====================================抽象接口======================================
class I_Observer {
public:
	virtual ~I_Observer(){};
	virtual void Update(const std::string& message_from_subject) = 0;
};

class I_Subject {
public:
	virtual ~I_Subject(){};
	virtual void Attach(std::shared_ptr<I_Observer> observer) = 0;
	virtual void Detach(std::shared_ptr<I_Observer> observer) = 0;
	virtual void Notify()                                     = 0;
};
//====================================被观察者======================================
class Subject : public I_Subject {
public:
	virtual ~Subject() { std::cout << "Subject delete" << std::endl; }

	void Attach(std::shared_ptr<I_Observer> observer) override { list_observer_.emplace_back(observer); }
	void Detach(std::shared_ptr<I_Observer> observer) override { list_observer_.remove(observer); }
	void Notify() override
	{
		OutObserverCount();
		for (auto& iterator : list_observer_) {
			iterator->Update(message_);
		}
	}

	void CreateMessage(std::string message = "NULL msg")
	{
		this->message_ = message;
		Notify();
	}
	void OutObserverCount() { std::cout << "There are " << list_observer_.size() << " observers in the list." << std::endl; }

private:
	std::list<std::shared_ptr<I_Observer>> list_observer_;
	std::string                            message_;
};

//====================================Android系统观察者======================================
class ObserverAndroid : public I_Observer {
public:
	ObserverAndroid(std::string name) : name_(name) {}
	virtual ~ObserverAndroid() { std::cout << name_ << " I was the Observer delete " << std::endl; }

	void Update(const std::string& message_from_subject) override
	{
		message_from_subject_ = message_from_subject;
		PrintInfo();
	}

private:
	void PrintInfo() { std::cout << name_ << std::endl; }

private:
	std::string message_from_subject_;
	std::string name_;
};
//====================================苹果系统观察者======================================
class ObserverApple : public I_Observer {
public:
	ObserverApple(std::string name) : name_(name) {}
	virtual ~ObserverApple() { std::cout << name_ << " Apple was the Observer delete " << std::endl; }

	void Update(const std::string& message_from_subject) override
	{
		message_from_subject_ = message_from_subject;
		PrintInfo();
	}

private:
	void PrintInfo() { std::cout << name_ << " IOS NB" << std::endl; }

private:
	std::string message_from_subject_;
	std::string name_;
};
//====================================测试======================================
void ClientCode()
{
	//创建被观察者
	std::shared_ptr<Subject> subject = std::make_shared<Subject>();
	//创建两个观察者并注册
	std::shared_ptr<ObserverAndroid> observer_xiaomi = std::make_shared<ObserverAndroid>("xiaomi");
	subject->Attach(observer_xiaomi);
	std::shared_ptr<ObserverAndroid> observer_vivo = std::make_shared<ObserverAndroid>("Vivo");
	subject->Attach(observer_vivo);

	//被观察者发布消息
	subject->CreateMessage("Hello World!");
	//移除一个被观察者并发布新消息
	subject->Detach(observer_vivo);
	subject->CreateMessage("Android NB");

	//创建一个新的观察者并注册
	std::shared_ptr<ObserverApple> observer_apple = std::make_shared<ObserverApple>("Apple phone");
	subject->Attach(observer_apple);
	//发布新消息
	subject->CreateMessage("Mobile NB");

	std::cout << std::endl;
}

int main_observer()
{
	ClientCode();
	return 0;
}