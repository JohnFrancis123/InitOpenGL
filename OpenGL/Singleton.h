#ifndef SINGLETON_H
#define SINGLETON_H

//singletons are held on the stack, so they delete at the end of their scope
template <typename T>
class Singleton {
public:
	static T& GetInstance() {  //because it's static, its scope is until the end of program execution.
		static T instance; //instance created on the stack becasue we do not use new.
		return instance; 
	}
protected:
	Singleton() {} //protected, so cannot be made new from outside the inheritance chain
	virtual ~Singleton() {}  //protected, so cannot be deleted from outside the inheritance chain
private:
	Singleton(Singleton const&) = delete; //overriding the copy constructor to prevent copying
	Singleton& operator=(Singleton const&) = delete; //overloading the equal operator to prevent assignment
};


#endif // SINGLETON_H