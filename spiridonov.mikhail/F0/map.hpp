#ifndef MAP_HPP
#define MAP_HPP

#include <map>
#include <string>

namespace spiridonov
{
  using dict_t = std::map< std::string, int >;
  using dictionaries_t = std::map< std::string, dict_t >;

  class Map
  {
  public:
    using iterator = dict_t::iterator;
    using const_iterator = dict_t::const_iterator;

    int& operator[](const std::string& key)
    {
      return dict_[key];
    }

    const int& operator[](const std::string& key) const
    {
      return dict_.at(key);
    }

    void insert(const std::string& key, int value)
    {
      dict_[key] += value;
    }

    void erase(const std::string& key)
    {
      dict_.erase(key);
    }

    iterator begin()
    {
      return dict_.begin();
    }
    iterator end()
    {
      return dict_.end();
    }
    const_iterator cbegin() const
    {
      return dict_.cbegin();
    }
    const_iterator cend() const
    {
      return dict_.cend();
    }

    bool empty() const
    {
      return dict_.empty();
    }

  private:
    dict_t dict_;
  };

  class mainDictsTree
  {
  public:
    const dict_t& at(const std::string& name) const
    {
      return dictionaries_.at(name);
    }
    dict_t& at(const std::string& name)
    {
      return dictionaries_.at(name);
    }

    void insert(const std::pair< std::string, dict_t >& pair)
    {
      dictionaries_.insert(pair);
    }

  private:
    dictionaries_t dictionaries_;
  };
}

#endif
