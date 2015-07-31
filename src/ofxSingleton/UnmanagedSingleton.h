#pragma once

#include <memory>

namespace ofxSingleton {
	template<typename ClassType>
	class UnmanagedSingleton {
	public:
		static ClassType & X() {
			return * ClassType::getSingleton();
		}
		static ClassType * getSingleton() {
			if (!ClassType::singleton) {
				ClassType::singleton = new ClassType();
			}
			return ClassType::singleton;
		}
	protected:
		static ClassType * singleton;
	};
}