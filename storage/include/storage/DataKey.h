#ifndef _DATA_KEY_H_
#define _DATA_KEY_H_

#include <string>
#include <functional>


struct DataKey
{
  DataKey(std::string tag, std::string typeTag);

  std::string tag;
  std::string typeTag;
  size_t hash;
};

template <>
struct std::hash<DataKey const>
{
  size_t operator()(DataKey const &k) const
  {
    return std::hash<std::string>{}(k.tag + k.typeTag);
  }
};


bool operator==(DataKey const &a, DataKey const &b)
{
  return a.hash == b.hash;
}


#endif