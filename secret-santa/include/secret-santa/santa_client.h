#pragma once

#include <sleepy_discord/websocketpp_websocket.h>
#include <sleepy_discord/message.h>

#include <secret-santa/santa.h>

namespace secret { namespace santa {

class santa_client: public SleepyDiscord::DiscordClient
{
  using SleepyDiscord::DiscordClient::DiscordClient;

public:
  static constexpr const char* CMD_PREFIX_REGISTER{"-register"};
  static constexpr const char* CMD_PREFIX_EXCLUDE{"-exclude"};
  static constexpr const char* CMD_PREFIX_DRAW{"-draw"};
  static constexpr const char* CMD_PREFIX_NOTIFY{"-notify"};
  static constexpr const char* CMD_PREFIX_SANTA{"-santa"};

  inline void set_master(const std::string& username) { _master_username = username; }
  inline void set_server(const std::string& servername) { _server_name = servername; }

protected:
  virtual void onMessage(SleepyDiscord::Message message) override;
  virtual void onServer(SleepyDiscord::Server server) override;

private:
  std::string _master_username;
  std::string _master_id;
  std::string _server_name;

  secret::santa::santa_t _santa;

  // user id -> username
  std::map<std::string, std::string> _id;

  bool is_master(const SleepyDiscord::User& u) const;
  std::string username(const std::string& id) const;

  void handle_register(const SleepyDiscord::Message& message);
  void handle_exclude(const SleepyDiscord::Message& message);
  void handle_notify();
  void handle_draw();
  void handle_santa(const std::string& user_id);
};

} } // secret::santa
