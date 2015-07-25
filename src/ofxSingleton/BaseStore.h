#pragma once

#include <typeinfo>

namespace ofxSingleton {
	class BaseStore {
	public:
		BaseStore() {
			this->masterStoreUntyped = nullptr;
		}

		virtual const std::type_info * getTypeInfo() const = 0;

		///Useful for when you're synchronising singletons between dynamic libraries
		void setMaster(BaseStore * masterStoreUntyped) {
			this->masterStoreUntyped = masterStoreUntyped;
			syncToMaster();
		}
	protected:
		///called from BaseStore and handled in derived class. returns true if we got an instance from the master
		virtual void syncToMaster() = 0;

		///In a dynamically loaded library, this will be the store for the singleton in the master app
		BaseStore * masterStoreUntyped;
	};
}