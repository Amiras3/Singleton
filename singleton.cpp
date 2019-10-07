#include <iostream>
#include <atomic>
#include <utility>
#include <mutex>

using namespace std;

class Singleton
{
	static mutex m;
	static atomic<Singleton*> singletonInstance;
	Singleton() = default;
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
public:
	static Singleton* getInstance() 
	{
		if(singletonInstance == nullptr) {
			lock_guard<mutex> lock(m);
			if(singletonInstance == nullptr) {
				singletonInstance = new Singleton();
			}
		}
		return singletonInstance;
	}
};

mutex Singleton::m;
atomic<Singleton*> Singleton::singletonInstance;

class SingletonC 
{
	SingletonC() = default;
	SingletonC(const SingletonC&) = delete;
	SingletonC& operator=(const SingletonC&) = delete;
public:
	static SingletonC& getInstance() 
	{
		static SingletonC s;
		return s;
	}
};

int main()
{
	auto singleton = Singleton::getInstance();
	auto& singletonc = SingletonC::getInstance();
	return 0;
}
