#include "pybind11/pybind11.h"

namespace py = pybind11;

void MshReader_binding(py::module &m);


PYBIND11_MODULE(Readers, m)
{
  MshReader_binding(m);
}