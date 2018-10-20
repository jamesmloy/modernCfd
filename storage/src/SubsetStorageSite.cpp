#include "storage/SubsetStorageSite.h"

#include <stdexcept>


SubsetStorageSite::
SubsetStorageSite(int const count, int const offset,
                  StorageSite const &parent)
  : StorageSite(count, count)
  , _offset(offset)
  , _parent(parent)
{
  if (offset + count > parent.selfCount())
    throw std::runtime_error("Subset last offset must be less than parent self count");
}