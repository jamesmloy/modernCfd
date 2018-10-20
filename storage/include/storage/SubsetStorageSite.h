#ifndef _SUBSET_STORAGE_SITE_H_
#define _SUBSET_STORAGE_SITE_H_

#include "storage/StorageSite.h"


class SubsetStorageSite : public StorageSite
{
public:

  SubsetStorageSite(int const count, int const offset,
                    StorageSite const &parent);

  StorageSite const& parent() const noexcept
  { return _parent; }

  int offset() const noexcept
  { return _offset; }

private:
  int const _offset;
  StorageSite const &_parent;
};

#endif