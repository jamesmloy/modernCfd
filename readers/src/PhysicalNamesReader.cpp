#include "readers/PhysicalNamesReader.h"


void PhysicalNamesReader::readSection(std::ifstream &f)
{
  std::cout << "physical names section\n";
  std::string ln;

  // first line is the header
  getline(f, ln);

  // second line is number of entities
  getline(f, ln);

  try
  {
    int const nNames = std::stoi(ln);
    
    for (int i = 0; i != nNames; ++i)
    {
      getline(f, ln);

      addName(ln);
    }
  }
  catch (std::invalid_argument const &e)
  {
    std::cout << "Found invalid argument\n";
  }
  scanSection(endLabel(), f);

  for (auto const& n : names)
    std::cout << n << std::endl;
}


void PhysicalNamesReader::accept(MeshBuilderVisitor &v)
{
}