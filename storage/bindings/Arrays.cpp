#include "pybind11/pybind11.h"

#include "blaze/math/DynamicVector.h"
#include "blaze/math/StaticVector.h"

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


template <typename T, int N>
void vectorArray_impl(py::module &m)
{
  using Vec = blaze::StaticVector<T,N>;
  using Array = blaze::DynamicVector<Vec>;
  auto n = NumericTraits<Array>::name();

  py::class_<Array> array(m, n.data(), py::buffer_protocol());

  auto getBuf = [] (Array &a) -> py::buffer_info
  {
    return
      py::buffer_info { blaze::data(a), sizeof(T),
                        py::format_descriptor<T>::format(),
                        2, std::vector<ssize_t>{ {ssize_t(size(a)), N} },
                        std::vector<ssize_t>{ {sizeof(T) * N, sizeof(T)} } };
  };

  array.def_buffer(getBuf);

  auto init = [] (size_t const vSize, T const& init)
  {
    auto a = std::make_unique<Array>(vSize);
    (*a) = Vec(init);
    return a;
  };

  array.def(py::init(init));
}


template <typename T, int I>
struct VectorArray
{
  static void bind(py::module &m)
  {
    static_assert(I > 1, "Static vectors of 2 components or more only");
    vectorArray_impl<T, I>(m);
    VectorArray<T, I-1>::bind(m);
  }
};


template <typename T>
struct VectorArray<T, 2>
{
  static void bind(py::module &m)
  {
    vectorArray_impl<T, 2>(m);
  }
};


void Arrays_binding(py::module &m)
{
  scalarArray<double>(m);
  scalarArray<float>(m);
  scalarArray<int>(m);
  scalarArray<bool>(m);

  VectorArray<double, 10>::bind(m);
  VectorArray<float, 10>::bind(m);
  VectorArray<int, 10>::bind(m);
  VectorArray<bool, 10>::bind(m);
}