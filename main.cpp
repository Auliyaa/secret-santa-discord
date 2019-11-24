#include <ctime>
#include <random>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <iostream>
#include <algorithm>

// user name -> discord id
static const std::map<std::string, std::string> USER_IDS{
  {"Auliyaa", "@Auliyaa#1234"},
  {"Khalypm", "@Khalypm#1234"},

  {"Shawo", "@Shawo#1234"},

  {"Vachequiri", "@Vachequiri#1234"},
  {"Rimapita", "@Rimapita#1234"},

  {"Bastious", "@Bastious#1234"},

  {"Noisy", "@Noisy#1234"},

  {"Iwik", "@Iwik#1234"},
  {"Lucie", "Lucie"},

  {"Edou", "@Edou#1234"},

  {"Dwarf", "@Dwarf#1234"},
  {"Cécile", "Cécile"},

  {"Sothir", "@Sothir#1234"},
  {"Simon", "@elliond#1234"}
};

// manual exclusions for secret santa (bidirectional)
const std::list<std::pair<std::string, std::string>> EXCLUSIONS{
  // couples
  {"Khalypm", "Auliyaa"},
  {"Dwarf", "Cécile"},
  {"Iwik", "Lucie"},
  {"Vachequiri", "Rimapita"},
  // friends
  {"Vachequiri", "Shawo"},
  {"Vachequiri", "Iwik"},
  {"Rimapita", "Iwik"},
  {"Simon", "Iwik"},
  {"Simon", "Vachequiri"},
  {"Bastious", "Dwarf"},
};

int main()
{
  srand(static_cast<unsigned int>(time(nullptr)));

  // list of users (keys from the USER_IDS map) for easier iteration later-on
  std::vector<std::string> users;
  for (const auto& kv : USER_IDS)
  {
    users.emplace_back(kv.first);
  }

  // will map each user to the list of potential users they can gift
  std::map<std::string, std::vector<std::string>> draw_pool;

  // start by associating everyone with everyone but themself
  for (const auto& giver : users)
  {
    draw_pool[giver] = {};
    for (const auto& receiver : users)
    {
      if (giver != receiver)
      {
        draw_pool[giver].emplace_back(receiver);
      }
    }
  }

  // apply manual exclusions
  for (const auto& exclusion_rule : EXCLUSIONS)
  {
    {
      auto& v = draw_pool[exclusion_rule.first];
      v.erase(std::find(v.begin(), v.end(), exclusion_rule.second));
    }
    {
      auto& v = draw_pool[exclusion_rule.second];
      v.erase(std::find(v.begin(), v.end(), exclusion_rule.first));
    }
  }

  // for each user, draw a random target.
  // each time a target is drawn, remove it from all other users
  // in addition, remove the user from the target's targets to avoid bidirectional gifts.
  std::map<std::string, std::string> result;

  while (!users.empty())
  {
    // sort users so that the one with the least possible matches is treated first
    std::sort(users.begin(), users.end(), [&](const auto& a, const auto& b) -> bool
    {
      // check if a has less potenital matches than b
      if (draw_pool[a].size() == draw_pool[b].size())
      {
        return a < b;
      }

      return (draw_pool[a].size() < draw_pool[b].size());
    });

    // select a random target
    auto src = users[0];
    auto tgt = draw_pool[src][static_cast<size_t>(rand()) % draw_pool[src].size()];

    // store result
    result[users[0]] = tgt;

    // exclude tgt from all other users' draw pool since it already has a gift
    for (auto& kv : draw_pool)
    {
      auto l = std::find(kv.second.begin(), kv.second.end(), tgt);
      if (l != kv.second.end())
      {
        kv.second.erase(l);
      }
    }

    // exclude src from tgt to avoid bidirectional gifts
    auto l = std::find(draw_pool[tgt].begin(), draw_pool[tgt].end(), src);
    if (l != draw_pool[tgt].end())
    {
      draw_pool[tgt].erase(l);
    }

    // remove the user before next iteration
    users.erase(users.begin());
  }

  for (const auto& kv : result)
  {
    std::cout << kv.first << " -> " << kv.second << std::endl;
  }
}
