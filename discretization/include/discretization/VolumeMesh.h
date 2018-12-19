#ifndef _VOLUME_MESH_H_
#define _VOLUME_MESH_H_

#include "storage/StorageSite.h"
#include "storage/SubsetStorageSite.h"

#include "connectivity/CrConnectivity.h"

#include <map>
#include <utility>
#include <vector>

class VolumeMesh
{
public:

  VolumeMesh(StorageSite const &cells, StorageSite const &faces,
             StorageSite const &vertices);

  using SitePair = std::pair<StorageSite const*, StorageSite const*>;
  using CrConnPtr = std::unique_ptr<CrConnectivity>;
  using SiteToConnectivityMap = std::map<SitePair const, CrConnPtr>;

  StorageSite&       cells()       noexcept
  { return _cells; }
  StorageSite const& cells() const noexcept
  { return _cells; }

  StorageSite&       faces()       noexcept
  { return _faces; }
  StorageSite const& faces() const noexcept
  { return _faces; }

  StorageSite&       vertices()       noexcept
  { return _vertices; }
  StorageSite const& vertices() const noexcept
  { return _vertices; }

  CrConnectivity const*
  hasConnectivity(StorageSite const& from, StorageSite const &to) const;

  CrConnectivity const&
  getConnectivity(StorageSite const& from, StorageSite const &to) const;

private:
  StorageSite _cells;
  StorageSite _faces;
  StorageSite _vertices;

  std::vector<SubsetStorageSite> _boundaries;

  SiteToConnectivityMap _connectivities;
};


#endif