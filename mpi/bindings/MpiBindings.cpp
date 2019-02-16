#include "pybind11/pybind11.h"
#include <mpi.h>
#include <mpi4py/mpi4py.h>

#include <iostream>

namespace py = pybind11;

void pyHello(py::object &obj)
{
  PyObject* pobj = obj.ptr();
  MPI_Comm* comm = PyMPIComm_Get(pobj);

  // Get the number of processes
  int world_size = 0;
  MPI_Comm_size(*comm, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(*comm, &world_rank);

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  // Print off a hello world message
  std::cout << "Hello world from processor " << processor_name << ", rank "
            << world_rank << " out of " << world_size
            << "\n";
}

PYBIND11_MODULE(CfdMpi, m)
{
  import_mpi4py();

  m.def("pyHello", &pyHello, "testing hello world");
}