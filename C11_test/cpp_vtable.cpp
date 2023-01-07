#include <iostream>
using namespace std;

namespace {
	class VTBase {
	public:
		virtual void a() { cout << "VTBase::a()" << endl; }
		virtual void b() { cout << "VTBase::b()" << endl; }
		virtual void c() { cout << "VTBase::c()" << endl; }
		int          x, y;
	};

	class VTBaseExt : public VTBase {
	public:
		virtual void b() { cout << "VTBaseExt::b()" << endl; }
	};

	typedef long long Vtpr_type;
	typedef void (*VFunc)(void); //定义一个函数指针类型变量类型 VFunc

	void TestVFuncArr()
	{
		//offsetof
		VTBase vtbase;
		std::cout << sizeof(vtbase) << endl;
		cout << offsetof(VTBase, x) << endl;
		cout << offsetof(VTBase, y) << endl;
		/*
	x偏移为8，y偏移为12
	所以前8个字节为虚函数表的大小，也是该类的第一个成员变量
	*/
		VTBase* v_base = new VTBase();
		//将对象的首地址输出
		Vtpr_type* vptr = nullptr;
		//vptr是虚函数类的第一个成员变量,也是虚函数表的指针
		memcpy(&vptr, v_base, sizeof(Vtpr_type));
		//虚函数的地址存储在了虚函数表中，虚函数表地址内的值，为虚函数的指针
		VFunc funa = (VFunc)(*vptr);
		VFunc funb = (VFunc)(*(vptr + 1));
		VFunc func = (VFunc)(*(vptr + 2));
		funa();
		funb();
		func();
		delete v_base;
		v_base = nullptr;
	}

	void TestVtprValue()
	{
		VTBase*    v_base1 = new VTBase();
		VTBase*    v_base2 = new VTBase();
		Vtpr_type* vptr1   = nullptr;
		Vtpr_type* vptr2   = nullptr;
		memcpy(&vptr1, v_base1, sizeof(Vtpr_type));
		memcpy(&vptr2, v_base2, sizeof(Vtpr_type));
		cout << vptr1 << endl;
		cout << vptr2 << endl;
	}

	void TestVtbExt()
	{
		VTBase*    v_base    = new VTBase();
		Vtpr_type* vptr_base = nullptr;
		memcpy(&vptr_base, v_base, sizeof(Vtpr_type));
		cout << vptr_base << endl;

		VTBaseExt* v_base_ext = new VTBaseExt();
		Vtpr_type* vptr_ext   = nullptr;
		memcpy(&vptr_ext, v_base_ext, sizeof(Vtpr_type));
		cout << vptr_ext << endl;

		VFunc funa_ext = (VFunc)(*(vptr_ext));
		VFunc funb_ext = (VFunc)(*(vptr_ext + 1));
		VFunc func_ext = (VFunc)(*(vptr_ext + 2));
		funa_ext();
		funb_ext();
		func_ext();

		VFunc funa_base = (VFunc)(*(vptr_base));
		VFunc funb_base = (VFunc)(*(vptr_base + 1));
		VFunc func_base = (VFunc)(*(vptr_base + 2));
		funa_base();
		funb_base();
		func_base();
		//获取虚函数表数组地址
		for (int i = 0; i < 3; i++) {
			cout << *(vptr_base + i) << " " << *(vptr_ext + i) << endl;
		}

	}

	void TestVtbPointer() {
		//基类指针指向自己
		VTBase*    v_base    = new VTBase();
		Vtpr_type* vptr_base = nullptr;
		memcpy(&vptr_base, v_base, sizeof(Vtpr_type));
		cout << vptr_base << endl;
		//派生类指针指向派生类
		VTBaseExt* v_base_ext = new VTBaseExt();
		Vtpr_type* vptr_ext   = nullptr;
		memcpy(&vptr_ext, v_base_ext, sizeof(Vtpr_type));
		cout << vptr_ext << endl;
		//基类指针指向派生类
		VTBase*    v_base_to_ext = new VTBaseExt();
		Vtpr_type* vptr_to_ext   = nullptr;
		memcpy(&vptr_to_ext, v_base_to_ext, sizeof(Vtpr_type));
		cout << vptr_to_ext << endl;
	}
} // namespace

int main_vtable()
{
	//TestVFuncArr();
	//TestVtprValue();
	//TestVtbExt();
	TestVtbPointer();
	
	;
	return 0;
}