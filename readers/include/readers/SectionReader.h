#ifndef _SECTION_READER_H_
#define _SECTION_READER_H_

#include <string>
#include <iostream>
#include <fstream>

// forward declare
class MeshBuilderVisitor;

class SectionReader
{
  std::string const _begLabel, _endLabel;
public:
  SectionReader(std::string begLabel, std::string endLabel)
    : _begLabel(std::move(begLabel))
    , _endLabel(std::move(endLabel))
  {}

  virtual ~SectionReader() {}

  std::string const & beginLabel()
  { return _begLabel; }

  std::string const & endLabel()
  { return _endLabel; }

  virtual void readSection(std::ifstream &f) = 0;
  virtual void accept(MeshBuilderVisitor &v) = 0;
};


void scanSection(std::string const &endTag, std::ifstream &f);

#endif