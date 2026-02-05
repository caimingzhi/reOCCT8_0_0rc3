#include <Interface_EntityIterator.hpp>
#include "RWStepDimTol_RWPositionTolerance.hpp"
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_PositionTolerance.hpp>

//=================================================================================================

RWStepDimTol_RWPositionTolerance::RWStepDimTol_RWPositionTolerance() = default;

//=================================================================================================

void RWStepDimTol_RWPositionTolerance::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepDimTol_PositionTolerance>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 4, ach, "position_tolerance"))
    return;

  // Inherited fields of GeometricTolerance

  occ::handle<TCollection_HAsciiString> aGeometricTolerance_Name;
  data->ReadString(num, 1, "geometric_tolerance.name", ach, aGeometricTolerance_Name);

  occ::handle<TCollection_HAsciiString> aGeometricTolerance_Description;
  data->ReadString(num, 2, "geometric_tolerance.description", ach, aGeometricTolerance_Description);

  occ::handle<Standard_Transient> aGeometricTolerance_Magnitude;
  data->ReadEntity(num,
                   3,
                   "geometric_tolerance.magnitude",
                   ach,
                   STANDARD_TYPE(Standard_Transient),
                   aGeometricTolerance_Magnitude);

  StepDimTol_GeometricToleranceTarget aGeometricTolerance_TolerancedShapeAspect;
  data->ReadEntity(num,
                   4,
                   "geometric_tolerance.toleranced_shape_aspect",
                   ach,
                   aGeometricTolerance_TolerancedShapeAspect);

  // Initialize entity
  ent->Init(aGeometricTolerance_Name,
            aGeometricTolerance_Description,
            aGeometricTolerance_Magnitude,
            aGeometricTolerance_TolerancedShapeAspect);
}

//=================================================================================================

void RWStepDimTol_RWPositionTolerance::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepDimTol_PositionTolerance>& ent) const
{

  // Inherited fields of GeometricTolerance

  SW.Send(ent->StepDimTol_GeometricTolerance::Name());

  SW.Send(ent->StepDimTol_GeometricTolerance::Description());

  SW.Send(ent->StepDimTol_GeometricTolerance::Magnitude());

  SW.Send(ent->StepDimTol_GeometricTolerance::TolerancedShapeAspect().Value());
}

//=================================================================================================

void RWStepDimTol_RWPositionTolerance::Share(const occ::handle<StepDimTol_PositionTolerance>& ent,
                                             Interface_EntityIterator& iter) const
{

  // Inherited fields of GeometricTolerance

  iter.AddItem(ent->StepDimTol_GeometricTolerance::Magnitude());

  iter.AddItem(ent->StepDimTol_GeometricTolerance::TolerancedShapeAspect().Value());
}
