#pragma once

#include <sleepy_discord/websocketpp_websocket.h>
#include <sleepy_discord/message.h>

namespace secret { namespace santa {

class santa_client: public SleepyDiscord::DiscordClient
{
  using SleepyDiscord::DiscordClient::DiscordClient;
protected:
  virtual void onMessage(SleepyDiscord::Message message) override;
};

} } // secret::santa
