#include "readers/EntitiesReader.h"


namespace {

std::tuple<int, std::vector<int>>
parseEntity(std::ifstream &f, bool hasChildren = true)
{
  int id{0};
  f >> id;

  int dummy;
  for (int i = 0; i != 6; ++i)
    f >> dummy;

  int numPhysical;
  f >> numPhysical;
  for (int i = 0; i != numPhysical; ++i)
    f >> dummy;

  std::vector<int> children;

  if (hasChildren)
  {
    int numChildren;
    f >> numChildren;

    children.reserve(numChildren);

    for (int i = 0; i != numChildren; ++i)
    {
      int child;
      f >> child;
      children.push_back(child);
    }
  }

  return {id, children};
}

}


void EntitiesReader::initializeIds(int const nv, int const ne, int const nf,
                                   int const nvol)
{
  _vertIds.clear();
  _vertIds.reserve(nv);

  _edgeIds.clear();
  _edgeIds.reserve(ne);

  _faceIds.clear();
  _faceIds.reserve(nf);

  _volIds.clear();
  _volIds.reserve(nvol);
}

std::ostream &operator<<(std::ostream &s, EntitiesReader const &e)
{
  s << "Vertex Ids: ";
  for_each(begin(e._vertIds), end(e._vertIds),
           [&s](int const &i) { s << i << " "; });

  s << "\nEdge Ids: ";
  for_each(begin(e._edgeIds), end(e._edgeIds),
           [&s](int const &i) { s << i << " "; });

  s << "\nFace Ids: ";
  for_each(begin(e._faceIds), end(e._faceIds),
           [&s](int const &i) { s << i << " "; });

  s << "\nVolume Ids: ";
  for_each(begin(e._volIds), end(e._volIds),
           [&s](int const &i) { s << i << " "; });
  return s;
}

void EntitiesReader::readSection(std::ifstream &f)
{
  std::cout << "entites section\n";

  std::string ln;

  // first line is header
  getline(f, ln);
  std::cout << "first line: " << ln << std::endl;

  int nVerts(0);
  int nEdges(0);
  int nFaces(0);
  int nVols(0);

  try
  {
    f >> nVerts;
    f >> nEdges;
    f >> nFaces;
    f >> nVols; 

    std::cout << "nVerts: " << nVerts << ", nEdges: " << nEdges
              << ", nFaces: " << nFaces << ", nVols: " << nVols << std::endl;

    initializeIds(nVerts, nEdges, nFaces, nVols);

    for (int i = 0; i != nVerts; ++i)
    {
      auto eInfo = parseEntity(f, false);
      std::cout << "parsed vertex entity # " << i << ", with id "
                << std::get<0>(eInfo) << std::endl;

      addVert(std::get<0>(eInfo));
    }

    for (int i = 0; i != nEdges; ++i)
    {
      auto eInfo = parseEntity(f);

      std::cout << "parsed edge entity # " << i << ", with id "
                << std::get<0>(eInfo) << std::endl;
      addEdge(std::get<0>(eInfo));
    }

    for (int i = 0; i != nFaces; ++i)
    {
      auto eInfo = parseEntity(f);

      std::cout << "parsed face entity # " << i << ", with id "
                << std::get<0>(eInfo) << std::endl;
      addFace(std::get<0>(eInfo));
    }

    for (int i = 0; i != nVols; ++i)
    {
      auto eInfo = parseEntity(f);

      std::cout << "parsed volume entity # " << i << ", with id "
                << std::get<0>(eInfo) << std::endl;
      addVol(std::get<0>(eInfo));
    }

    scanSection(endLabel(), f);
  }
  catch (std::exception &e)
  {
    std::cout << "Entities failed with error: " << e.what() << std::endl;
    scanSection(endLabel(), f);
  }

  std::cout << "Entities reader:\n" << *this << std::endl;
}

void EntitiesReader::accept(MeshBuilderVisitor &v) {}