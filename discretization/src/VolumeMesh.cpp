#include "discretization/VolumeMesh.h"

#include <stdexcept>

VolumeMesh::
VolumeMesh(StorageSite const &cells, StorageSite const &faces,
           StorageSite const &vertices)
  : _cells(cells)
  , _faces(faces)
  , _vertices(vertices)
{}


CrConnectivity const*
VolumeMesh::hasConnectivity(StorageSite const& from, StorageSite const &to) const
{
  auto sites = std::make_pair(&from, &to);
  auto found = _connectivities.find(sites);

  if (found == end(_connectivities))
    return nullptr;
  else
    return found->second.get();
}


CrConnectivity const&
VolumeMesh::
getConnectivity(StorageSite const& from, StorageSite const &to) const
{
  CrConnectivity const *conn = hasConnectivity(from, to);
  if (!conn)
    throw std::runtime_error("Attempting to get connectivity that cannot be found");
  return *conn;
}