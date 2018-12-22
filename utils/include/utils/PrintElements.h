#ifndef _PRINT_ELEMENTS_H_
#define _PRINT_ELEMENTS_H_

#include <algorithm>
#include <iterator>
#include <utility>

namespace Utils {

template <typename Stream, typename Collection>
void printElements(Stream &s, Collection const &coll)
{
  using ConstRef = decltype(*std::declval<Collection const>().begin());
  struct Printer
  {
    Printer(Stream &s) : s(s) {}
    void operator()(ConstRef i)
    { s << i << " "; }
    Stream &s;
  };

  std::for_each(std::begin(coll), std::end(coll), Printer(s));
}

}

#endif