

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWCartesianTransformationOperator3d.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_CartesianTransformationOperator3d.hpp>
#include <StepGeom_Direction.hpp>

RWStepGeom_RWCartesianTransformationOperator3d::RWStepGeom_RWCartesianTransformationOperator3d() =
  default;

void RWStepGeom_RWCartesianTransformationOperator3d::ReadStep(
  const occ::handle<StepData_StepReaderData>&                    data,
  const int                                                      num,
  occ::handle<Interface_Check>&                                  ach,
  const occ::handle<StepGeom_CartesianTransformationOperator3d>& ent) const
{

  if (!data->CheckNbParams(num, 8, ach, "cartesian_transformation_operator_3d"))
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

  occ::handle<StepGeom_Direction> aAxis3;
  bool                            hasAaxis3 = true;
  if (data->IsParamDefined(num, 8))
  {

    data->ReadEntity(num, 8, "axis3", ach, STANDARD_TYPE(StepGeom_Direction), aAxis3);
  }
  else
  {
    hasAaxis3 = false;
    aAxis3.Nullify();
  }

  ent->Init(aName,
            hasAaxis1,
            aAxis1,
            hasAaxis2,
            aAxis2,
            aLocalOrigin,
            hasAscale,
            aScale,
            hasAaxis3,
            aAxis3);
}

void RWStepGeom_RWCartesianTransformationOperator3d::WriteStep(
  StepData_StepWriter&                                           SW,
  const occ::handle<StepGeom_CartesianTransformationOperator3d>& ent) const
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

  bool hasAaxis3 = ent->HasAxis3();
  if (hasAaxis3)
  {
    SW.Send(ent->Axis3());
  }
  else
  {
    SW.SendUndef();
  }
}

void RWStepGeom_RWCartesianTransformationOperator3d::Share(
  const occ::handle<StepGeom_CartesianTransformationOperator3d>& ent,
  Interface_EntityIterator&                                      iter) const
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

  if (ent->HasAxis3())
  {
    iter.GetOneItem(ent->Axis3());
  }
}
