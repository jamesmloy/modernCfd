#include "pybind11/pybind11.h"

#include "readers/MshReader.h"

namespace py = pybind11;

void MshReader_binding(py::module &m)
{
  py::class_<MshReader> cls(m, "MshReader");

  cls.def(py::init());
  cls.def("readMesh", &MshReader::readMesh, "Read a .msh file");
}