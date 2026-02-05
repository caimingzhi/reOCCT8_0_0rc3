#include <StepElement_SurfaceSection.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_SurfaceSection, Standard_Transient)

//=================================================================================================

StepElement_SurfaceSection::StepElement_SurfaceSection() = default;

//=================================================================================================

void StepElement_SurfaceSection::Init(
  const StepElement_MeasureOrUnspecifiedValue& aOffset,
  const StepElement_MeasureOrUnspecifiedValue& aNonStructuralMass,
  const StepElement_MeasureOrUnspecifiedValue& aNonStructuralMassOffset)
{

  theOffset = aOffset;

  theNonStructuralMass = aNonStructuralMass;

  theNonStructuralMassOffset = aNonStructuralMassOffset;
}

//=================================================================================================

StepElement_MeasureOrUnspecifiedValue StepElement_SurfaceSection::Offset() const
{
  return theOffset;
}

//=================================================================================================

void StepElement_SurfaceSection::SetOffset(const StepElement_MeasureOrUnspecifiedValue& aOffset)
{
  theOffset = aOffset;
}

//=================================================================================================

StepElement_MeasureOrUnspecifiedValue StepElement_SurfaceSection::NonStructuralMass() const
{
  return theNonStructuralMass;
}

//=================================================================================================

void StepElement_SurfaceSection::SetNonStructuralMass(
  const StepElement_MeasureOrUnspecifiedValue& aNonStructuralMass)
{
  theNonStructuralMass = aNonStructuralMass;
}

//=================================================================================================

StepElement_MeasureOrUnspecifiedValue StepElement_SurfaceSection::NonStructuralMassOffset() const
{
  return theNonStructuralMassOffset;
}

//=================================================================================================

void StepElement_SurfaceSection::SetNonStructuralMassOffset(
  const StepElement_MeasureOrUnspecifiedValue& aNonStructuralMassOffset)
{
  theNonStructuralMassOffset = aNonStructuralMassOffset;
}
