#pragma once

#include <Standard.hpp>

#include <StepDimTol_RunoutZoneOrientation.hpp>
#include <StepDimTol_ToleranceZoneDefinition.hpp>
#include <Standard_Integer.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//! Representation of STEP entity ToleranceZoneDefinition
class StepDimTol_RunoutZoneDefinition : public StepDimTol_ToleranceZoneDefinition
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_RunoutZoneDefinition();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<StepDimTol_ToleranceZone>&                               theZone,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_ShapeAspect>>>& theBoundaries,
    const occ::handle<StepDimTol_RunoutZoneOrientation>&                       theOrientation);

  //! Returns field Orientation
  inline occ::handle<StepDimTol_RunoutZoneOrientation> Orientation() const { return myOrientation; }

  //! Set field Orientation
  inline void SetOrientation(const occ::handle<StepDimTol_RunoutZoneOrientation>& theOrientation)
  {
    myOrientation = theOrientation;
  }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_RunoutZoneDefinition, StepDimTol_ToleranceZoneDefinition)

private:
  occ::handle<StepDimTol_RunoutZoneOrientation> myOrientation;
};
