#include "BaseStore.h"

namespace ofxSingleton {
	//----------
	BaseStore::BaseStore() {
		this->masterStoreUntyped = nullptr;
	}

	//----------
	void BaseStore::setMaster(BaseStore * masterStoreUntyped) {
		this->masterStoreUntyped = masterStoreUntyped;
	}

	//----------
	bool BaseStore::hasMaster() const {
		return (bool) this->masterStoreUntyped;
	}
}
