/**
 *  @file
 *  @copyright defined in LICENSE.txt
 */
#include <eosiolib/eosio.hpp>
#include <string>

using namespace eosio;
using std::string;

class Dec : public eosio::contract
{
public:
  using contract::contract;
  Dec(account_name self) : contract(self) {}

  // 投票发起人接口
  void addposposal(string posposal_name);                      // 初始化投票提案
  void addvoter(account_name voter_name, uint64_t weight = 1); // 初始化投票人
  // 普通选民接口
  void delegate(account_name voter, account_name delegate_to); // 委托投票（跟随投票）
  void vote(account_name voter, string proposal);              // 投票给某个提议
  void winproposal();                                          // 返回投票数最多的提议
  void allproposal();                                          // 返回全部提案投票状态

private:
  // 定义投票人
  struct voter
  {
    account_name account;      // 投票人
    uint64_t weight;           // 权重
    bool voted;                // 如果值为true，代表这个投票人已经投过票
    uint64_t delegate_account; // 委托投票人地址
    string pos_name;           // 投票提案名

    uint64_t primary_key() const { return account; }

    EOSLIB_SERIALIZE(voter, (account)(weight)(voted)(delegate_account)(pos_name));
  };
  // 提案的数据结构
  struct posposal
  {
    string name;        // 提案的名称
    uint64_t voteCount; // 提议接受的投票数

    uint64_t primary_key() const { return eosio::string_to_name(name.c_str()); }

    EOSLIB_SERIALIZE(posposal, (name)(voteCount));
  };

  typedef eosio::multi_index<N(voter), voter> voter_index;
  typedef eosio::multi_index<N(posposal), posposal> posposal_index;
};
