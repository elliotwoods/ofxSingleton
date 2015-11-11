#pragma once

#include <memory>

#define OFXSINGLETON_DEFINE_UNMANAGED(X) template<> std::shared_ptr<X> ofxSingleton::UnmanagedSingleton<X>::getInstance() { \
	static std::shared_ptr<X> instance = make_shared<X>(); \
	return instance; \
}

namespace ofxSingleton {
	template<typename ClassType>
	class UnmanagedSingleton {
	public:
		static ClassType & X() {
			return * ClassType::getInstance();
		}
		static std::shared_ptr<ClassType> getInstance();
	};
}