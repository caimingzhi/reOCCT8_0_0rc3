#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_CompositeShapeAspect.hpp>
#include <StepData_Logical.hpp>
class StepDimTol_Datum;
class TCollection_HAsciiString;
class StepRepr_ProductDefinitionShape;

//! Representation of STEP entity CommonDatum
class StepDimTol_CommonDatum : public StepRepr_CompositeShapeAspect
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_CommonDatum();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&        theShapeAspect_Name,
    const occ::handle<TCollection_HAsciiString>&        theShapeAspect_Description,
    const occ::handle<StepRepr_ProductDefinitionShape>& theShapeAspect_OfShape,
    const StepData_Logical                              theShapeAspect_ProductDefinitional,
    const occ::handle<TCollection_HAsciiString>&        theDatum_Name,
    const occ::handle<TCollection_HAsciiString>&        theDatum_Description,
    const occ::handle<StepRepr_ProductDefinitionShape>& theDatum_OfShape,
    const StepData_Logical                              theDatum_ProductDefinitional,
    const occ::handle<TCollection_HAsciiString>&        theDatum_Identification);

  //! Returns data for supertype Datum
  Standard_EXPORT occ::handle<StepDimTol_Datum> Datum() const;

  //! Set data for supertype Datum
  Standard_EXPORT void SetDatum(const occ::handle<StepDimTol_Datum>& theDatum);

  DEFINE_STANDARD_RTTIEXT(StepDimTol_CommonDatum, StepRepr_CompositeShapeAspect)

private:
  occ::handle<StepDimTol_Datum> myDatum;
};
