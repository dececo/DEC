#include <sstream>
#include <string>
#include "committee.hpp"

using std::string;
using std::ostringstream;

void committeemanager::allmember(uint64_t id,
		vector<account_name>& account_list) {
	committee_index ci(_self, _self);
	auto it = ci.find(id);
	eosio_assert(it != ci.end(), "id doesn't exist!");
	print("id: ", id, ", committee: [", it->account_list.size(), "]");
}

void committeemanager::addmember(uint64_t id, account_name name) {
	committee_index ci(_self, _self);
	auto it = ci.find(id);
	if(it == ci.end()) {
		ci.emplace(_self, [&](auto &c) {
			c.id = id;
			c.account_list.push_back(name);
		});
		print("id: ", id, ", committee: [", ci.find(id)->account_list.size(), "]");
	} else {
		ci.modify(it, _self, [&](auto &c) {
			c.account_list.push_back(name);
		});
		print("id: ", id, ", committee: [", it->account_list.size(), "]");
	}
}

void committeemanager::removemember(uint64_t id, account_name name) {
	committee_index ci(_self, _self);
	auto it = ci.find(id);
	eosio_assert(it != ci.end(), "id doesn't exist!");
	vector<account_name> al;
	for(auto a : it->account_list) {
		if(a != name) {
			al.push_back(a);
		}
	}
	// 即便委员会为空，也不删除改行数据
	ci.modify(it, _self, [&](auto &c) {
		c.account_list = al;
	});
	print("id: ", id, ", committee: [", it->account_list.size(), "]");
}

EOSIO_ABI(committeemanager, (allmember)(addmember)(removemember))
