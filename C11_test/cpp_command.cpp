#include<iostream>
#include <memory>
#include <vector>
using namespace std;

class Command {
public:
	virtual ~Command() {}
	virtual void Execute() const = 0;
};
class Receiver {
public:
	virtual void DoSomething(const int a)     = 0;
	virtual void DoSomethingElse(const int b) = 0;
};


/*实例化一个厨师类的处理人*/
class CookReceiver : public Receiver {
public:
	explicit CookReceiver(const std::string& cook_name) : cook_name_(cook_name) {}
	void DoSomething(const int a) { 
		std::cout << "->cook " << cook_name_ << " Receiver: Working sum= " << a << std::endl;
	}
	void DoSomethingElse(const int b)
	{
		std::cout << "->cook " << cook_name_ << "  Receiver: Working food weight=" << b << std::endl;
	}

private:
	std::string cook_name_;
};

class MilkCommand : public Command {
private:
	int sum_;
public:
	MilkCommand(int sum) : sum_(sum) {}
	void Execute() const override { std::cout << "->The customer need milk= " << this->sum_ << std::endl; }
};
/*实例化一条复杂的命令*/
class SteakCommand : public Command {

public:
	explicit SteakCommand(std::shared_ptr<Receiver> receiver_cook, int sum, int weight)
		: sum_(sum), weight_(weight), receiver_cook_(receiver_cook)
	{
	}
	void Execute() const override
	{
		std::cout << "->The customer ordered a steak" << std::endl;
		this->receiver_cook_->DoSomething(this->sum_);
		this->receiver_cook_->DoSomethingElse(this->weight_);
	}

private:
	std::shared_ptr<Receiver> receiver_cook_;
	int                       sum_    = 0;
	int                       weight_ = 0;
};
/*饭店前台*/
class Invoker {
private:
	vector<std::shared_ptr<Command>> command_list_;

public:
	~Invoker() { command_list_.clear(); }
	void InsertFontCommand(std::shared_ptr<Command> command) { command_list_.insert(command_list_.begin(), command); }
	void PushBackCommand(std::shared_ptr<Command> command) { command_list_.push_back(command); }
	void ExecuteCommand()
	{
		std::cout << "The customer order start execute!" << std::endl;
		for (auto& item_command : command_list_) {
			item_command->Execute();
		}
		std::cout << "The customer order finished!" << std::endl;
	}
};
int main()
{
	//饭店前台
	auto invoker            = std::make_shared<Invoker>();
	//创建厨师小明
	auto receiver_cook_user = std::make_shared<CookReceiver>("xiao ming");
	//订购牛排并指定小明厨师制作
	invoker->PushBackCommand(make_shared<SteakCommand>(receiver_cook_user, 5, 100));
	//订购牛奶
	invoker->InsertFontCommand(std::make_shared<MilkCommand>(int(5)));
	//执行订单
	invoker->ExecuteCommand();
	return 0;
}