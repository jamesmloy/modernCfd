#ifndef _FORMAT_READER_H_
#define _FORMAT_READER_H_

#include "readers/SectionReader.h"

class FormatReader : public SectionReader
{
public:
  FormatReader() : SectionReader("$MeshFormat", "$EndMeshFormat")
  {}

  void readSection(std::ifstream &f) override;
  void accept(MeshBuilderVisitor &v) override;
};

#endif