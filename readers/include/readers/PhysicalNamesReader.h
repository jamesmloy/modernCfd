#ifndef _PHYSICAL_NAMES_READER_H_
#define _PHYSICAL_NAMES_READER_H_

#include "readers/SectionReader.h"

#include <regex>


class PhysicalNamesReader : public SectionReader
{
  std::regex _re{"(\\d+) (\\d+) \"(.+)\""};
public:
  PhysicalNamesReader() : SectionReader("$PhysicalNames", "$EndPhysicalNames")
  {}

  struct NameInfo
  {
    std::string const name;
    int const dim;
    int const id;

    NameInfo(std::string n, int d, int id)
      : name(std::move(n))
      , dim(d)
      , id(id)
    {}  
  };

  std::vector<NameInfo> names;

  void readSection(std::ifstream &f) override;
  void accept(MeshBuilderVisitor &v) override;

private:

  friend std::ostream& operator<<(std::ostream &s, NameInfo const &n)
  {
    s << "Name: " << n.name
      << ", dim: " << n.dim
      << ", id:" << n.id;
    return s;
  }

  void addName(std::string const& line)
  {
    std::smatch m;

    try
    {
      std::regex_search(line, m, _re);
    }
    catch (std::exception &e)
    {
      std::cout << e.what() << std::endl;
    }

    int const dim = std::stoi(m[1].str());
    int const id = std::stoi(m[2].str());

    names.emplace_back(m[3].str(), dim, id);
  }
};

#endif