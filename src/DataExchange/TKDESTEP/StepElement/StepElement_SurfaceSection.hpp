#pragma once


#include <Standard.hpp>

#include <StepElement_MeasureOrUnspecifiedValue.hpp>
#include <Standard_Transient.hpp>

//! Representation of STEP entity SurfaceSection
class StepElement_SurfaceSection : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepElement_SurfaceSection();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const StepElement_MeasureOrUnspecifiedValue& aOffset,
                            const StepElement_MeasureOrUnspecifiedValue& aNonStructuralMass,
                            const StepElement_MeasureOrUnspecifiedValue& aNonStructuralMassOffset);

  //! Returns field Offset
  Standard_EXPORT StepElement_MeasureOrUnspecifiedValue Offset() const;

  //! Set field Offset
  Standard_EXPORT void SetOffset(const StepElement_MeasureOrUnspecifiedValue& Offset);

  //! Returns field NonStructuralMass
  Standard_EXPORT StepElement_MeasureOrUnspecifiedValue NonStructuralMass() const;

  //! Set field NonStructuralMass
  Standard_EXPORT void SetNonStructuralMass(
    const StepElement_MeasureOrUnspecifiedValue& NonStructuralMass);

  //! Returns field NonStructuralMassOffset
  Standard_EXPORT StepElement_MeasureOrUnspecifiedValue NonStructuralMassOffset() const;

  //! Set field NonStructuralMassOffset
  Standard_EXPORT void SetNonStructuralMassOffset(
    const StepElement_MeasureOrUnspecifiedValue& NonStructuralMassOffset);

  DEFINE_STANDARD_RTTIEXT(StepElement_SurfaceSection, Standard_Transient)

private:
  StepElement_MeasureOrUnspecifiedValue theOffset;
  StepElement_MeasureOrUnspecifiedValue theNonStructuralMass;
  StepElement_MeasureOrUnspecifiedValue theNonStructuralMassOffset;
};

