#include "daomanager.hpp"

bool daomanager::create(uint64_t id, account_name owner, string name,
		string desc) {
	print("id: ", id, ", owner: ", owner, "name: ", name, "desc: ", desc);
	dao_index daos(_self, _self);
	auto it = daos.find(id);
	eosio_asset(it == daos.end(), "dao id exists!");
	daos.emplace(_self, [&](auto &d) {
		d.id = id;
		d.owner = owner;
		d.name = name;
		d.desc = desc;
		d.timestamp = 1000; //TODO
		});

	return true;
}

bool daomanager::updatae_owner(string new_owner) {
	print("change owner to: ", new_owner);
	dao_index daos(_self, _self);
	auto it = daos.find(id);
	eosio_asset(it != daos.end(), "dao id doesn't exist!");
	daos.modify(it, _self, [&](auto &d) {
		d.owner = new_owner;
	});

	return true;
}

bool daomanager::update_name(string new_name) {
	print("change name to: ", new_name);
	dao_index daos(_self, _self);
	auto it = daos.find(id);
	eosio_asset(it != daos.end(), "dao id doesn't exist!");
	daos.modify(it, _self, [&](auto &d) {
		d.name = new_name;
	});

	return true;
}

bool daomanager::update_desc(string new_desc) {
	print("change desc to: ", new_desc);
	dao_index daos(_self, _self);
	auto it = daos.find(id);
	eosio_asset(it != daos.end(), "dao id doesn't exist!");
	daos.modify(it, _self, [&](auto &d) {
		d.owner = new_desc;
	});

	return true;
}

bool daomanager::remove(uint64_t id) {
	print("remove dao by id: ", id);
	dao_index daos(_self, _self);
	auto it = daos.find(id);
	eosio_asset(it != daos.end(), "dao id doesn't exist!");
	daos.erase(it);

	return true;
}
