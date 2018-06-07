/**
 *  @file
 *  @copyright defined in LICENSE.txt
 */
#include <eosiolib/eosio.hpp>
#include <string>

using namespace eosio;
using std::string;

class daomanager: public eosio::contract {
public:
	using contract::contract;
	daomanager(account_name self) :
			contract(self) {
	}

	void create(uint64_t id, account_name owner, string name, string desc);
	void updateowner(uint64_t id, account_name new_owner);
	void updatename(uint64_t id, string new_name);
	void updatedesc(uint64_t id, string new_desc);
	void remove(uint64_t id);

private:
	// @abi table daos i64
	struct dao {
		uint64_t id;
		account_name owner;
		string name;
		string desc;
		uint64_t timestamp;

		uint64_t primary_key() const {
			return id;
		}

		EOSLIB_SERIALIZE( dao, (id)(owner)(name)(desc)(timestamp) )
	};
	typedef eosio::multi_index<N(daos), dao> dao_index;
};
