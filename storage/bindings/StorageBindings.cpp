#include "pybind11/pybind11.h"

namespace py = pybind11;

void ContiguousDataStore_binding(py::module &m);

PYBIND11_MODULE(Storage, m)
{
  ContiguousDataStore_binding(m);
}