#include "storage/ContiguousDataStore.h"

//#include "numeric/NumericTraits.h"

#include "pybind11/pybind11.h"

namespace py = pybind11;

template <typename T>
void addData_b(py::module &m)
{
  auto const n = NumericTraits<T>::name();
  std::string const fName = std::string("addData_") + n;
  std::string const doc = std::string("Add ") + n + std::string("storage");
  m.def(fName.data(), &addData<double>, doc.data());
}

void ContiguousDataStore_binding(py::module &m)
{
  py::class_<ContiguousDataStore> cdsClass(m, "ContiguousDataStore");

  cdsClass.def(py::init<int>());

  addData_b<bool>(m);
  addData_b<int>(m);
  addData_b<float>(m);
  addData_b<double>(m);
}