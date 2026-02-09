#include <StepDimTol_CommonDatum.hpp>
#include <StepDimTol_Datum.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_CommonDatum, StepRepr_CompositeShapeAspect)

StepDimTol_CommonDatum::StepDimTol_CommonDatum() = default;

void StepDimTol_CommonDatum::Init(
  const occ::handle<TCollection_HAsciiString>&        theShapeAspect_Name,
  const occ::handle<TCollection_HAsciiString>&        theShapeAspect_Description,
  const occ::handle<StepRepr_ProductDefinitionShape>& theShapeAspect_OfShape,
  const StepData_Logical                              theShapeAspect_ProductDefinitional,
  const occ::handle<TCollection_HAsciiString>&        theDatum_Name,
  const occ::handle<TCollection_HAsciiString>&        theDatum_Description,
  const occ::handle<StepRepr_ProductDefinitionShape>& theDatum_OfShape,
  const StepData_Logical                              theDatum_ProductDefinitional,
  const occ::handle<TCollection_HAsciiString>&        theDatum_Identification)
{
  StepRepr_CompositeShapeAspect::Init(theShapeAspect_Name,
                                      theShapeAspect_Description,
                                      theShapeAspect_OfShape,
                                      theShapeAspect_ProductDefinitional);
  myDatum->Init(theDatum_Name,
                theDatum_Description,
                theDatum_OfShape,
                theDatum_ProductDefinitional,
                theDatum_Identification);
}

occ::handle<StepDimTol_Datum> StepDimTol_CommonDatum::Datum() const
{
  return myDatum;
}

void StepDimTol_CommonDatum::SetDatum(const occ::handle<StepDimTol_Datum>& theDatum)
{
  myDatum = theDatum;
}
