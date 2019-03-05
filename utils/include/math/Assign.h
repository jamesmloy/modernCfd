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

  namespace detail
  {
    template <typename T, size_t N, size_t M>
    struct AssignNM
    {
      static inline void
      call(blaze::StaticVector<T, N> &to,
           blaze::StaticVector<T, M> const &from,
           std::true_type nGreaterThanM)
      {
        for (int i = 0; i != M; ++i)
          to[i] = from[i];
        for (int i = M; i != N; ++i)
          to[i] = T(0);
      }

      static inline void
      call(blaze::StaticVector<T, N> &to,
           blaze::StaticVector<T, M> const &from,
           std::false_type mGreaterThanN)
      {
        for (int i = 0; i != N; ++i)
          to[i] = from[i];
      }
    };
  }

  /// assign 2 static vectors of different size
  template <typename T, size_t N, size_t M>
  void
  assign(blaze::StaticVector<T, N> &to, blaze::StaticVector<T, M> const &from)
  {
    using NMRelation = std::integral_constant<bool, (N > M)>;
    detail::AssignNM<T, N, M>::call(to, from, NMRelation());
  }
}

#endif