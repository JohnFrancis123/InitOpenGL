#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton {
public:
	static T& GetInstance() {
		static T instance;
		return instance;
	}
protected:
	Singleton() {}
	~Singleton() {}
private:
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;
};


#endif // SINGLETON_H