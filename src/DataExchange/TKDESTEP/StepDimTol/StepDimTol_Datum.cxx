#include <StepDimTol_Datum.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_Datum, StepRepr_ShapeAspect)

//=================================================================================================

StepDimTol_Datum::StepDimTol_Datum() = default;

//=================================================================================================

void StepDimTol_Datum::Init(
  const occ::handle<TCollection_HAsciiString>&        theShapeAspect_Name,
  const occ::handle<TCollection_HAsciiString>&        theShapeAspect_Description,
  const occ::handle<StepRepr_ProductDefinitionShape>& theShapeAspect_OfShape,
  const StepData_Logical                              theShapeAspect_ProductDefinitional,
  const occ::handle<TCollection_HAsciiString>&        theIdentification)
{
  StepRepr_ShapeAspect::Init(theShapeAspect_Name,
                             theShapeAspect_Description,
                             theShapeAspect_OfShape,
                             theShapeAspect_ProductDefinitional);
  myIdentification = theIdentification;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepDimTol_Datum::Identification() const
{
  return myIdentification;
}

//=================================================================================================

void StepDimTol_Datum::SetIdentification(
  const occ::handle<TCollection_HAsciiString>& theIdentification)
{
  myIdentification = theIdentification;
}
