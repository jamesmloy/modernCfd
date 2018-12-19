#ifndef _ENTITIES_READER_H_
#define _ENTITIES_READER_H_

#include "readers/SectionReader.h"

#include <regex>

class EntitiesReader : public SectionReader
{
  std::regex _countsRe{"(\\d+) (\\d+) (\\d+) (\\d+)"};

  using ChildrenList = std::vector<std::vector<int>>;

  std::vector<int> _vertIds;
  std::vector<int> _edgeIds;
  ChildrenList _edgeChildren;
  std::vector<int> _faceIds;
  ChildrenList _faceChildren;
  std::vector<int> _volIds;
  ChildrenList _volChildren;

  void initializeIds(int const nv, int const ne, int const nf, int const nvol);

  void addVert(int const id) { _vertIds.push_back(id); }
  void addEdge(int const id) { _edgeIds.push_back(id); }
  void addFace(int const id) { _faceIds.push_back(id); }
  void addVol(int const id) { _volIds.push_back(id); }

  friend std::ostream &operator<<(std::ostream &s, EntitiesReader const &e);

public:
  EntitiesReader() : SectionReader("$Entities", "$EndEntities") {}

  void readSection(std::ifstream &f) override;
  void accept(MeshBuilderVisitor &v) override;
};

#endif