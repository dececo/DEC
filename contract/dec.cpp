#include <eosiolib/eosio.hpp>
#include "dec.hpp"

using namespace eosio;

// 投票发起人接口
void Dec::addposposal(string posposal_name) // 初始化投票提案
{
  require_auth(_self);

  posposal_index posposals(_self, _self);
  auto it = posposals.find(eosio::string_to_name(posposal_name.c_str()));
  eosio_assert(it == posposals.end(), "posposal exist");

  posposals.emplace(_self, [&](auto &a) {
    a.name = posposal_name;
    a.voteCount = 0;
  });
}
void Dec::addvoter(account_name voter_name, uint64_t weight /* =1 */) // 初始化投票人
{
  require_auth(_self);
  eosio_assert(weight > 0, "must positive weight");

  voter_index voters(_self, _self);
  auto it = voters.find(voter_name);

  eosio_assert(it == voters.end(), "voter exist");
  voters.emplace(_self, [&](auto &a) {
    a.account = voter_name;
    a.weight = weight;
    a.voted = false;
    a.delegate_account = 0;
    a.pos_name = "";
  });
}
// 普通选民接口
void Dec::delegate(account_name voter, account_name delegate_to) // 委托投票（跟随投票）
{
  require_auth(voter);

  voter_index voters(_self, _self);
  auto vit = voters.find(voter);
  eosio_assert(vit->voted == false, "is voted");
  eosio_assert(vit != voters.end(), "voter not exist");
  auto it = voters.find(delegate_to);
  eosio_assert(it != voters.end(), "delegate_to not exist");

  while (it != voters.end() && it->delegate_account != 0 && it->delegate_account != voter)
    it = voters.find(it->delegate_account);

  eosio_assert(it != voters.end(), "delegate obj not exist");
  eosio_assert(it->account != voter, "not delegate self");

  if (it->voted)
  {
    vote(voter, it->pos_name);
  }
  else
  {
    voters.modify(it, _self, [&](auto &a) {
      a.weight += vit->weight;
    });
    voters.modify(vit, _self, [&](auto &a) {
      a.voted = true;
    });
  }
}
void Dec::vote(account_name voter, string proposal) // 投票给某个提议
{
  require_auth(voter);
  posposal_index posposals(_self, _self);
  auto it = posposals.find(eosio::string_to_name(proposal.c_str()));
  eosio_assert(it != posposals.end(), "posposal not exist");

  voter_index voters(_self, _self);
  auto vit = voters.find(voter);
  eosio_assert(vit->voted == false, "is voted");
  eosio_assert(vit != voters.end(), "voter not exist");

  voters.modify(vit, _self, [&](auto &a) {
    a.voted = true;
    a.pos_name = proposal;
  });

  posposals.modify(it, _self, [&](auto &a) {
    a.voteCount += vit->weight;
  });
}
void Dec::winproposal() // 返回投票数最多的提议
{
  posposal_index posposals(_self, _self);
  auto win = posposal();
  uint64_t max = 0;
  for (auto it : posposals)
  {
    if (it.voteCount > max)
    {
      max = it.voteCount;
      win = it;
    }
  }
  if (max > 0)
  {
    eosio::print("win posposal is: ", win.name.c_str(), "vote count", win.voteCount, "\n");
  }
  else
  {
    eosio::print("not vote", "\n");
  }
}
void Dec::allproposal() // 返回全部提案投票状态
{
  posposal_index posposals(_self, _self);
  uint64_t idx = 0;
  for (auto it : posposals)
  {
    eosio::print(" posposal ", idx, ":", it.name.c_str(), "vote count", it.voteCount, "\n");
  }
}

EOSIO_ABI(Dec, (addposposal)(addvoter)(delegate)(vote)(winproposal)(allproposal))

