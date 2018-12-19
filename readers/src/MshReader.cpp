#include "readers/MshReader.h"
#include "readers/ElementsReader.h"
#include "readers/EntitiesReader.h"
#include "readers/FormatReader.h"
#include "readers/MeshBuilderVisitor.h"
#include "readers/NodesReader.h"
#include "readers/PhysicalNamesReader.h"

#include "discretization/VolumeMesh.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>

namespace
{
using ReaderMap =
    std::unordered_map<std::string, std::unique_ptr<SectionReader>>;

ReaderMap getReaderMap()
{
  ReaderMap rMap;

  auto formatReader = std::make_unique<FormatReader>();
  rMap.emplace(formatReader->beginLabel(), std::move(formatReader));

  auto pnReader = std::make_unique<PhysicalNamesReader>();
  rMap.emplace(pnReader->beginLabel(), std::move(pnReader));

  auto entitiesReader = std::make_unique<EntitiesReader>();
  rMap.emplace(entitiesReader->beginLabel(), std::move(entitiesReader));

  auto nodesReader = std::make_unique<NodesReader>();
  rMap.emplace(nodesReader->beginLabel(), std::move(nodesReader));

  auto elementsReader = std::make_unique<ElementsReader>();
  rMap.emplace(elementsReader->beginLabel(), std::move(elementsReader));

  return rMap;
}
} // namespace

void MshReader::readMesh(std::string const fName)
{
  std::cout << "READING MESH from " << fName << "!\n";
  std::ifstream fStream(fName);

  if (fStream.is_open())
  {
    auto readers = getReaderMap();

    std::cout << "opened file!\n";
    std::string ln;

    auto posStart = fStream.tellg();
    std::cout << "initial position: " << posStart << "\n";
    auto const rEnd = end(readers);

    while (getline(fStream, ln))
    {
      auto posEnd = fStream.tellg();
      fStream.seekg(posStart);
      auto r = readers.find(ln);

      if (r != rEnd)
      {
        r->second->readSection(fStream);
        posStart = fStream.tellg();
      }
      else
        throw std::runtime_error("invalid section found");
    }
    fStream.close();
  }
  else
    throw std::runtime_error("could not open file");
}