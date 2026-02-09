

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWPointOnCurve.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_PointOnCurve.hpp>

RWStepGeom_RWPointOnCurve::RWStepGeom_RWPointOnCurve() = default;

void RWStepGeom_RWPointOnCurve::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepGeom_PointOnCurve>&   ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "point_on_curve"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Curve> aBasisCurve;

  data->ReadEntity(num, 2, "basis_curve", ach, STANDARD_TYPE(StepGeom_Curve), aBasisCurve);

  double aPointParameter;

  data->ReadReal(num, 3, "point_parameter", ach, aPointParameter);

  ent->Init(aName, aBasisCurve, aPointParameter);
}

void RWStepGeom_RWPointOnCurve::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepGeom_PointOnCurve>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->BasisCurve());

  SW.Send(ent->PointParameter());
}

void RWStepGeom_RWPointOnCurve::Share(const occ::handle<StepGeom_PointOnCurve>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  iter.GetOneItem(ent->BasisCurve());
}
