#include "readers/NodesReader.h"

#include "utils/PrintElements.h"
#include "utils/ReadType.h"

std::ostream &operator<<(std::ostream &s, NodesReader const &n)
{
  s << "NodesReader\nCoordinates:\n";
  Utils::printElements(s, n._coords);
  return s;
}


void NodesReader::readSection(std::ifstream &f)
{
  using namespace Utils;

  {
    // first line is header
    std::string ln;
    getline(f, ln);
  }

  int const sumTot = readType<int>(f);
  int const numVerts = readType<int>(f);

  _coords.resize(numVerts);

  int dummyI;
  int nv(0);
  int vId(0);

  for (int i = 0; i != sumTot; ++i)
  {
    // tag
    f >> dummyI;
    // dimension
    f >> dummyI;
    // save parametric
    f >> dummyI;

    // number of vertices
    nv = readType<int>(f);

    for (int v = 0; v != nv; ++v)
    {
      vId = readType<int>(f);
      Coord &pos = _coords[vId];
      pos[0] = readType<double>(f);
      pos[1] = readType<double>(f);
      pos[2] = readType<double>(f);
    }
  }

  scanSection(endLabel(), f);
}


void NodesReader::accept(MeshBuilderVisitor &v)
{}