#include "storage/DataKey.h"


DataKey::DataKey(std::string tag, std::string typeTag)
: tag(tag)
, typeTag(typeTag)
{
  hash = std::hash<DataKey const>{}(*this);
}