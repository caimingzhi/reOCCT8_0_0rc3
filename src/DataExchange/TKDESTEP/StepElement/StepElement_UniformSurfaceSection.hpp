#pragma once

#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <StepElement_SurfaceSection.hpp>

//! Representation of STEP entity UniformSurfaceSection
class StepElement_UniformSurfaceSection : public StepElement_SurfaceSection
{

public:
  //! Empty constructor
  Standard_EXPORT StepElement_UniformSurfaceSection();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const StepElement_MeasureOrUnspecifiedValue& aSurfaceSection_Offset,
    const StepElement_MeasureOrUnspecifiedValue& aSurfaceSection_NonStructuralMass,
    const StepElement_MeasureOrUnspecifiedValue& aSurfaceSection_NonStructuralMassOffset,
    const double                                 aThickness,
    const StepElement_MeasureOrUnspecifiedValue& aBendingThickness,
    const StepElement_MeasureOrUnspecifiedValue& aShearThickness);

  //! Returns field Thickness
  Standard_EXPORT double Thickness() const;

  //! Set field Thickness
  Standard_EXPORT void SetThickness(const double Thickness);

  //! Returns field BendingThickness
  Standard_EXPORT StepElement_MeasureOrUnspecifiedValue BendingThickness() const;

  //! Set field BendingThickness
  Standard_EXPORT void SetBendingThickness(
    const StepElement_MeasureOrUnspecifiedValue& BendingThickness);

  //! Returns field ShearThickness
  Standard_EXPORT StepElement_MeasureOrUnspecifiedValue ShearThickness() const;

  //! Set field ShearThickness
  Standard_EXPORT void SetShearThickness(
    const StepElement_MeasureOrUnspecifiedValue& ShearThickness);

  DEFINE_STANDARD_RTTIEXT(StepElement_UniformSurfaceSection, StepElement_SurfaceSection)

private:
  double                                theThickness;
  StepElement_MeasureOrUnspecifiedValue theBendingThickness;
  StepElement_MeasureOrUnspecifiedValue theShearThickness;
};
