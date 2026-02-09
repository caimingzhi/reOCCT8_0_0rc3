

#include <StepShape_EdgeLoop.hpp>
#include <StepShape_OrientedEdge.hpp>
#include <StepShape_OrientedPath.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_OrientedPath, StepShape_Path)

StepShape_OrientedPath::StepShape_OrientedPath() = default;

void StepShape_OrientedPath::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                  const occ::handle<StepShape_EdgeLoop>&       aPathElement,
                                  const bool                                   aOrientation)
{

  pathElement = aPathElement;
  orientation = aOrientation;

  occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>> aEdgeList;
  aEdgeList.Nullify();
  StepShape_Path::Init(aName, aEdgeList);
}

void StepShape_OrientedPath::SetPathElement(const occ::handle<StepShape_EdgeLoop>& aPathElement)
{
  pathElement = aPathElement;
}

occ::handle<StepShape_EdgeLoop> StepShape_OrientedPath::PathElement() const
{
  return pathElement;
}

void StepShape_OrientedPath::SetOrientation(const bool aOrientation)
{
  orientation = aOrientation;
}

bool StepShape_OrientedPath::Orientation() const
{
  return orientation;
}

void StepShape_OrientedPath::SetEdgeList(
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>>&)
{

  std::cout << "Field is redefined, SetUp Forbidden" << std::endl;
}

occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>> StepShape_OrientedPath::
  EdgeList() const
{

  if (orientation)
    return pathElement->EdgeList();
  else
  {

    return pathElement->EdgeList();
  }
}

occ::handle<StepShape_OrientedEdge> StepShape_OrientedPath::EdgeListValue(const int num) const
{

  if (orientation)
    return pathElement->EdgeListValue(num);
  else
  {
    int nbEdges = pathElement->NbEdgeList();
    return pathElement->EdgeListValue(nbEdges - num + 1);
  }
}

int StepShape_OrientedPath::NbEdgeList() const
{

  return pathElement->NbEdgeList();
}
