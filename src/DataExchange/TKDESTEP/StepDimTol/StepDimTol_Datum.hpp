#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ShapeAspect.hpp>
#include <StepData_Logical.hpp>
class TCollection_HAsciiString;
class StepRepr_ProductDefinitionShape;

//! Representation of STEP entity Datum
class StepDimTol_Datum : public StepRepr_ShapeAspect
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_Datum();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&        theShapeAspect_Name,
    const occ::handle<TCollection_HAsciiString>&        theShapeAspect_Description,
    const occ::handle<StepRepr_ProductDefinitionShape>& theShapeAspect_OfShape,
    const StepData_Logical                              theShapeAspect_ProductDefinitional,
    const occ::handle<TCollection_HAsciiString>&        theIdentification);

  //! Returns field Identification
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Identification() const;

  //! Set field Identification
  Standard_EXPORT void SetIdentification(
    const occ::handle<TCollection_HAsciiString>& theIdentification);

  DEFINE_STANDARD_RTTIEXT(StepDimTol_Datum, StepRepr_ShapeAspect)

private:
  occ::handle<TCollection_HAsciiString> myIdentification;
};

