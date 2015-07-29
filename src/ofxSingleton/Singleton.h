#pragma once
#include "Register.h"
#include "BaseStore.h"

#include "ofLog.h"

#include <memory>

namespace ofxSingleton {
	template<typename ClassType>
	class Singleton {
	public:
		///The Store keeps the singleton, we always have an instance of it
		///mostly because it is cheaper to always 
		class SingletonStore : public BaseStore {
			std::shared_ptr<ClassType> instance;
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
				if (!this->instance) {
					//no instance yet here
					if (this->hasMaster()) {
						//we have a master application, let's ask that for a valid instance
						auto masterStore = dynamic_cast<SingletonStore*>(this->masterStoreUntyped);
						if (masterStore) {
							//this may cause an early initialisation on the master store, but seems like a safe strategy
							this->instance = masterStore->getInstance();
						}
					} else {
						//we have no master, we will create the instance
						this->instance = std::make_shared<ClassType>();
					}
				}
				return this->instance;
			}
		};

		static ClassType & X() {
			return *ClassType::singletonStore.getInstance();
		}

		static SingletonStore & getStore() {
			return ClassType::Store;
		}
	private:
		static SingletonStore singletonStore;
	};
}