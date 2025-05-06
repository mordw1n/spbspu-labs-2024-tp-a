#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <fstream>
#include <iostream>
#include <string>
#include "map.hpp"

namespace spiridonov
{
  void create_dict(std::istream& in, dictionaries_t& dicts);
  void load_dict(std::istream& in, dictionaries_t& dicts);
  void add_word(std::istream& in, dictionaries_t& dicts);
  void remove_word(std::istream& in, dictionaries_t& dicts);
  void find_freq(std::istream& in, dictionaries_t& dicts);
  void display_dict(std::istream& in, const dictionaries_t& dicts, std::ostream& out);
  void merge_dicts(std::istream& in, dictionaries_t& dicts);
  void save_to_file(std::istream& in, dictionaries_t& dicts);
  void compare_dicts(std::istream& in, dictionaries_t& dicts);
  void intersect_dict(std::istream& in, dictionaries_t& dicts);
  void diff_dict(std::istream& in, dictionaries_t& dicts);
  void union_dict(std::istream& in, dictionaries_t& dicts);
  void dict_from_file(std::istream& in, dictionaries_t& dicts);
}

#endif
