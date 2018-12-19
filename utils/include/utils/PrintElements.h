#ifndef _PRINT_ELEMENTS_H_
#define _PRINT_ELEMENTS_H_

#include <iterator>

namespace Utils {

template <typename Stream, typename Collection>
void printElements(Stream &s, Collection const &coll)
{
  using ConstRef = typename Collection::const_reference;
  struct Printer
  {
    Printer(Stream &s) : s(s) {}
    void operator()(ConstRef i)
    { s << i << " "; }
    Stream &s;
  };

  for_each(std::begin(coll), std::end(coll), Printer(s));
}

}

#endif