#include "pybind11/pybind11.h"

#include "blaze/math/DynamicVector.h"

#include "numeric/NumericTraits.h"

#include <string>

namespace py = pybind11;


template <typename T>
void scalarArray(py::module &m)
{
  using Array = blaze::DynamicVector<T>;
  auto n = NumericTraits<Array>::name();

  py::class_<Array> array(m, n.data(), py::buffer_protocol());

  auto getBuf = [] (Array &a) -> py::buffer_info
  {
    return
      py::buffer_info { blaze::data(a), sizeof(T),
                        py::format_descriptor<T>::format(),
                        1, { size(a) }, { sizeof(T) } };
  };

  array.def_buffer(getBuf);

  auto init = [] (int size)
  {
    auto a = std::make_unique<Array>(size);
    (*a) = T(0);
    return a;
  };

  array.def(py::init(init));
}

void Arrays_binding(py::module &m)
{
  scalarArray<double>(m);
  scalarArray<float>(m);
  scalarArray<int>(m);
  scalarArray<bool>(m);
}