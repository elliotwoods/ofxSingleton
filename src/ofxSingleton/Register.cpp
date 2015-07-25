#include "Register.h"
#include "ofLog.h"

#include <iostream>

using namespace std;

namespace ofxSingleton {
	//----------
	std::shared_ptr<Register> Register::singleton;

	//----------
	Register::Register() {
		this->parentRegister = nullptr;
	}

	//----------
	const Register::Entries & Register::getEntries() const {
		return this->entries;
	}

	//----------
	void Register::addEntry(BaseStore * baseStore) {
		if (baseStore) {
			const auto typeInfo = baseStore->getTypeInfo();

			this->entries.insert(Pair(typeInfo, baseStore));

			//sync it to the master (if we're master then nothing happens)
			this->syncSingleton(typeInfo);
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
	void Register::syncSingleton(const std::type_info * singletonType) {
		if (this->parentRegister) {
			//check if it exists in the master registry
			auto findParentEntry = this->parentRegister->entries.find(singletonType);
			if (findParentEntry != this->parentRegister->entries.end()) {
				//entry for this singleton exists in master
				this->entries[singletonType]->setMaster(findParentEntry->second);
			}
			else {
				//problem time, the singleton is registered in the client but not the master
				ofLogWarning("ofxSingleton") << "Singleton entry '" << singletonType->name() << "' exists in Client registry but not in Master register. Cannot synchronise singleton";
			}
		}
	}
}