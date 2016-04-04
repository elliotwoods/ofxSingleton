#pragma once
#include "Register.h"
#include "BaseStore.h"

#include "ofLog.h"

#include <memory>

#define OFXSINGLETON_DEFINE(X) template<> \
ofxSingleton::Singleton<X>::SingletonStore & ofxSingleton::Singleton<X>::getSingletonStore() { \
	static X::SingletonStore singletonStore;\
	return singletonStore; \
}

namespace ofxSingleton {
	template<typename ClassType>
	class Singleton {
	public:
		///The Store keeps the singleton, we always have an instance of it
		///mostly because it is cheaper to always 
		class SingletonStore : public BaseStore {
		public:
			SingletonStore() {
				auto & singletonRegister = Register::X();
				singletonRegister.addEntry(this);
			}

			///Override BaseStore
			const std::type_info * getTypeInfo() const override {
				return & typeid(ClassType);
			}

			///Always returns a valid pointer (i.e. create on first call)
			std::shared_ptr<ClassType> getInstance() {	
				//if we have a host application, use the singleton from that
				if (this->hasMaster()) {
					auto masterStore = static_cast<SingletonStore*>(this->masterStoreUntyped);
					return masterStore->getInstance();
				}
				//otherwise use local
				if(!this->instance) {
					this->instance = std::make_shared<ClassType>();
				}
				return this->instance;
			}

			void clearInstance() override {
				this->instance.reset();
			}
		protected:
			std::shared_ptr<ClassType> instance;
		};

		static ClassType & X() {
			return * ClassType::getSingletonStore().getInstance();
		}

		static SingletonStore & getSingletonStore();
	};
}