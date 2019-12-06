#include <iostream>

#include <secret-santa/santa.h>
#include <secret-santa/santa_client.h>

int main()
{
  secret::santa::santa_client clt{"MjcyNzk3NjY5NjAzMTQ3Nzc3.Xdt2Eg.xNRc4ELDfod3Q6qqwe1FdKp1ZZs", 2};
  clt.set_master("Auliyaa");
  clt.set_server("You need a montage");
  clt.run();
}
