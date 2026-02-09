

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWPolyLoop.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_PolyLoop.hpp>

RWStepShape_RWPolyLoop::RWStepShape_RWPolyLoop() = default;

void RWStepShape_RWPolyLoop::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                      const int                                   num,
                                      occ::handle<Interface_Check>&               ach,
                                      const occ::handle<StepShape_PolyLoop>&      ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "poly_loop"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> aPolygon;
  occ::handle<StepGeom_CartesianPoint>                                   anent2;
  int                                                                    nsub2;
  if (data->ReadSubList(num, 2, "polygon", ach, nsub2))
  {
    int nb2  = data->NbParams(nsub2);
    aPolygon = new NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadEntity(nsub2,
                           i2,
                           "cartesian_point",
                           ach,
                           STANDARD_TYPE(StepGeom_CartesianPoint),
                           anent2))
        aPolygon->SetValue(i2, anent2);
    }
  }

  ent->Init(aName, aPolygon);
}

void RWStepShape_RWPolyLoop::WriteStep(StepData_StepWriter&                   SW,
                                       const occ::handle<StepShape_PolyLoop>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbPolygon(); i2++)
  {
    SW.Send(ent->PolygonValue(i2));
  }
  SW.CloseSub();
}

void RWStepShape_RWPolyLoop::Share(const occ::handle<StepShape_PolyLoop>& ent,
                                   Interface_EntityIterator&              iter) const
{

  int nbElem1 = ent->NbPolygon();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->PolygonValue(is1));
  }
}
