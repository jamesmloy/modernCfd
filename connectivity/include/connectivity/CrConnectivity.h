#ifndef _CRCONNECTIVITY_H_
#define _CRCONNECTIVITY_H_

#include "blaze/math/DynamicVector.h"

#include <utility>


class CrConnectivity
{
public:

  using IndexArray = blaze::DynamicVector<int>;

  CrConnectivity(IndexArray offsets, IndexArray entries);

  inline int const& neib(int const i, int const off) const
  {
    return _entries[_offsets[i] + off];
  }

  inline int count(int const i) const
  {
    return _offsets[i + 1] - _offsets[i];
  }

  using ConstIterator = IndexArray::ConstIterator;
  using ConstItPair = std::pair<ConstIterator, ConstIterator>;

  inline ConstItPair neibs(int const i) const
  {
    auto start = begin(_offsets) + i;
    auto finish = begin(_offsets) + i + 1;
    return std::make_pair(start, finish);
  }

private:
  IndexArray const _offsets;
  IndexArray const _entries;
};

#endif