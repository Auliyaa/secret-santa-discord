#include <secret-santa/santa_client.h>

using namespace secret::santa;

void santa_client::onMessage(SleepyDiscord::Message message)
{
  std::cout << message.type << std::endl;
}
