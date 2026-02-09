#include <MAT_Arc.hpp>
#include <MAT_Node.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MAT_Arc, Standard_Transient)

MAT_Arc::MAT_Arc(const int                        ArcIndex,
                 const int                        GeomIndex,
                 const occ::handle<MAT_BasicElt>& FirstElement,
                 const occ::handle<MAT_BasicElt>& SecondElement)
    : arcIndex(ArcIndex),
      geomIndex(GeomIndex),
      firstArcLeft(nullptr),
      firstArcRight(nullptr),
      secondArcRight(nullptr),
      secondArcLeft(nullptr)
{
  firstElement  = FirstElement;
  secondElement = SecondElement;
}

int MAT_Arc::Index() const
{
  return arcIndex;
}

int MAT_Arc::GeomIndex() const
{
  return geomIndex;
}

occ::handle<MAT_BasicElt> MAT_Arc::FirstElement() const
{
  return firstElement;
}

occ::handle<MAT_BasicElt> MAT_Arc::SecondElement() const
{
  return secondElement;
}

occ::handle<MAT_Node> MAT_Arc::FirstNode() const
{
  return firstNode;
}

occ::handle<MAT_Node> MAT_Arc::SecondNode() const
{
  return secondNode;
}

occ::handle<MAT_Node> MAT_Arc::TheOtherNode(const occ::handle<MAT_Node>& aNode) const
{
  if (FirstNode() == aNode)
    return SecondNode();
  else if (SecondNode() == aNode)
    return FirstNode();
  else
  {
    throw Standard_DomainError("MAT_Arc::TheOtherNode");
  }
}

bool MAT_Arc::HasNeighbour(const occ::handle<MAT_Node>& aNode, const MAT_Side aSide) const
{
  if (aSide == MAT_Left)
  {

    if (aNode == FirstNode())
      return (firstArcLeft != nullptr);

    if (aNode == SecondNode())
      return (secondArcLeft != nullptr);
  }
  else
  {

    if (aNode == FirstNode())
      return (firstArcRight != nullptr);

    if (aNode == SecondNode())
      return (secondArcRight != nullptr);
  }
  throw Standard_DomainError("MAT_Arc::HasNeighbour");
}

occ::handle<MAT_Arc> MAT_Arc::Neighbour(const occ::handle<MAT_Node>& aNode,
                                        const MAT_Side               aSide) const

{
  if (aSide == MAT_Left)
  {
    if (aNode == FirstNode())
      return (MAT_Arc*)firstArcLeft;
    if (aNode == SecondNode())
      return (MAT_Arc*)secondArcLeft;
  }
  else
  {
    if (aNode == FirstNode())
      return (MAT_Arc*)firstArcRight;
    if (aNode == SecondNode())
      return (MAT_Arc*)secondArcRight;
  }
  throw Standard_DomainError("MAT_Arc::Neighbour");
}

void MAT_Arc::SetIndex(const int anInteger)
{
  arcIndex = anInteger;
}

void MAT_Arc::SetGeomIndex(const int anInteger)
{
  geomIndex = anInteger;
}

void MAT_Arc::SetFirstElement(const occ::handle<MAT_BasicElt>& aBasicElt)
{
  firstElement = aBasicElt;
}

void MAT_Arc::SetSecondElement(const occ::handle<MAT_BasicElt>& aBasicElt)
{
  secondElement = aBasicElt;
}

void MAT_Arc::SetFirstNode(const occ::handle<MAT_Node>& aNode)
{
  firstNode = aNode;
}

void MAT_Arc::SetSecondNode(const occ::handle<MAT_Node>& aNode)
{
  secondNode = aNode;
}

void MAT_Arc::SetFirstArc(const MAT_Side aSide, const occ::handle<MAT_Arc>& anArc)
{
  if (aSide == MAT_Left)
    firstArcLeft = anArc.get();
  else
    firstArcRight = anArc.get();
}

void MAT_Arc::SetSecondArc(const MAT_Side aSide, const occ::handle<MAT_Arc>& anArc)
{
  if (aSide == MAT_Left)
    secondArcLeft = anArc.get();
  else
    secondArcRight = anArc.get();
}

void MAT_Arc::SetNeighbour(const MAT_Side               aSide,
                           const occ::handle<MAT_Node>& aNode,
                           const occ::handle<MAT_Arc>&  anArc)
{
  if (aSide == MAT_Left)
  {
    if (aNode == FirstNode())
      firstArcLeft = anArc.get();
    else if (aNode == SecondNode())
      secondArcLeft = anArc.get();
    else
      throw Standard_DomainError("MAT_Arc::SetNeighbour");
  }
  else
  {
    if (aNode == FirstNode())
      firstArcRight = anArc.get();
    else if (aNode == SecondNode())
      secondArcRight = anArc.get();
    else
      throw Standard_DomainError("MAT_Arc::SetNeighbour");
  }
}
