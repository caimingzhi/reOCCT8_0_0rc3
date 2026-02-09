

#include <StepShape_FaceBound.hpp>
#include <StepShape_Loop.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_FaceBound, StepShape_TopologicalRepresentationItem)

StepShape_FaceBound::StepShape_FaceBound() = default;

void StepShape_FaceBound::Init(const occ::handle<TCollection_HAsciiString>& aName,
                               const occ::handle<StepShape_Loop>&           aBound,
                               const bool                                   aOrientation)
{

  bound       = aBound;
  orientation = aOrientation;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_FaceBound::SetBound(const occ::handle<StepShape_Loop>& aBound)
{
  bound = aBound;
}

occ::handle<StepShape_Loop> StepShape_FaceBound::Bound() const
{
  return bound;
}

void StepShape_FaceBound::SetOrientation(const bool aOrientation)
{
  orientation = aOrientation;
}

bool StepShape_FaceBound::Orientation() const
{
  return orientation;
}
