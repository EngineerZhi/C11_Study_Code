#include <iostream> // std::cou
#include <map>
#include <functional>
using namespace std;
class CMapFunc {
public:
	typedef void (CMapFunc::*FUNC)(int a); //需要加上作用域限制

	CMapFunc(){
		func_map.insert(make_pair<string, FUNC>("FuncA", &CMapFunc::FuncA));
		func_map.insert(make_pair<string, FUNC>("FuncB", &CMapFunc::FuncB));
		func_map_c11.insert(make_pair<string, std::function<void(CMapFunc*, int)>>(
			"FuncA", &CMapFunc::FuncA));
		func_map_c11.insert(make_pair<string, std::function<void(CMapFunc*, int)>>(
			"FuncB", &CMapFunc::FuncB));
	};
	~CMapFunc(){};

	void CallFunc(string func_name, int value) {
		auto it = func_map.find(func_name);
		if (it != func_map.end()) {
			(this->*func_map[func_name])(value); 
		}
		
	}
	void CallFunc_c11(string func_name, int value){
		auto it_c11 = func_map_c11.find(func_name);
		if (it_c11 != func_map_c11.end()) {
			it_c11->second(this, value);
		}
	}

private:
	void FuncA(int value) { cout << "This is FuncA value=" << value << endl; }
	void FuncB(int value) { cout << "This is FuncB value=" << value << endl; }

private:
	map<string, std::function<void(CMapFunc*, int)>> func_map_c11;
	map<string, FUNC> func_map;
};

int mainfun()
{
	CMapFunc* test = new CMapFunc();
	test->CallFunc("FuncA", 26);
	test->CallFunc("FuncB", 27);
	test->CallFunc("FuncC", 27);
	test->CallFunc_c11("FuncA", 66);
	test->CallFunc_c11("FuncB", 67);
	test->CallFunc_c11("FuncC", 68);
	return 0;
}