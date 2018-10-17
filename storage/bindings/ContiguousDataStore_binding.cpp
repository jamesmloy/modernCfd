#include "storage/ContiguousDataStore.h"

#include "pybind11/pybind11.h"

namespace py = pybind11;

void ContiguousDataStore_binding(py::module &m)
{
  py::class_<ContiguousDataStore> cdsClass(m, "ContiguousDataStore");

  cdsClass.def(py::init<int>());

  m.def("addData_double", &addData<double>, "Add double storage");
}