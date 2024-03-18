#include"dataStruct.hpp"

#include<string>

#include"delimeter.hpp"

std::istream& zaparin::operator>>(std::istream& in, zaparin::DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = Delimeter;

  in >> del{ "(" };
  size_t keysCount = 0;
  DataStruct temp{ 0, {0, 0}, "" };

  while (in && keysCount < 3)
  {
    size_t keyType = 0;
    in >> del{ ":key" } >> keyType;

    switch (keyType)
    {
    case 1:
      in >> del{ " 0b" } >> temp.key1;
      keysCount++;

    case 2:
      in >> del{ " (:N " } >> temp.key2.first >> del{ ":D " } >> temp.key2.second >> del{ ":)" };
      keysCount++;

    case 3:
      in >> del{ "\"" };
      std::getline(in, temp.key3, '\"');
      keysCount++;

    default:
      in.setstate(std::ios::failbit);
    }
  }

  in >> del{ ":)" };
  if (in)
  {
    data = temp;
  }

  return in;
}

