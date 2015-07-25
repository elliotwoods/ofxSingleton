# ofxSingleton

## Introduction

Utilities for using the singleton pattern with your own classes.

Singletons are generally classes which have 1 instance shared across the application. You can read more about what singletons are and why you might want to use them at [http://www.codeproject.com/Articles/1921/Singleton-Pattern-its-implementation-with-C].

Some people consider singletons to be 'bad design' or otherwise a design element which is often used in a lazy way (Google even disallows them in their own code), you can read about this debate at [http://stackoverflow.com/questions/11831/singletons-good-design-or-a-crutch].

## Usage

### Designing signleton classes

In your class declaration (.h), inherit from `ofxSingleton::Singleton<YourClassType>`, e.g.:

```c++
class MyClassType : public ofxSingleton::Singleton<MyClassType> {
	//...	
};
```

In your class definition (.cpp), define the symbol `MyClassType::singletonStore`, e.g.:

```c++
#include "MyClassType.h"

MyClassType::SingletonStore MyClassType::singletonStore;

// rest of class definition
```

### Using singleton classes

Generally whenever you want to use the singleton of `YourClassType`, you simply use `YourClassType::X()` which returns a non-const reference to the singleton. You don't need to worry about creating or clearing the singleton, this happens automatically for you.

### Register

ofxSingleton also provides a class `ofxSingleton::Register` (which is itself a singleton). This register keeps track of all singletons and can be useful for synchronising singletons between plugins and applications.

## Notes

* Since some logic must be run each time you call `MySingletonClass::X()`, you might want to keep a local const reference if you plan on calling it many times in the same function.
* Instead of `ofxSingleton::Singleton`, you also have the option to instead inherit from `ofxSingleton::UnmanagedSingleton` which has fewer features and does not put the singleton into the singleton registry. Note that the line you must put into the class definition is different and looks like `std::shared_ptr<MyClassType> MyClassType::singleton;`

## License

MIT License.