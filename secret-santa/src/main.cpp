#include <iostream>

#include <secret-santa/santa.h>
#include <secret-santa/santa_client.h>

int main(int, char** argv)
{
  secret::santa::santa_client clt{argv[1], 2};
  clt.set_master("Auliyaa");
  clt.set_server("You need a montage");
  clt.run();
}
