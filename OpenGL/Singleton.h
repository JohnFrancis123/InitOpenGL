#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton {
public:
	static T& GetInstance() {  //because it's static, its scope is until the end of program execution.
		static T instance; //instance created on the stack becasue we do not use new.
		return instance; 
	}
protected:
	Singleton() {} //protected, so cannot be made new from outside the inheritance chain
	virtual ~Singleton() {} 
private:
	Singleton(Singleton const&) = delete; //overriding the copy constructor
	Singleton& operator=(Singleton const&) = delete; //overloading the equal operator
};


#endif // SINGLETON_H