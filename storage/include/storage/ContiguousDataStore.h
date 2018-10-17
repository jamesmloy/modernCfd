#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include <iostream>
#include <stdexcept>

#include "storage/DataKey.h"

#include "numeric/NumericTraits.h"

#include "blaze/math/DynamicVector.h"


class DataHandle
{
public:
  virtual ~DataHandle() {}
};


template <typename T>
class SpecificDataHandle : public DataHandle
{
public:
  SpecificDataHandle(std::unique_ptr<blaze::DynamicVector<T>> v)
  : _v(std::move(v))
  {}

  blaze::DynamicVector<T>& getData()
  {
    return *_v;
  }

private:
  std::unique_ptr<blaze::DynamicVector<T>> _v;
};


class ContiguousDataStore
{
public:
  ContiguousDataStore(int const numElements)
  : _size(numElements)
  {}

  template <typename T>
  blaze::DynamicVector<T>& getData(std::string const &name)
  {
    auto k = createKey<T>(name);

    auto it = _dataMap.find(k);

    if (it == std::end(_dataMap))
      throw std::runtime_error("Storage doesnt exist");

    auto &handle = *static_cast<SpecificDataHandle<T>*>(it->second.get());

    return handle.getData();
  }

private:

  template <typename T>
  static DataKey createKey(std::string const &name)
  {
    return DataKey(name, NumericTraits<T>::tag());
  }

  template <typename T>
  std::unique_ptr<blaze::DynamicVector<T>>
  allocateData() const
  {
    return std::make_unique<blaze::DynamicVector<T>>(_size);
  }

  void assertStorageDoesntExist(DataKey const &k) const
  {
    bool const exists = _dataMap.find(k) != std::end(_dataMap);

    if (exists)
      throw std::runtime_error("Data already exists");
  }

  template <typename T>
  friend void addData(ContiguousDataStore &, std::string&);

  int _size;
  std::unordered_map<DataKey const, std::unique_ptr<DataHandle>> _dataMap;
};


template <typename T>
void addData(ContiguousDataStore &store, std::string &name)
{
  auto k = store.template createKey<T>(name);
  store.assertStorageDoesntExist(k);

  auto d = store.template allocateData<T>();
  (*d) = T(0);

  std::unique_ptr<DataHandle> dh
    {std::make_unique<SpecificDataHandle<T>>(std::move(d))};

  store._dataMap.emplace(k, std::move(dh));
}