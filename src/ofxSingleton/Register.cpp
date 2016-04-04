#include "Register.h"
#include "ofLog.h"

#include <iostream>

using namespace std;

OFXSINGLETON_DEFINE_UNMANAGED(ofxSingleton::Register)

namespace ofxSingleton {	
	//----------
	Register::Register() {
		this->parentRegister = nullptr;

		ofAddListener(ofEvents().exit, this, &Register::onExit);
	}

	//----------
	const Register::Entries & Register::getEntries() const {
		return this->entries;
	}

	//----------
	void Register::addEntry(BaseStore * baseStore) {
		if (baseStore) {
			const auto typeName = string(baseStore->getTypeInfo()->name());

			this->entries.insert(Pair(typeName, baseStore));

			//sync it to the master (if we're master then nothing happens)
			this->syncSingleton(typeName);
		}
	}

	//----------
	void Register::setParentRegister(Register * parentRegister) {
		this->parentRegister = parentRegister;

		for (auto & entry : this->entries) {
			this->syncSingleton(entry.first);
		}
	}

	//----------
	void Register::syncSingleton(string typeName) {
		if (this->parentRegister) {
			//check if it exists in the master registry
			auto findParentEntry = this->parentRegister->entries.find(typeName);
			if (findParentEntry != this->parentRegister->entries.end()) {
				//entry for this singleton exists in master
				this->entries[typeName]->setMaster(findParentEntry->second);
			}
			else {
				//problem time, the singleton is registered in the client but not the master
				ofLogWarning("ofxSingleton") << "Singleton entry '" << typeName << "' exists in Client registry but not in Master register. Cannot synchronise singleton";
			}
		}
	}

	//----------
	void Register::onExit(ofEventArgs &) {
		for (auto singletonStore : this->getEntries()) {
			if (singletonStore.second) {
				singletonStore.second->clearInstance();
			}
		}
	}
}