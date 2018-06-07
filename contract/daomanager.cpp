#include "daomanager.hpp"

void daomanager::create(uint64_t id, account_name owner, string name,
		string desc) {
	dao_index dao(_self, _self);
	auto it = dao.find(id);
	eosio_assert(it == dao.end(), "dao id already exists!");
	dao.emplace(_self, [&](auto &d) {
		d.id = id;
		d.owner = owner;
		d.name = name;
		d.desc = desc;
		d.timestamp = 1000; //TODO
		});
	print("create dao, id: ", id, ", owner: ", owner, ", name: ", name, ", desc: ", desc, ".");
}

void daomanager::updateowner(uint64_t id, account_name new_owner) {
	dao_index dao(_self, _self);
	auto it = dao.find(id);
	eosio_assert(it != dao.end(), "dao id doesn't exist!");
	dao.modify(it, _self, [&](auto &d) {
		d.owner = new_owner;
	});
	print("change owner to: ", new_owner);
}

void daomanager::updatename(uint64_t id, string new_name) {
	dao_index dao(_self, _self);
	auto it = dao.find(id);
	eosio_assert(it != dao.end(), "dao id doesn't exist!");
	dao.modify(it, _self, [&](auto &d) {
		d.name = new_name;
	});
	print("change name to: ", new_name);
}

void daomanager::updatedesc(uint64_t id, string new_desc) {
	dao_index dao(_self, _self);
	auto it = dao.find(id);
	eosio_assert(it != dao.end(), "dao id doesn't exist!");
	dao.modify(it, _self, [&](auto &d) {
		d.desc = new_desc;
	});
	print("change desc to: ", new_desc);
}

void daomanager::remove(uint64_t id) {
	print("remove dao by id: ", id);
	dao_index dao(_self, _self);
	auto it = dao.find(id);
	eosio_assert(it != dao.end(), "dao id doesn't exist!");
	dao.erase(it);
}

EOSIO_ABI(daomanager, (create)(updateowner)(updatename)(updatedesc)(remove))
