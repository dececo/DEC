#include "committee.hpp"

void committeemanager::allmember(uint64_t id,
		set<account_name>& account_list) {
	committee_index ci(_self, _self);
	auto it = ci.find(id);
	eosio_assert(it != dao.end(), "id doesn't exist!");
	member_list ml = *it;
	account_list = ml.account_list
	print("id: ", id, ", committee: ", account_list);
}

void committeemanager::addmember(uint64_t id, account_name name) {
	committee_index ci(_self, _self);
	auto it = ci.find(id);
	eosio_assert(it != dao.end(), "id doesn't exist!");
	member_list ml = *it;
	ml.account_list.insert(name)
	print("id: ", id, ", committee: ", ml.account_list);
}

void committeemanager::removemember(uint64_t id, account_name name) {
	committee_index ci(_self, _self);
	auto it = ci.find(id);
	eosio_assert(it != dao.end(), "id doesn't exist!");
	member_list ml = *it;
	ml.account_list.erase(name)
	print("id: ", id, ", committee: ", ml.account_list);
}

EOSIO_ABI(committeemanager, (allmember)(addmember)(removemember))
