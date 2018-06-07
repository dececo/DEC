#include <sstream>
#include <string>
#include "committee.hpp"

using std::string;
using std::ostringstream;

void committeemanager::allmember(uint64_t id,
		set<account_name>& account_list) {
	committee_index ci(_self, _self);
	auto it = ci.find(id);
	eosio_assert(it != ci.end(), "id doesn't exist!");
	member_list ml = *it;
	ostringstream oss;
	for(auto it2 = ml.account_list.begin(); it2 != ml.account_list.end(); it2++) {
		oss << *it2 << ",";
	}
	string l = oss.str();
	print("id: ", id, ", committee: [", l, "]");
}

void committeemanager::addmember(uint64_t id, account_name name) {
	committee_index ci(_self, _self);
	auto it = ci.find(id);
	eosio_assert(it != ci.end(), "id doesn't exist!");
	member_list ml = *it;
	ml.account_list.insert(name);
	ostringstream oss;
	for(auto it2 = ml.account_list.begin(); it2 != ml.account_list.end(); it2++) {
		oss << *it2 << ",";
	}
	string l = oss.str();
	print("id: ", id, ", committee: [", l, "]");
}

void committeemanager::removemember(uint64_t id, account_name name) {
	committee_index ci(_self, _self);
	auto it = ci.find(id);
	eosio_assert(it != ci.end(), "id doesn't exist!");
	member_list ml = *it;
	ml.account_list.erase(name);
	ostringstream oss;
	for(auto it2 = ml.account_list.begin(); it2 != ml.account_list.end(); it2++) {
		oss << *it2 << ",";
	}
	string l = oss.str();
	print("id: ", id, ", committee: [", l, "]");
}

EOSIO_ABI(committeemanager, (allmember)(addmember)(removemember))
