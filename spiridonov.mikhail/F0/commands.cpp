#include "commands.hpp"
#include <iostream>
#include <fstream>
#include <map>

void spiridonov::create_dict(std::istream& in, dictionaries_t& dicts)
{
  std::string name;
  in >> name;
  if (dicts.find(name) != dicts.end())
  {
    std::cerr << "<NAME IS BUSY>\n";
    return;
  }
  else
  {
    dicts[name] = dict_t();
  }
}

void spiridonov::load_dict(std::istream& in, dictionaries_t& dicts)
{
  std::string name, filename, word;
  in >> name >> filename;
  dicts[name] = dict_t();
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "<FILE NOT FOUND>\n";
    return;
  }
  int freq = 0;
  while (file >> word >> freq)
  {
    dict_t& dict_t = dicts.at(name);
    dict_t[word] += freq;
  }
}

void spiridonov::add_word(std::istream& in, dictionaries_t& dicts)
{
  std::string name, word, frequency_str;
  in >> name >> word >> frequency_str;
  int frequency = 0;
  try
  {
    frequency = std::stoi(frequency_str);
  }
  catch (const std::invalid_argument&)
  {
    std::cerr << "<BAD VALUE>\n";
    return;
  }
  try
  {
    dict_t& dict_t = dicts.at(name);
    dict_t[word] += frequency;
  }
  catch (const std::out_of_range&)
  {
    std::cerr << "<DICTIONARY NOT FOUND>\n";
  }
}

void spiridonov::remove_word(std::istream& in, dictionaries_t& dicts)
{
  std::string name, word;
  in >> name >> word;
  dict_t& dict_t = dicts.at(name);
  auto it = dict_t.find(word);
  if (it != dict_t.end())
  {
    dict_t.erase(it);
  }
  else
  {
    std::cout << "<WORD NOT FOUND>\n";
  }
}

void spiridonov::find_freq(std::istream& in, dictionaries_t& dicts)
{
  std::string name, word;
  in >> name >> word;
  const dict_t& dict_t = dicts.at(name);
  auto it = dict_t.find(word);
  if (it != dict_t.cend())
  {
    std::cout << it->second << "\n";
  }
  else
  {
    std::cout << "<WORD NOT FOUND>\n";
  }
}

void spiridonov::display_dict(std::istream& in, const dictionaries_t& dicts, std::ostream& out)
{
  std::string in_dict_name;
  in >> in_dict_name;
  const dict_t& in_dict = dicts.at(in_dict_name);
  if (in_dict.empty())
  {
    std::cerr << "<DICTIONARY IS EMPTY>\n";
    return;
  }
  out << in_dict_name << ":";
  for (const auto& pair : in_dict)
  {
    out << " " << pair.first << " " << pair.second;
  }
  out << "\n";
}

void spiridonov::merge_dicts(std::istream& in, dictionaries_t& dicts)
{
  std::string new_name, first_name, second_name;
  in >> new_name >> first_name >> second_name;
  if (dicts.find(first_name) == dicts.end() ||
    dicts.find(second_name) == dicts.end() ||
    first_name == second_name)
  {
    std::cerr << "<MERGE ERROR>\n";
    return;
  }
  dict_t& first = dicts.at(first_name);
  dict_t& second = dicts.at(second_name);
  dict_t res = first;
  for (const auto& pair : second)
  {
    res[pair.first] += pair.second;
  }
  dicts[new_name] = std::move(res);
}

void spiridonov::save_to_file(std::istream& in, dictionaries_t& dicts)
{
  std::string name, filename;
  in >> filename >> name;
  const dict_t& dict_t = dicts.at(name);
  std::ofstream file(filename);
  if (dict_t.empty())
  {
    std::cerr << "<DICTIONARY IS EMPTY>\n";
    return;
  }
  for (const auto& pair : dict_t)
  {
    file << pair.first << " " << pair.second << "\n";
  }
}

void spiridonov::compare_dicts(std::istream& in, dictionaries_t& dicts)
{
  std::string first_name, second_name;
  in >> first_name >> second_name;
  const dict_t& first = dicts.at(first_name);
  const dict_t& second = dicts.at(second_name);

  for (const auto& pair : first)
  {
    if (second.find(pair.first) == second.end())
    {
      std::cout << "\"" << pair.first << "\" is not in " << second_name << "\n";
    }
  }
  for (const auto& pair : second)
  {
    if (first.find(pair.first) == first.end())
    {
      std::cout << "\"" << pair.first << "\" is not in " << first_name << "\n";
    }
  }
}

void spiridonov::intersect_dict(std::istream& in, dictionaries_t& dicts)
{
  std::string new_name, first_name, second_name;
  in >> new_name >> first_name >> second_name;
  if (dicts.find(first_name) == dicts.end() ||
    dicts.find(second_name) == dicts.end())
  {
    std::cerr << "<DICTIONARY NOT FOUND>\n";
    return;
  }
  if (dicts.find(new_name) != dicts.end())
  {
    std::cerr << "<NAME IS BUSY>\n";
    return;
  }
  const auto& first = dicts.at(first_name);
  const auto& second = dicts.at(second_name);
  dict_t res;
  for (const auto& pair : first)
  {
    if (second.find(pair.first) != second.end())
    {
      res.insert(pair);
    }
  }
  dicts.insert({ new_name, res });
  if (res.empty())
  {
    std::cout << "<DICTIONARY IS EMPTY>\n";
  }
}

void spiridonov::diff_dict(std::istream& in, dictionaries_t& dicts)
{
  std::string new_name, first_name, second_name;
  in >> new_name >> first_name >> second_name;
  const auto& first = dicts.at(first_name);
  const auto& second = dicts.at(second_name);
  dict_t res;

  for (const auto& pair : first)
  {
    auto it = second.find(pair.first);
    if (it == second.end() || it->second != pair.second)
    {
      res.insert(pair);
    }
  }
  dicts.insert({ new_name, res });
}

void spiridonov::union_dict(std::istream& in, dictionaries_t& dicts)
{
  std::string new_name, first_name, second_name;
  in >> new_name >> first_name >> second_name;
  try
  {
    const auto& first = dicts.at(first_name);
    const auto& second = dicts.at(second_name);

    dict_t res = first;

    for (const auto& pair : second)
    {
      auto it = res.find(pair.first);
      if (it != res.end())
      {
        it->second += pair.second;
      }
      else
      {
        res.insert(pair);
      }
    }
    dicts.insert({ new_name, res });
  }
  catch (const std::out_of_range&)
  {
    std::cerr << "<SOME DICTIONARY NOT FOUND>\n";
  }
}

void spiridonov::dict_from_file(std::istream& in, dictionaries_t& dicts)
{
  std::string filename, name, word;
  in >> filename >> name;
  dicts.insert({ name, dict_t() });
  std::ifstream file(filename);
  auto& dict = dicts.at(name);
  while (file >> word)
  {
    ++dict[word];
  }
}
