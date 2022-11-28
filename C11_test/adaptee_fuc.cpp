#include <iostream>
#include <memory>


class Charge {
public:
	virtual ~Charge() = default;
	virtual std::string StartCharge() const { 
		return "this is Universal charger"; 
	}
};

class AppleCharge {
public:
	std::string StartQuickCharge() const { 
		return "this is apple charge"; 
	}
};

class AdapterApple : public Charge {
private:
	std::shared_ptr<AppleCharge> apple_;
public:
	AdapterApple(std::shared_ptr<AppleCharge> apple) : apple_(apple) {}
	std::string StartCharge() const override{
		std::string apple_charge = this->apple_->StartQuickCharge();
		return "Adapter:" + apple_charge + " line";
	}
};

void GoCharge(const std::shared_ptr<Charge> target)
{
	std::cout << target->StartCharge()<<std::endl;
}

int main_adaptee()
{
	std::shared_ptr<Charge> target = std::make_shared<Charge>();
	GoCharge(target);

	std::shared_ptr<AppleCharge> apple = std::make_shared<AppleCharge>();
	std::cout << "charge object: " << apple->StartQuickCharge() << std::endl;

	std::shared_ptr<AdapterApple> apple_line = std::make_shared<AdapterApple>(apple);
	GoCharge(apple_line);

	return 0;
}