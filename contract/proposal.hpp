/**
 *  @file
 *  @copyright defined in LICENSE.txt
 */
#include <eosiolib/eosio.hpp>
#include <boost/container/flat_map.hpp>

using namespace eosio;
using boost::container::flat_map;

class proposals: public eosio::contract {
public:
	using contract::contract;
	proposals(account_name self) :
			contract(self) {
	}

	void vote(uint64_t id, account_name account, uint32_t vote);
	void add(uint64_t id, account_name owner);
	void remove(uint64_t id, account_name owner);

private:
	// @abi table proposal i64
	struct aproposal {
		uint64_t id;
		account_name owner;
		flat_map<account_name, uint32_t> votes;

		uint64_t primary_key() const {
			return id;
		}
		EOSLIB_SERIALIZE( aproposal, (id)(owner)(votes) )
	};

	typedef eosio::multi_index<N(proposal), aproposal> proposal_index;

};
