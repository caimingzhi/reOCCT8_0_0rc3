

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWCartesianTransformationOperator.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_CartesianTransformationOperator.hpp>
#include <StepGeom_Direction.hpp>

RWStepGeom_RWCartesianTransformationOperator::RWStepGeom_RWCartesianTransformationOperator() =
  default;

void RWStepGeom_RWCartesianTransformationOperator::ReadStep(
  const occ::handle<StepData_StepReaderData>&                  data,
  const int                                                    num,
  occ::handle<Interface_Check>&                                ach,
  const occ::handle<StepGeom_CartesianTransformationOperator>& ent) const
{

  if (!data->CheckNbParams(num, 7, ach, "cartesian_transformation_operator"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 3, "name", ach, aName);

  occ::handle<StepGeom_Direction> aAxis1;
  bool                            hasAaxis1 = true;
  if (data->IsParamDefined(num, 4))
  {

    data->ReadEntity(num, 4, "axis1", ach, STANDARD_TYPE(StepGeom_Direction), aAxis1);
  }
  else
  {
    hasAaxis1 = false;
    aAxis1.Nullify();
  }

  occ::handle<StepGeom_Direction> aAxis2;
  bool                            hasAaxis2 = true;
  if (data->IsParamDefined(num, 5))
  {

    data->ReadEntity(num, 5, "axis2", ach, STANDARD_TYPE(StepGeom_Direction), aAxis2);
  }
  else
  {
    hasAaxis2 = false;
    aAxis2.Nullify();
  }

  occ::handle<StepGeom_CartesianPoint> aLocalOrigin;

  data
    ->ReadEntity(num, 6, "local_origin", ach, STANDARD_TYPE(StepGeom_CartesianPoint), aLocalOrigin);

  double aScale;
  bool   hasAscale = true;
  if (data->IsParamDefined(num, 7))
  {

    data->ReadReal(num, 7, "scale", ach, aScale);
  }
  else
  {
    hasAscale = false;
    aScale    = 0.;
  }

  ent->Init(aName, hasAaxis1, aAxis1, hasAaxis2, aAxis2, aLocalOrigin, hasAscale, aScale);
}

void RWStepGeom_RWCartesianTransformationOperator::WriteStep(
  StepData_StepWriter&                                         SW,
  const occ::handle<StepGeom_CartesianTransformationOperator>& ent) const
{

  SW.Send(ent->Name());
  SW.Send(ent->Name());
  SW.Send(ent->Name());

  bool hasAaxis1 = ent->HasAxis1();
  if (hasAaxis1)
  {
    SW.Send(ent->Axis1());
  }
  else
  {
    SW.SendUndef();
  }

  bool hasAaxis2 = ent->HasAxis2();
  if (hasAaxis2)
  {
    SW.Send(ent->Axis2());
  }
  else
  {
    SW.SendUndef();
  }

  SW.Send(ent->LocalOrigin());

  bool hasAscale = ent->HasScale();
  if (hasAscale)
  {
    SW.Send(ent->Scale());
  }
  else
  {
    SW.SendUndef();
  }
}

void RWStepGeom_RWCartesianTransformationOperator::Share(
  const occ::handle<StepGeom_CartesianTransformationOperator>& ent,
  Interface_EntityIterator&                                    iter) const
{
  if (ent->HasAxis1())
  {
    iter.GetOneItem(ent->Axis1());
  }

  if (ent->HasAxis2())
  {
    iter.GetOneItem(ent->Axis2());
  }

  iter.GetOneItem(ent->LocalOrigin());
}
