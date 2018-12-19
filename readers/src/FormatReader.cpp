#include "readers/FormatReader.h"

void FormatReader::readSection(std::ifstream &f)
{
  std::cout << "format section\n";
  scanSection(endLabel(), f);
}


void FormatReader::accept(MeshBuilderVisitor &v)
{
}