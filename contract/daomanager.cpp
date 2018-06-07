#include "daomanager.hpp"

bool daomanager::create(uint64_t id, account_name owner, string name,
		string desc) {
	print("id: ", id, ", owner: ", owner, "name: ", name, "desc: ", desc);
	dao_index daos(_self, _self);
	auto it = daos.find(id);
	eosio_assert(it == daos.end(), "dao id exists!");
	daos.emplace(_self, [&](auto &d) {
		d.id = id;
		d.owner = owner;
		d.name = name;
		d.desc = desc;
		d.timestamp = 1000; //TODO
		});

	return true;
}

bool daomanager::update_owner(uint64_t id, account_name new_owner) {
	print("change owner to: ", new_owner);
	dao_index daos(_self, _self);
	auto it = daos.find(id);
	eosio_assert(it != daos.end(), "dao id doesn't exist!");
	daos.modify(it, _self, [&](auto &d) {
		d.owner = new_owner;
	});

	return true;
}

bool daomanager::update_name(uint64_t id, string new_name) {
	print("change name to: ", new_name);
	dao_index daos(_self, _self);
	auto it = daos.find(id);
	eosio_assert(it != daos.end(), "dao id doesn't exist!");
	daos.modify(it, _self, [&](auto &d) {
		d.name = new_name;
	});

	return true;
}

bool daomanager::update_desc(uint64_t id, string new_desc) {
	print("change desc to: ", new_desc);
	dao_index daos(_self, _self);
	auto it = daos.find(id);
	eosio_assert(it != daos.end(), "dao id doesn't exist!");
	daos.modify(it, _self, [&](auto &d) {
		d.desc = new_desc;
	});

	return true;
}

bool daomanager::remove(uint64_t id) {
	print("remove dao by id: ", id);
	dao_index daos(_self, _self);
	auto it = daos.find(id);
	eosio_assert(it != daos.end(), "dao id doesn't exist!");
	daos.erase(it);

	return true;
}

EOSIO_ABI(daomanager, (create)(update_owner)(update_name)(update_desc)(remove))
