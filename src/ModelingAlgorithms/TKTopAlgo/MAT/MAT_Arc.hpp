#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <MAT_Side.hpp>
class MAT_BasicElt;
class MAT_Node;

class MAT_Arc : public Standard_Transient
{

public:
  Standard_EXPORT MAT_Arc(const int                        ArcIndex,
                          const int                        GeomIndex,
                          const occ::handle<MAT_BasicElt>& FirstElement,
                          const occ::handle<MAT_BasicElt>& SecondElement);

  Standard_EXPORT int Index() const;

  Standard_EXPORT int GeomIndex() const;

  Standard_EXPORT occ::handle<MAT_BasicElt> FirstElement() const;

  Standard_EXPORT occ::handle<MAT_BasicElt> SecondElement() const;

  Standard_EXPORT occ::handle<MAT_Node> FirstNode() const;

  Standard_EXPORT occ::handle<MAT_Node> SecondNode() const;

  Standard_EXPORT occ::handle<MAT_Node> TheOtherNode(const occ::handle<MAT_Node>& aNode) const;

  Standard_EXPORT bool HasNeighbour(const occ::handle<MAT_Node>& aNode, const MAT_Side aSide) const;

  Standard_EXPORT occ::handle<MAT_Arc> Neighbour(const occ::handle<MAT_Node>& aNode,
                                                 const MAT_Side               aSide) const;

  Standard_EXPORT void SetIndex(const int anInteger);

  Standard_EXPORT void SetGeomIndex(const int anInteger);

  Standard_EXPORT void SetFirstElement(const occ::handle<MAT_BasicElt>& aBasicElt);

  Standard_EXPORT void SetSecondElement(const occ::handle<MAT_BasicElt>& aBasicElt);

  Standard_EXPORT void SetFirstNode(const occ::handle<MAT_Node>& aNode);

  Standard_EXPORT void SetSecondNode(const occ::handle<MAT_Node>& aNode);

  Standard_EXPORT void SetFirstArc(const MAT_Side aSide, const occ::handle<MAT_Arc>& anArc);

  Standard_EXPORT void SetSecondArc(const MAT_Side aSide, const occ::handle<MAT_Arc>& anArc);

  Standard_EXPORT void SetNeighbour(const MAT_Side               aSide,
                                    const occ::handle<MAT_Node>& aNode,
                                    const occ::handle<MAT_Arc>&  anArc);

  DEFINE_STANDARD_RTTIEXT(MAT_Arc, Standard_Transient)

private:
  int                       arcIndex;
  int                       geomIndex;
  occ::handle<MAT_BasicElt> firstElement;
  occ::handle<MAT_BasicElt> secondElement;
  occ::handle<MAT_Node>     firstNode;
  occ::handle<MAT_Node>     secondNode;
  void*                     firstArcLeft;
  void*                     firstArcRight;
  void*                     secondArcRight;
  void*                     secondArcLeft;
};
