#ifndef _READ_TYPE_H_
#define _READ_TYPE_H_

namespace Utils {

template <typename T, typename StreamType>
T readType(StreamType &s)
{
  T t;
  s >> t;
  return t;
}

}

#endif