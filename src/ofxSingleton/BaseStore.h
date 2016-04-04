#pragma once

#include <typeinfo>

namespace ofxSingleton {
	/**
	The BaseStore is an abstract storage class for singletons.
	Each managed (default) singleton uses a Store to keep the singleton.
	The store can talk to stores in other dynamic libs (e.g. to share singletons between dynamic libs)
	**/
	class BaseStore {
	public:
		BaseStore();
		virtual const std::type_info * getTypeInfo() const = 0;

		///Useful for when you're synchronising singletons between dynamic libraries
		void setMaster(BaseStore *);
		bool hasMaster() const;

		virtual void clearInstance() = 0;
	protected:
		///In a dynamically loaded library, this will be the store for the singleton in the master app
		BaseStore * masterStoreUntyped;

	};
}