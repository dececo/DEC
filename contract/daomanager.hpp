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
	bool create(uint64_t id, account_name owner, string name, string desc);
	bool update_owner(uint64_t id, account_name new_owner);
	bool update_name(uint64_t id, string new_name);
	bool update_desc(uint64_t id, string new_desc);
	bool remove(uint64_t id);

private:
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
	typedef eosio::multi_index<N(dao), dao> dao_index;
};
