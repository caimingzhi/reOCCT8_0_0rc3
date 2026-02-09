

#include <StepShape_ClosedShell.hpp>
#include <StepShape_ConnectedFaceSet.hpp>
#include <StepShape_ManifoldSolidBrep.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_ManifoldSolidBrep, StepShape_SolidModel)

StepShape_ManifoldSolidBrep::StepShape_ManifoldSolidBrep() = default;

void StepShape_ManifoldSolidBrep::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                       const occ::handle<StepShape_ClosedShell>&    aOuter)
{

  outer = aOuter;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_ManifoldSolidBrep::Init(const occ::handle<TCollection_HAsciiString>&   aName,
                                       const occ::handle<StepShape_ConnectedFaceSet>& aOuter)
{

  outer = aOuter;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_ManifoldSolidBrep::SetOuter(const occ::handle<StepShape_ConnectedFaceSet>& aOuter)
{
  outer = aOuter;
}

occ::handle<StepShape_ConnectedFaceSet> StepShape_ManifoldSolidBrep::Outer() const
{
  return outer;
}
