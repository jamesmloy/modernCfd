#ifndef _ELEMENTS_READER_H_
#define _ELEMENTS_READER_H_

#include "readers/SectionReader.h"


class ElementsReader : public SectionReader
{
public:
  ElementsReader() : SectionReader("$Elements", "$EndElements")
  {}

  void readSection(std::ifstream &f) override;
  void accept(MeshBuilderVisitor &v) override;
};

#endif