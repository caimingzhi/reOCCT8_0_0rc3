

#include <StepShape_Path.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_Path, StepShape_TopologicalRepresentationItem)

StepShape_Path::StepShape_Path() = default;

void StepShape_Path::Init(
  const occ::handle<TCollection_HAsciiString>&                                 aName,
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>>& aEdgeList)
{

  edgeList = aEdgeList;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_Path::SetEdgeList(
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>>& aEdgeList)
{
  edgeList = aEdgeList;
}

occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>> StepShape_Path::EdgeList()
  const
{
  return edgeList;
}

occ::handle<StepShape_OrientedEdge> StepShape_Path::EdgeListValue(const int num) const
{
  return edgeList->Value(num);
}

int StepShape_Path::NbEdgeList() const
{
  if (edgeList.IsNull())
    return 0;
  return edgeList->Length();
}
