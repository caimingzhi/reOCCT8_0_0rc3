#include <StepRepr_ShapeAspect.hpp>
#include <StepShape_DimensionalSize.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_DimensionalSize, Standard_Transient)

//=================================================================================================

StepShape_DimensionalSize::StepShape_DimensionalSize() = default;

//=================================================================================================

void StepShape_DimensionalSize::Init(const occ::handle<StepRepr_ShapeAspect>&     aAppliesTo,
                                     const occ::handle<TCollection_HAsciiString>& aName)
{

  theAppliesTo = aAppliesTo;

  theName = aName;
}

//=================================================================================================

occ::handle<StepRepr_ShapeAspect> StepShape_DimensionalSize::AppliesTo() const
{
  return theAppliesTo;
}

//=================================================================================================

void StepShape_DimensionalSize::SetAppliesTo(const occ::handle<StepRepr_ShapeAspect>& aAppliesTo)
{
  theAppliesTo = aAppliesTo;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepShape_DimensionalSize::Name() const
{
  return theName;
}

//=================================================================================================

void StepShape_DimensionalSize::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}
