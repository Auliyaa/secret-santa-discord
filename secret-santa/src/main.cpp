#include <iostream>

#include <secret-santa/santa.h>

int main()
{
  secret::santa::santa_t s;
  s.reg_user("Auliyaa", "@Auliyaa#1234");
  s.reg_user("Khalypm", "@Khalypm#1234");
  s.reg_user("Shawo", "@Shawo#1234");
  s.reg_user("Vachequiri", "@Vachequiri#1234");
  s.reg_user("Rimapita", "@Rimapita#1234");
  s.reg_user("Bastious", "@Bastious#1234");
  s.reg_user("Noisy", "@Noisy#1234");
  s.reg_user("Iwik", "@Iwik#1234");
  s.reg_user("Lucie", "Lucie");
  s.reg_user("Edou", "@Edou#1234");
  s.reg_user("Dwarf", "@Dwarf#1234");
  s.reg_user("Cécile", "Cécile");
  s.reg_user("Sothir", "@Sothir#1234");
  s.reg_user("Simon", "@elliond#1234");

  s.exclude("Khalypm", "Auliyaa");
  s.exclude("Dwarf", "Cécile");
  s.exclude("Iwik", "Lucie");
  s.exclude("Vachequiri", "Rimapita");
  s.exclude("Vachequiri", "Shawo");
  s.exclude("Vachequiri", "Iwik");
  s.exclude("Rimapita", "Iwik");
  s.exclude("Simon", "Iwik");
  s.exclude("Simon", "Vachequiri");
  s.exclude("Bastious", "Dwarf");

  auto r = s.draw();
  for (const auto& kv : r)
  {
    std::cout << kv.first << ": " << kv.second << std::endl;
  }
}
