#include <iostream>
#include <memory>
#include <string>
#include <list>
using namespace std;
class I_Phone {
public:
	virtual ~I_Phone(){};
	virtual void ShowFunction() = 0;
};

//三个手机
class XiaoMi : public I_Phone {
public:
	void ShowFunction() { cout << "This is XiaoMi Moblie Phone" << endl; }
};
class ViVo : public I_Phone {
public:
	void ShowFunction() { cout << "This is ViVo Moblie Phone" << endl; }
};
class Apple : public I_Phone {
public:
	void ShowFunction() { cout << "This is Apple Moblie Phone" << endl; }
};

class Decorator_5G : public I_Phone {
public:
	Decorator_5G(std::shared_ptr<I_Phone> phone) : i_phone_(phone) {}
	void ShowFunction()
	{
		i_phone_->ShowFunction();
		cout << "Function:5G" << endl;
	}
private:
	std::shared_ptr<I_Phone> i_phone_;
};

class Decorator_Camera : public I_Phone {
public:
	Decorator_Camera(std::shared_ptr<I_Phone> phone) : i_phone_(phone) {}
	void ShowFunction()
	{
		i_phone_->ShowFunction();
		cout << "Function:Camera" << endl;
	}
private:
	std::shared_ptr<I_Phone> i_phone_;
};

class Decorator_CloudService : public I_Phone {
public:
	Decorator_CloudService(std::shared_ptr<I_Phone> phone) : i_phone_(phone) {}
	void ShowFunction()
	{
		i_phone_->ShowFunction();
		cout << "Function:CloudService" << endl;
	}
private:
	std::shared_ptr<I_Phone> i_phone_;
};

int main_decorate()
{
	//最初只有三款手机
	std::shared_ptr<I_Phone> mi_    = std::make_shared<XiaoMi>();
	std::shared_ptr<I_Phone> vivo_  = std::make_shared<ViVo>();
	std::shared_ptr<I_Phone> apple_ = std::make_shared<Apple>();
	//XiaoMi公司给手机拓展的功能
	std::shared_ptr<I_Phone> mi_decorate_ = std::make_shared<Decorator_5G>(mi_);
	mi_decorate_                          = std::make_shared<Decorator_Camera>(mi_decorate_);
	mi_decorate_->ShowFunction();
	cout << endl;
	//vivo公司给手机拓展的功能
	std::shared_ptr<I_Phone> vivo_decorate_ = std::make_shared<Decorator_Camera>(vivo_);
	vivo_decorate_->ShowFunction();
	cout << endl;
	//Apple公司给手机拓展的功能
	std::shared_ptr<I_Phone> apple_decorate_ = std::make_shared<Decorator_Camera>(apple_);
	apple_decorate_                          = std::make_shared<Decorator_CloudService>(apple_decorate_);
	apple_decorate_                          = std::make_shared<Decorator_5G>(apple_decorate_);
	apple_decorate_->ShowFunction();
	cout << endl;


	return 0;
}
