#include <iostream>
#include "input.hpp"
#include "map.hpp"
#include "commands.hpp"

int main()
{
  using namespace spiridonov;
  dictionaries_t dicts;
  process_commands(dicts);
}
