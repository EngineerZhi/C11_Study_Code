//#include <iostream>
//#include <string>
//#include <vector>
//using namespace std;
//
//class I_Image { //抽象的享元对象
//public:
//	virtual string GetKey() { return this->_Key; }
//	I_Image() {}
//	I_Image(string Key) { this->_Key = Key; }
//
//public:
//	string _Key;
//};
//
//class UserHeader : public I_Image { //具体化的对象
//public:
//	UserHeader(string Key)
//	{
//		this->_Key = Key;
//		cout << "UserHeader Build....." << Key << endl;
//	}
//	~UserHeader();
//};
//
//class ImageFactory {
//public:
//	ImageFactory() {}
//	~ImageFactory();
//	I_Image* GetFlyweight(const string& key)
//	{
//		vector<I_Image*>::iterator it = _header_.begin();
//		for (; it != _header_.end(); it++) {
//			if ((*it)->GetKey() == key) {
//				cout << key << " already created byusers...." << endl; //已经创建直接返回
//				return *it;
//			}
//		}
//		I_Image* fn = new UserHeader(key); //没有找到，创建对象返回
//		_header_.push_back(fn);
//		return fn;
//	}
//
//private:
//	vector<I_Image*> _header_; //用vector容器管理对象，也可以用哈希表
//};
//int main()
//{
//	ImageFactory* fc  = new ImageFactory();
//	I_Image*        fw1 = fc->GetFlyweight("hello");
//	I_Image*        fw2 = fc->GetFlyweight("world!");
//	I_Image*        fw3 = fc->GetFlyweight("hello");
//	return 0;
//}

#include <iostream>
#include <string>
#include <map>
using namespace std;

/* 抽象享元类 */
class I_Image {
public:
	virtual ~I_Image(){};
	virtual void OutPutImage() = 0;
};
/* 具体享元类 */
class UserHeader : public I_Image {
private:
	string str;

public:
	UserHeader(string str) { this->str = str; }
	void OutPutImage() { cout << "user header image is : " << str << endl; }
};
/* 享元工厂类 */
class ImageFactory {
private:
	map<string, std::shared_ptr<I_Image>> image_map_;

public:
	ImageFactory() {}
	std::shared_ptr<I_Image> GetImage(string obj)
	{
		std::shared_ptr<I_Image> item_image = nullptr;
		//如果没有找到对应的图片则创建
		if (image_map_.count(obj) == 0) {
			cout << "No find user header and Create Header= " << obj << endl;
			item_image = std::make_shared<UserHeader>(obj);
			image_map_.insert(std::map<std::string, std::shared_ptr<I_Image>>::value_type(obj, item_image));
		}
		return image_map_[obj];
	}
	int GetImageMapSize() { return image_map_.size(); }
};

int mainfly()
{
	std::shared_ptr<ImageFactory> image_factory = std::make_shared<ImageFactory>();
	std::shared_ptr<I_Image>      header_1      = image_factory->GetImage("zhangsan");
	std::shared_ptr<I_Image>      header_2      = image_factory->GetImage("lisi");
	std::shared_ptr<I_Image>      header_3      = image_factory->GetImage("zhangsan");
	std::shared_ptr<I_Image>      header_4      = image_factory->GetImage("xiaoming");
	std::shared_ptr<I_Image>      header_5      = image_factory->GetImage("xiaohong");
	std::shared_ptr<I_Image>      header_6      = image_factory->GetImage("lisi");
	cout << "======================================================"<< endl;
	cout << "image_factory size = " << image_factory->GetImageMapSize() << endl;
	cout << "======================================================" << endl;
	header_1->OutPutImage();
	header_2->OutPutImage();
	header_3->OutPutImage();
	header_4->OutPutImage();
	header_5->OutPutImage();
	header_6->OutPutImage();
	return 0;
}
