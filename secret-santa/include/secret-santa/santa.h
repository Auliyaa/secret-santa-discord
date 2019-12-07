#pragma once

#include <map>
#include <vector>
#include <list>

namespace secret { namespace santa {

class santa_t
{
public:
  santa_t();
  virtual ~santa_t() = default;

  void register_id(const std::string& id);
  void exclude(const std::string& user_a, const std::string& user_b);
  void draw();

  inline std::vector<std::string> registered() const { return _registered; }
  bool is_registered(const std::string& id) const;
  inline std::list<std::pair<std::string, std::string>> exclusions() const { return _excluded; }
  inline std::map<std::string, std::string> results() const { return _results; }
  std::string result(const std::string& id) const;

  void save(const std::string& file, const std::map<std::string, std::string>& ids) const;
  void load(const std::string& file);

private:
  // display name -> discord id
  std::vector<std::string> _registered;
  // display name -> display name
  std::list<std::pair<std::string, std::string>> _excluded;
  // stores the result of the call to draw()
  std::map<std::string, std::string> _results;
};

} } // secret::santa
