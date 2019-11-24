#pragma once

#include <map>

namespace secret { namespace santa {

class santa_t
{
public:
  santa_t();
  virtual ~santa_t() = default;

  void reg_user(const std::string& display_name, const std::string& discord_id);
  void exclude(const std::string& user_a, const std::string& user_b);

  std::map<std::string, std::string> draw() const;

private:
  // display name -> discord id
  std::map<std::string, std::string> _registered;
  // display name -> display name
  std::map<std::string, std::string> _excluded;
};

} } // secret::santa
