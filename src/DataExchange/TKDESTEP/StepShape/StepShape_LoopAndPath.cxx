

#include <Standard_Type.hpp>
#include <StepShape_Loop.hpp>
#include <StepShape_LoopAndPath.hpp>
#include <StepShape_OrientedEdge.hpp>
#include <StepShape_Path.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_LoopAndPath, StepShape_TopologicalRepresentationItem)

StepShape_LoopAndPath::StepShape_LoopAndPath() = default;

void StepShape_LoopAndPath::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                 const occ::handle<StepShape_Loop>&           aLoop,
                                 const occ::handle<StepShape_Path>&           aPath)
{

  loop = aLoop;
  path = aPath;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_LoopAndPath::Init(
  const occ::handle<TCollection_HAsciiString>&                                 aName,
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>>& aEdgeList)
{

  StepRepr_RepresentationItem::Init(aName);

  loop = new StepShape_Loop();
  loop->Init(aName);

  path = new StepShape_Path();
  path->Init(aName, aEdgeList);
}

void StepShape_LoopAndPath::SetLoop(const occ::handle<StepShape_Loop>& aLoop)
{
  loop = aLoop;
}

occ::handle<StepShape_Loop> StepShape_LoopAndPath::Loop() const
{
  return loop;
}

void StepShape_LoopAndPath::SetPath(const occ::handle<StepShape_Path>& aPath)
{
  path = aPath;
}

occ::handle<StepShape_Path> StepShape_LoopAndPath::Path() const
{
  return path;
}

void StepShape_LoopAndPath::SetEdgeList(
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>>& aEdgeList)
{
  path->SetEdgeList(aEdgeList);
}

occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>> StepShape_LoopAndPath::
  EdgeList() const
{
  return path->EdgeList();
}

occ::handle<StepShape_OrientedEdge> StepShape_LoopAndPath::EdgeListValue(const int num) const
{
  return path->EdgeListValue(num);
}

int StepShape_LoopAndPath::NbEdgeList() const
{
  return path->NbEdgeList();
}
