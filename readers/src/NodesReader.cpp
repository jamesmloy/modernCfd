  #include "readers/NodesReader.h"


  void NodesReader::readSection(std::ifstream &f)
  {
    std::cout << "nodes section\n";
    scanSection(endLabel(), f);
  }


  void NodesReader::accept(MeshBuilderVisitor &v)
  {}