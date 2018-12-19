#include "readers/EntitiesReader.h"

#include "utils/PrintElements.h"


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


void EntitiesReader::addEdgeChildren(std::vector<int> &&c)
{
  _edgeChildren.emplace_back(c);
}


void EntitiesReader::addFaceChildren(std::vector<int> &&c)
{
  _faceChildren.emplace_back(c);
}


void EntitiesReader::addVolChildren(std::vector<int> &&c)
{
  _volChildren.emplace_back(c);
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
  Utils::printElements(s, e._vertIds);
  s << "\n";

  s << "\nEdge Ids: ";
  Utils::printElements(s, e._edgeIds);
  s << "\n";

  for_each(std::begin(e._edgeChildren), std::end(e._edgeChildren),
           [&s] (std::vector<int> const& v)
           {
             s << "Edge children: ";
             Utils::printElements(s, v);
             s << "\n";
           });

  s << "\nFace Ids: ";
  Utils::printElements(s, e._faceIds);
  s << "\n";

  for_each(std::begin(e._faceChildren), std::end(e._faceChildren),
           [&s] (std::vector<int> const& v)
           {
             s << "Face children: ";
             Utils::printElements(s, v);
             s << "\n";
           });

  s << "\nVolume Ids: ";
  Utils::printElements(s, e._volIds);
  s << "\n";

  for_each(std::begin(e._volChildren), std::end(e._volChildren),
           [&s] (std::vector<int> const& v)
           {
             s << "Volume children: ";
             Utils::printElements(s, v);
             s << "\n";
           });

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
      addVert(std::get<0>(eInfo));
    }

    for (int i = 0; i != nEdges; ++i)
    {
      auto eInfo = parseEntity(f);
      addEdge(std::get<0>(eInfo));
      addEdgeChildren(std::move(std::get<1>(eInfo)));
    }

    for (int i = 0; i != nFaces; ++i)
    {
      auto eInfo = parseEntity(f);
      addFace(std::get<0>(eInfo));
      addFaceChildren(std::move(std::get<1>(eInfo)));
    }

    for (int i = 0; i != nVols; ++i)
    {
      auto eInfo = parseEntity(f);

      std::cout << "parsed volume entity # " << i << ", with id "
                << std::get<0>(eInfo) << std::endl;
      addVol(std::get<0>(eInfo));
      addVolChildren(std::move(std::get<1>(eInfo)));
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