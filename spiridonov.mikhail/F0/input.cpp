#include "input.hpp"
#include <iostream>
#include <string>
#include <functional>
#include <stdexcept>
#include <limits>
#include <map>

namespace spiridonov
{
  void process_commands(dictionaries_t& dicts)
  {
    using namespace std::placeholders;

    std::map< std::string, std::function< void(std::istream&, dictionaries_t&) > > cmds;
    cmds["create"] = std::bind(create_dict, _1, _2);
    cmds["load"] = std::bind(load_dict, _1, _2);
    cmds["add_word"] = std::bind(add_word, _1, _2);
    cmds["remove_word"] = std::bind(remove_word, _1, _2);
    cmds["find"] = std::bind(find_freq, _1, _2);
    cmds["display"] = std::bind(display_dict, _1, _2, std::ref(std::cout));
    cmds["merge"] = std::bind(merge_dicts, _1, _2);
    cmds["save"] = std::bind(save_to_file, _1, _2);
    cmds["compare"] = std::bind(compare_dicts, _1, _2);
    cmds["intersect"] = std::bind(intersect_dict, _1, _2);
    cmds["diff"] = std::bind(diff_dict, _1, _2);
    cmds["union"] = std::bind(union_dict, _1, _2);
    cmds["dict_ff"] = std::bind(dict_from_file, _1, _2);

    std::string cmd;
    while (std::cin >> cmd)
    {
      try
      {
        cmds.at(cmd)(std::cin, dicts);
      }
      catch (const std::exception&)
      {
        std::cout << "<INVALID COMMAND>" << '\n';
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
