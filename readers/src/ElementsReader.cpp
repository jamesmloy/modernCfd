#include "readers/ElementsReader.h"


void ElementsReader::readSection(std::ifstream &f)
{
  std::cout << "elements section\n";
  scanSection(endLabel(), f);
}


void ElementsReader::accept(MeshBuilderVisitor &v)
{}