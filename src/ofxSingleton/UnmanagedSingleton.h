#pragma once

#include <memory>

namespace ofxSingleton {
	template<typename ClassType>
	class UnmanagedSingleton {
	public:
		static ClassType & X() {
			return * ClassType::getSingleton();
		}
		static std::shared_ptr<ClassType> getSingleton() {
			if (!ClassType::singleton) {
				ClassType::singleton = std::make_shared<ClassType>();
			}
			return ClassType::singleton;
		}
	private:
		static std::shared_ptr<ClassType> singleton;
	};
}