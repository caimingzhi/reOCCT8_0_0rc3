

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWPolyline.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Polyline.hpp>

RWStepGeom_RWPolyline::RWStepGeom_RWPolyline() = default;

void RWStepGeom_RWPolyline::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                     const int                                   num,
                                     occ::handle<Interface_Check>&               ach,
                                     const occ::handle<StepGeom_Polyline>&       ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "polyline"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> aPoints;
  occ::handle<StepGeom_CartesianPoint>                                   anent2;
  int                                                                    nsub2;
  if (data->ReadSubList(num, 2, "points", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    aPoints = new NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadEntity(nsub2,
                           i2,
                           "cartesian_point",
                           ach,
                           STANDARD_TYPE(StepGeom_CartesianPoint),
                           anent2))
        aPoints->SetValue(i2, anent2);
    }
  }

  ent->Init(aName, aPoints);
}

void RWStepGeom_RWPolyline::WriteStep(StepData_StepWriter&                  SW,
                                      const occ::handle<StepGeom_Polyline>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbPoints(); i2++)
  {
    SW.Send(ent->PointsValue(i2));
  }
  SW.CloseSub();
}

void RWStepGeom_RWPolyline::Share(const occ::handle<StepGeom_Polyline>& ent,
                                  Interface_EntityIterator&             iter) const
{

  int nbElem1 = ent->NbPoints();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->PointsValue(is1));
  }
}
