#include <iostream>
#include <memory>
#include <string>
#include <list>
using namespace std;
//节点的定义
class I_Component {
public:
	virtual ~I_Component() {}
	virtual void Add(std::shared_ptr<I_Component> cmpt){};
	virtual void Remove(std::shared_ptr<I_Component> cmpt){};
	virtual void Operation() = 0;
};

//输节点
class CompositeEntity : public I_Component {
public:
	CompositeEntity(const string& s) : name(s) {}
	virtual void Add(std::shared_ptr<I_Component> element) override {
		elements.push_back(element);
	}
	virtual void Remove(std::shared_ptr<I_Component> element) override {
		elements.remove(element);
	}
	virtual void Operation()
	{
		cout << name << endl;
		cout << "this is Composite has children size=" << elements.size() << endl;
		for (auto& leaf : elements) {
			cout << "chrild:";
			leaf->Operation();
		}
	}

private:
	string                             name;
	list<std::shared_ptr<I_Component>> elements;
};

//叶子节点
class LeafEntity : public I_Component {
public:
	LeafEntity(string s) : name(s) {}
	virtual void Operation(){
		cout << "this is leaf:" << name<< endl;
	}

private:
	string name;
};

//可以用了
//先写一个调用函数
static void ShowComponent(std::shared_ptr<I_Component> c)
{
	c->Operation();
	cout << "\r" << endl;
}

int main_component()
{
	std::shared_ptr<I_Component> pRoot = std::make_shared<CompositeEntity>("pRoot");

	std::shared_ptr<I_Component> pPart1 = std::make_shared<CompositeEntity>("pPart1");
	pPart1->Add(std::make_shared<LeafEntity>("Leaf1-1"));
	pPart1->Add(std::make_shared<LeafEntity>("Leaf1-2"));

	std::shared_ptr<I_Component> pPart2 = std::make_shared<CompositeEntity>("pPart2");
	std::shared_ptr<I_Component> pPart2_1 = std::make_shared<CompositeEntity>("pPart2_1");
	pPart2->Add(std::make_shared<LeafEntity>("Leaf2-1"));
	pPart2->Add(std::make_shared<LeafEntity>("Leaf2-2"));
	pPart2->Add(pPart2_1);

	std::shared_ptr<I_Component> leaf_999 = std::make_shared<LeafEntity>("leaf_999");
	pPart2_1->Add(leaf_999);
	pRoot->Add(pPart1);
	pRoot->Add(pPart2);

	//获取根节点下的数据
	ShowComponent(pRoot); 
	//获取某一个节点下的数据
	ShowComponent(pPart2_1);

	return 0;
}