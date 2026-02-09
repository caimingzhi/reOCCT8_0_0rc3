

#include <StepShape_BrepWithVoids.hpp>
#include <StepShape_ClosedShell.hpp>
#include <StepShape_OrientedClosedShell.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_BrepWithVoids, StepShape_ManifoldSolidBrep)

StepShape_BrepWithVoids::StepShape_BrepWithVoids() = default;

void StepShape_BrepWithVoids::Init(
  const occ::handle<TCollection_HAsciiString>&                                        aName,
  const occ::handle<StepShape_ClosedShell>&                                           aOuter,
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedClosedShell>>>& aVoids)
{

  voids = aVoids;

  StepShape_ManifoldSolidBrep::Init(aName, aOuter);
}

void StepShape_BrepWithVoids::SetVoids(
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedClosedShell>>>& aVoids)
{
  voids = aVoids;
}

occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedClosedShell>>>
  StepShape_BrepWithVoids::Voids() const
{
  return voids;
}

occ::handle<StepShape_OrientedClosedShell> StepShape_BrepWithVoids::VoidsValue(const int num) const
{
  return voids->Value(num);
}

int StepShape_BrepWithVoids::NbVoids() const
{
  if (voids.IsNull())
    return 0;
  return voids->Length();
}
