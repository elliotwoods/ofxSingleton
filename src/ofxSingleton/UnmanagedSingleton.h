#pragma once

#include <memory>

namespace ofxSingleton {
	template<typename ClassType>
	class UnmanagedSingleton {
	public:
		static ClassType & X() {
			if (!ClassType::singleton) {
				ClassType::singleton = std::make_shared<ClassType>();
			}
			return * ClassType::singleton;
		}
	protected:
		static std::shared_ptr<ClassType> singleton;
	};
}