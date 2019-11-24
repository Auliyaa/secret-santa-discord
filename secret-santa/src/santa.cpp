#include <secret-santa/santa.h>

#include <vector>
#include <algorithm>

using namespace secret::santa;

santa_t::santa_t()
{
  static bool srand_done{false};
  if (!srand_done)
  {
    srand_done = true;
    srand(static_cast<unsigned int>(time(nullptr)));
  }
}

void santa_t::reg_user(const std::string& display_name, const std::string& discord_id)
{
  _registered[display_name] = discord_id;
}

void santa_t::exclude(const std::string& user_a, const std::string& user_b)
{
  _excluded[user_a] = user_b;
}

std::map<std::string, std::string> santa_t::draw() const
{
  // list of users (keys from the _registered map) for easier iteration later-on
  std::vector<std::string> users;
  for (const auto& kv : _registered)
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
  for (const auto& exclusion_rule : _excluded)
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

  return result;
}
