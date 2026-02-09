#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <StepBasic_LengthMeasureWithUnit.hpp>
#include <StepDimTol_ToleranceZoneDefinition.hpp>
#include <StepRepr_ShapeAspect.hpp>

class StepDimTol_ProjectedZoneDefinition : public StepDimTol_ToleranceZoneDefinition
{

public:
  Standard_EXPORT StepDimTol_ProjectedZoneDefinition();

  Standard_EXPORT void Init(
    const occ::handle<StepDimTol_ToleranceZone>&                               theZone,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_ShapeAspect>>>& theBoundaries,
    const occ::handle<StepRepr_ShapeAspect>&                                   theProjectionEnd,
    const occ::handle<StepBasic_LengthMeasureWithUnit>&                        theProjectionLength);

  inline occ::handle<StepRepr_ShapeAspect> ProjectionEnd() const { return myProjectionEnd; }

  inline void SetProjectionEnd(const occ::handle<StepRepr_ShapeAspect>& theProjectionEnd)
  {
    myProjectionEnd = theProjectionEnd;
  }

  inline occ::handle<StepBasic_LengthMeasureWithUnit> ProjectionLength()
  {
    return myProjectionLength;
  }

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
