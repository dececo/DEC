#include "proposal.hpp"

void proposals::vote(uint64_t id,
		account_name account, uint32_t vote) {
	proposal_index pi(_self, _self);
	auto it = pi.find(id);
	eosio_assert(it != pi.end(), "id doesn't exist!");
	
	pi.modify(it, _self,[&](auto &p) {
			p.votes[account] = vote;
			});
	print("id: ", id, ", account: ", account, ", vote: ", vote);
}

void proposals::add(uint64_t id, account_name owner) {
	proposal_index pi(_self, _self);
	auto it = pi.find(id);
	eosio_assert(it == pi.end(), "id already exists!");
	pi.emplace(_self, [&](auto &p) {
		p.id = id;
		p.owner = owner;
	});
	print("id: ", id, ", owner: ", owner);
}

void proposals::remove(uint64_t id, account_name owner) {
	proposal_index pi(_self, _self);
	auto it = pi.find(id);
	eosio_assert(it == pi.end(), "id already exists!");
	pi.erase(it);
	print("id: ", id, ", owner: ", owner);
}

EOSIO_ABI(proposals, (vote)(add)(remove))
