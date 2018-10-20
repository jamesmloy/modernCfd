#ifndef _STORAGE_SITE_H_
#define _STORAGE_SITE_H_


class StorageSite
{
public:

  StorageSite(int const selfCount, int const count);

  int count() const noexcept
  { return _count; }

  int selfCount() const noexcept
  { return _selfCount; }

private:
  int const _selfCount;
  int const _count;
};

#endif