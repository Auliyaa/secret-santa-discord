#include <secret-santa/santa_client.h>

using namespace secret::santa;

void santa_client::onMessage(SleepyDiscord::Message message)
{
  // handle admin commands here
  if (is_master(message.author))
  {
    // -register: registers all provided users inside the santa instance)
    if (message.startsWith(CMD_PREFIX_REGISTER))
    {
      handle_register(message);
    }

    else if (message.startsWith(CMD_PREFIX_EXCLUDE))
    {
      handle_exclude(message);
    }

    else if (message.startsWith(CMD_PREFIX_DRAW))
    {
      handle_draw();
    }

    else if (message.startsWith(CMD_PREFIX_NOTIFY))
    {
      handle_notify();
    }
  }

  if (message.startsWith(CMD_PREFIX_SANTA))
  {
    handle_santa(message.author.ID);
  }
}

void santa_client::onServer(SleepyDiscord::Server server)
{
  if (server.name == _server_name)
  {
    for (const auto& member : server.members)
    {
      _id[member.user.ID.string()] = member.user.username;
      if (member.user.username == _master_username)
      {
        _master_id = member.user.ID.string();
        _santa.register_id(_master_id);
      }
    }

    // check that the master is actually a member of the server
    if (_master_id.empty())
    {
      std::cerr << "Failed to locate master " << _master_username << " in server " << _server_name << std::endl;
      std::exit(1);
    }
  }
}

bool santa_client::is_master(const SleepyDiscord::User& u) const
{
  return u.ID.string() == _master_id;
}

std::string santa_client::username(const std::string& id) const
{
  auto l = _id.find(id);
  if (l == _id.end())
  {
    return id;
  }
  return l->second;
}

void santa_client::handle_register(const SleepyDiscord::Message& message)
{
  // usage: -register [user [user [user...]]]
  for (const auto& mention : message.mentions)
  {
    _santa.register_id(mention.ID.string());
  }

  sendMessage(message.channelID, "Registered users:");
  for (const auto& reg : _santa.registered())
  {
    sendMessage(message.channelID, " -- " + username(reg));
  }
}

void santa_client::handle_exclude(const SleepyDiscord::Message& message)
{
  std::string user_a, user_b;

  for (const auto& mention : message.mentions)
  {
    if (user_a.empty()) user_a = mention.ID.string();
    else user_b = mention.ID.string();
  }

  if (!user_a.empty() && !user_b.empty())
  {
    if (!_santa.is_registered(user_a))
    {
      sendMessage(message.channelID, username(user_a) + " is not registered for the secret santa.");
      return;
    }
    if (!_santa.is_registered(user_b))
    {
      sendMessage(message.channelID, username(user_b) + " is not registered for the secret santa.");
      return;
    }
    _santa.exclude(user_a, user_b);
  }

  sendMessage(message.channelID, "List of exclusions:");
  for (const auto& exclusion : _santa.exclusions())
  {
    sendMessage(message.channelID, " -- " + username(exclusion.first) + " <-> " + username(exclusion.second));
  }
}

void santa_client::handle_notify()
{
  for (const auto& user_id : _santa.registered())
  {
    handle_santa(user_id);
    sleep(2000);
  }
}

void santa_client::handle_draw()
{
  _santa.draw();
  sendMessage(createDirectMessageChannel(_master_id).cast().ID, "Results of the secret santa are ready !");
  sendMessage(createDirectMessageChannel(_master_id).cast().ID, "Run the -notify command to send a private message to all members with their secret santa");
}

void santa_client::handle_santa(const std::string& user_id)
{
  auto reg = _santa.registered();
  if (std::find(reg.begin(), reg.end(), user_id) == reg.end())
  {
    return;
  }

  auto dmc = createDirectMessageChannel(user_id).cast().ID;
//  auto dmc = createDirectMessageChannel(_master_id).cast().ID;
  sendMessage(dmc, "Coucou " + username(user_id) + " ! Voici ton tirage pour le secret santa !\n" +
                   "Ton cadeau est destiné à: **" + username(_santa.result(user_id)) + "**.\n" +
                   "**Pour rappel** : Soit quelque chose de fabriqué, soit un cadeau en dessous de 10€.\n" +
                   "Si tu as besoin d'un rappel, tu peux m'envoyer **-santa** au 8-12-... En message privé pour obtenir ce message de nouveau.\n"
                   "Des bisous !");
}
