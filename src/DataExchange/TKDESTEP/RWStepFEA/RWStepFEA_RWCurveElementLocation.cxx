#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWCurveElementLocation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_CurveElementLocation.hpp>
#include <StepFEA_FeaParametricPoint.hpp>

//=================================================================================================

RWStepFEA_RWCurveElementLocation::RWStepFEA_RWCurveElementLocation() = default;

//=================================================================================================

void RWStepFEA_RWCurveElementLocation::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepFEA_CurveElementLocation>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 1, ach, "curve_element_location"))
    return;

  // Own fields of CurveElementLocation

  occ::handle<StepFEA_FeaParametricPoint> aCoordinate;
  data
    ->ReadEntity(num, 1, "coordinate", ach, STANDARD_TYPE(StepFEA_FeaParametricPoint), aCoordinate);

  // Initialize entity
  ent->Init(aCoordinate);
}

//=================================================================================================

void RWStepFEA_RWCurveElementLocation::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepFEA_CurveElementLocation>& ent) const
{

  // Own fields of CurveElementLocation

  SW.Send(ent->Coordinate());
}

//=================================================================================================

void RWStepFEA_RWCurveElementLocation::Share(const occ::handle<StepFEA_CurveElementLocation>& ent,
                                             Interface_EntityIterator& iter) const
{

  // Own fields of CurveElementLocation

  iter.AddItem(ent->Coordinate());
}
