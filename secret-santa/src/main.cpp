#include <iostream>

#include <secret-santa/santa.h>
#include <secret-santa/santa_client.h>

int main()
{
  secret::santa::santa_client clt{"MjcyNzk3NjY5NjAzMTQ3Nzc3.Xeq5DA.Uhmi5lrI7a_iGxOWhBXfxSJJX2s", 2};
  clt.set_master("Auliyaa");
  clt.set_server("You need a montage");
  clt.run();
}
