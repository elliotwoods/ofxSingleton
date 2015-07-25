#pragma once

#include "UnmanagedSingleton.h"
#include "BaseStore.h"

#include <map>
#include <typeinfo>

namespace ofxSingleton {
	///A register of all active and inactive singletons
	class Register : public UnmanagedSingleton<Register> {
	public:
		typedef std::map<const std::type_info *, BaseStore *> Entries;
		typedef std::pair<const std::type_info *, BaseStore *> Pair;

		Register();
		const Entries & getEntries() const; ///Called on master from client
		void addEntry(BaseStore *);

		///Call this function to synchronise this Register to a master register
		void setParentRegister(Register *);
	private:
		void syncSingleton(const std::type_info *);
		Entries entries;
		const Register * parentRegister;
	};
}