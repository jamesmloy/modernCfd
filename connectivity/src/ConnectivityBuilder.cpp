#include "connectivity/ConnectivityBuilder.h"

#include <stdexcept>
#include <algorithm>
#include <iostream>


ConnectivityBuilder::
ConnectivityBuilder(int const nRows, int const nCols)
  : _nRows(nRows)
  , _nCols(nCols)
  , _offsets(nRows + 1, 0)
  , _entries()
{}


void
ConnectivityBuilder::
addCount(int const i, int const count)
{
  if (!(i < _nRows))
    throw std::runtime_error("adding count to invalid index");
  _offsets[i] += count;
}


void
ConnectivityBuilder::
finalizeCount()
{
  int nnz = 0;
  for (int i = 0; i < _nRows + 1; ++i)
  {
    int const cnt = _offsets[i];
    _offsets[i] = nnz;
    nnz += cnt;
  }

  _entries.resize(nnz + 1, false);
}


void
ConnectivityBuilder::
addEntry(int const i, int const j)
{
  if (!(i < _nRows))
    throw std::runtime_error("adding entry to invalid index");
  _entries[_offsets[i]++] = j;
}


std::unique_ptr<CrConnectivity>
ConnectivityBuilder::
makeConnectivity()
{
  auto const eBeg = begin(_entries);
  for (int i = 0; i < _nRows; ++i)
  {
    int const iStart = _offsets[i];
    int const iEnd = _offsets[i + 1];
    std::sort(eBeg + iStart, eBeg + iEnd);
  }

  int nnz = 0;
  for (int i = 0; i < _nRows + 1; ++i)
  {
    int const nnzOld = _offsets[i];
    _offsets[i] = nnz;
    nnz = nnzOld;
  }

  return std::make_unique<CrConnectivity>(std::move(_offsets), std::move(_entries));
}