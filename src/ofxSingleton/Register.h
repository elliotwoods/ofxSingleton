#pragma once

#include "UnmanagedSingleton.h"
#include "BaseStore.h"

#include <map>
#include <typeinfo>
#include <memory>
#include <string>

namespace ofxSingleton {
	///A register of all active and inactive singletons
	class Register : public UnmanagedSingleton<Register> {
	public:
		typedef std::map<std::string, BaseStore *> Entries;
		typedef std::pair<std::string, BaseStore *> Pair;

		const Entries & getEntries() const; ///Called on master from client
		void addEntry(BaseStore *);

		///Call this function to synchronise this Register to a master register
		void setParentRegister(std::shared_ptr<Register>);
	private:
		void syncSingleton(std::string typeName);
		Entries entries;

		//decided against weak_ptr because we probably want to keep the parent's stuff even if it somehow unloads
		std::shared_ptr<Register> parentRegister;
	};
}