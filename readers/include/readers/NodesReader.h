#ifndef _NODES_READER_H_
#define _NODES_READER_H_

#include "readers/SectionReader.h"


class NodesReader : public SectionReader
{
public:
  NodesReader() : SectionReader("$Nodes", "$EndNodes")
  {}

  void readSection(std::ifstream &f) override;
  void accept(MeshBuilderVisitor &v) override;
};

#endif