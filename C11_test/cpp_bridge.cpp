
#include <iostream>
#include <memory>
#include <list>
class I_SoftWare {
public:
	virtual ~I_SoftWare(){};
	virtual void RunApp() = 0;
};

class StreamLiveApp : public I_SoftWare {
public:
	void RunApp() {
		std::cout << " Start Live APP " << std::endl; 
	}
};
class IMChatApp : public I_SoftWare {
public:
	void RunApp() { 
		std::cout << " Start Chat APP " << std::endl; 
	}
};
class GameApp : public I_SoftWare {
public:
	void RunApp() { std::cout << " Start Game APP " << std::endl; }
};

class I_OperatingSystem {
protected:
	std::list<std::shared_ptr<I_SoftWare>> soft_list_;

public:
	virtual ~I_OperatingSystem(){};
	virtual void InstallApp(std::shared_ptr<I_SoftWare> ptrSoft) {
		soft_list_.push_back(ptrSoft);
	}
	virtual void StartApp() = 0;

};
//Win10
class Windows10_OS : public I_OperatingSystem {
public:
	void StartApp()
	{
		std::cout << "Windows 10 run App:"<<std::endl;
		for (auto& ptr : soft_list_) {
			ptr->RunApp();
		}
	}
};
//win7
class Windows7_OS : public I_OperatingSystem {
public:
	void StartApp()
	{
		std::cout << "Windows 7 run App:" << std::endl;
		for (auto& ptr : soft_list_) {
			std::cout << "run App with Animation:";
			ptr->RunApp();
		}
	}
};


void SystemRunApp(std::shared_ptr<I_OperatingSystem> os) {
	std::shared_ptr<I_SoftWare> live_app = std::make_shared<StreamLiveApp>();
	std::shared_ptr<I_SoftWare> chat_app = std::make_shared<IMChatApp>();
	os->InstallApp(live_app);
	os->InstallApp(chat_app);
	os->StartApp();
}

int main_bridge()
{
	std::shared_ptr<I_OperatingSystem> system1 = std::make_shared<Windows10_OS>();
	SystemRunApp(system1);
	std::cout << "================================" << std::endl; 
	std::shared_ptr<I_OperatingSystem> system2 = std::make_shared<Windows7_OS>();
	SystemRunApp(system2);
	std::cout << "================================" << std::endl; 
	system1->InstallApp(std::make_shared<GameApp>());
	system1->StartApp();
	system("pause");
	return 0;
}
