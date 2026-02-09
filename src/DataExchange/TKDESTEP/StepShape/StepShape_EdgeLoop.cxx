

#include <StepShape_EdgeLoop.hpp>
#include <StepShape_OrientedEdge.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_EdgeLoop, StepShape_Loop)

StepShape_EdgeLoop::StepShape_EdgeLoop() = default;

void StepShape_EdgeLoop::Init(
  const occ::handle<TCollection_HAsciiString>&                                 aName,
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>>& aEdgeList)
{

  StepRepr_RepresentationItem::Init(aName);

  edgeList = aEdgeList;
}

void StepShape_EdgeLoop::SetEdgeList(
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>>& aEdgeList)
{
  edgeList = aEdgeList;
}

occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>> StepShape_EdgeLoop::EdgeList()
  const
{
  return edgeList;
}

occ::handle<StepShape_OrientedEdge> StepShape_EdgeLoop::EdgeListValue(const int num) const
{
  return edgeList->Value(num);
}

int StepShape_EdgeLoop::NbEdgeList() const
{
  if (edgeList.IsNull())
    return 0;
  return edgeList->Length();
}
