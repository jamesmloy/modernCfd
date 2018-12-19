#include "readers/SectionReader.h"

void scanSection(std::string const &endTag, std::ifstream &f)
{
  std::string ln;
  while (getline(f, ln))
  {
    if (ln == endTag)
      break;
  }
}