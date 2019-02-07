#ifndef _ELEMENTS_READER_H_
#define _ELEMENTS_READER_H_

#include "readers/SectionReader.h"

#include <map>
#include <vector>


class ElementsReader : public SectionReader
{
public:
  ElementsReader() : SectionReader("$Elements", "$EndElements")
  {}

  void readSection(std::ifstream &f) override;
  void accept(MeshBuilderVisitor &v) override;

private:
  using FaceVerts = std::vector<std::vector<int>>;
  FaceVerts _faceVerts;
};

#endif