/**
 *  @file
 *  @copyright defined in LICENSE.txt
 */
#include <eosiolib/eosio.hpp>
#include <string>

using namespace eosio;

class committeemanager: public eosio::contract {
public:
	using contract::contract;
	committee(account_name self) :
			contract(self) {
	}

	void allmember(uint64_t id, set<account_name>& account_list);
	void addmember(uint64_t id, account_name name);
	void removemember(uint64_t id, account_name name);

private:
	// @abi table committee i64
	struct member_list {
		uint64_t id;
		set<account_name> account_list;

		uint64_t primary_key() const {
			return id;
		}

		EOSLIB_SERIALIZE( member_list, (id)(account_list) )
	};

	typedef eosio::multi_index<N(committee), member_list> committee_index;

}
