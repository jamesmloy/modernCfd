#ifndef _ASSIGN_H_
#define _ASSIGN_H_

#include "blaze/math/StaticVector.h"

#include <array>

namespace MathUtils
{
  template <typename T, size_t N, bool TF = false>
  void
  assign(blaze::StaticVector<T, N, TF> &l, std::array<T, N> const &r)
  {
    std::copy(begin(r), end(r), begin(l));
  }
}

#endif