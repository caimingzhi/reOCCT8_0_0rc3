

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWPath.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_OrientedEdge.hpp>
#include <StepShape_Path.hpp>

RWStepShape_RWPath::RWStepShape_RWPath() = default;

void RWStepShape_RWPath::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                  const int                                   num,
                                  occ::handle<Interface_Check>&               ach,
                                  const occ::handle<StepShape_Path>&          ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "path"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>> aEdgeList;
  occ::handle<StepShape_OrientedEdge>                                   anent2;
  int                                                                   nsub2;
  if (data->ReadSubList(num, 2, "edge_list", ach, nsub2))
  {
    int nb2   = data->NbParams(nsub2);
    aEdgeList = new NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadEntity(nsub2,
                           i2,
                           "oriented_edge",
                           ach,
                           STANDARD_TYPE(StepShape_OrientedEdge),
                           anent2))
        aEdgeList->SetValue(i2, anent2);
    }
  }

  ent->Init(aName, aEdgeList);
}

void RWStepShape_RWPath::WriteStep(StepData_StepWriter&               SW,
                                   const occ::handle<StepShape_Path>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbEdgeList(); i2++)
  {
    SW.Send(ent->EdgeListValue(i2));
  }
  SW.CloseSub();
}

void RWStepShape_RWPath::Share(const occ::handle<StepShape_Path>& ent,
                               Interface_EntityIterator&          iter) const
{

  int nbElem1 = ent->NbEdgeList();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->EdgeListValue(is1));
  }
}
