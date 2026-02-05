#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <StepBasic_LengthMeasureWithUnit.hpp>
#include <StepDimTol_ToleranceZoneDefinition.hpp>
#include <StepRepr_ShapeAspect.hpp>

//! Representation of STEP entity ProjectedZoneDefinition
class StepDimTol_ProjectedZoneDefinition : public StepDimTol_ToleranceZoneDefinition
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_ProjectedZoneDefinition();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<StepDimTol_ToleranceZone>&                               theZone,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_ShapeAspect>>>& theBoundaries,
    const occ::handle<StepRepr_ShapeAspect>&                                   theProjectionEnd,
    const occ::handle<StepBasic_LengthMeasureWithUnit>&                        theProjectionLength);

  //! Returns field ProjectionEnd
  inline occ::handle<StepRepr_ShapeAspect> ProjectionEnd() const { return myProjectionEnd; }

  //! Set field ProjectionEnd
  inline void SetProjectionEnd(const occ::handle<StepRepr_ShapeAspect>& theProjectionEnd)
  {
    myProjectionEnd = theProjectionEnd;
  }

  //! Returns field ProjectionLength
  inline occ::handle<StepBasic_LengthMeasureWithUnit> ProjectionLength()
  {
    return myProjectionLength;
  }

  //! Set field ProjectionLength
  inline void SetProjectionLength(
    const occ::handle<StepBasic_LengthMeasureWithUnit>& theProjectionLength)
  {
    myProjectionLength = theProjectionLength;
  }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_ProjectedZoneDefinition, StepDimTol_ToleranceZoneDefinition)

private:
  occ::handle<StepRepr_ShapeAspect>            myProjectionEnd;
  occ::handle<StepBasic_LengthMeasureWithUnit> myProjectionLength;
};
