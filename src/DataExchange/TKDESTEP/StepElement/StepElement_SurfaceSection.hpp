#pragma once

#include <Standard.hpp>

#include <StepElement_MeasureOrUnspecifiedValue.hpp>
#include <Standard_Transient.hpp>

class StepElement_SurfaceSection : public Standard_Transient
{

public:
  Standard_EXPORT StepElement_SurfaceSection();

  Standard_EXPORT void Init(const StepElement_MeasureOrUnspecifiedValue& aOffset,
                            const StepElement_MeasureOrUnspecifiedValue& aNonStructuralMass,
                            const StepElement_MeasureOrUnspecifiedValue& aNonStructuralMassOffset);

  Standard_EXPORT StepElement_MeasureOrUnspecifiedValue Offset() const;

  Standard_EXPORT void SetOffset(const StepElement_MeasureOrUnspecifiedValue& Offset);

  Standard_EXPORT StepElement_MeasureOrUnspecifiedValue NonStructuralMass() const;

  Standard_EXPORT void SetNonStructuralMass(
    const StepElement_MeasureOrUnspecifiedValue& NonStructuralMass);

  Standard_EXPORT StepElement_MeasureOrUnspecifiedValue NonStructuralMassOffset() const;

  Standard_EXPORT void SetNonStructuralMassOffset(
    const StepElement_MeasureOrUnspecifiedValue& NonStructuralMassOffset);

  DEFINE_STANDARD_RTTIEXT(StepElement_SurfaceSection, Standard_Transient)

private:
  StepElement_MeasureOrUnspecifiedValue theOffset;
  StepElement_MeasureOrUnspecifiedValue theNonStructuralMass;
  StepElement_MeasureOrUnspecifiedValue theNonStructuralMassOffset;
};
