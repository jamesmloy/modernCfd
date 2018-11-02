#include "connectivity/CrConnectivity.h"


CrConnectivity::
CrConnectivity(CrConnectivity::IndexArray offsets, CrConnectivity::IndexArray entries)
  : _offsets(std::move(offsets))
  , _entries(std::move(entries))
{
}