#ifndef _NODES_READER_H_
#define _NODES_READER_H_

#include "readers/SectionReader.h"

#include "blaze/math/StaticVector.h"
#include "blaze/math/DynamicVector.h"


class NodesReader : public SectionReader
{
public:
  using Coord = blaze::StaticVector<double, 3, false>;
  using CoordArr = blaze::DynamicVector<Coord, false>;

  NodesReader() : SectionReader("$Nodes", "$EndNodes")
  {}

  void readSection(std::ifstream &f) override;
  void accept(MeshBuilderVisitor &v) override;

private:
  friend std::ostream &operator<<(std::ostream &s, NodesReader const &n);

  CoordArr _coords;
};

#endif