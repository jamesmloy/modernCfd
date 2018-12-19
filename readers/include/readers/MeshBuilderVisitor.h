#ifndef _MESH_BUILDER_VISITOR_H_
#define _MESH_BUILDER_VISITOR_H_


class FormatReader;
class PhysicalNamesReader;
class EntitiesReader;
class NodesReader;
class ElementsReader;

class MeshBuilderVisitor
{
public:
  void processFormat(FormatReader &r);
  void processPhysicalNames(PhysicalNamesReader &r);
  void processEntities(EntitiesReader &r);
  void processNodes(NodesReader &r);
  void processElements(ElementsReader &r);
};

#endif