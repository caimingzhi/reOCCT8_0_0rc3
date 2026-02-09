

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWLoopAndPath.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_LoopAndPath.hpp>
#include <StepShape_OrientedEdge.hpp>

RWStepShape_RWLoopAndPath::RWStepShape_RWLoopAndPath() = default;

void RWStepShape_RWLoopAndPath::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num0,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepShape_LoopAndPath>&   ent) const
{

  int num = num0;

  if (!data->CheckNbParams(num, 0, ach, "loop"))
    return;

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 1, ach, "path"))
    return;

  occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>> aEdgeList;
  occ::handle<StepShape_OrientedEdge>                                   anent1;
  int                                                                   nsub1;
  if (data->ReadSubList(num, 1, "edge_list", ach, nsub1))
  {
    int nb1   = data->NbParams(nsub1);
    aEdgeList = new NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>(1, nb1);
    for (int i1 = 1; i1 <= nb1; i1++)
    {

      if (data->ReadEntity(nsub1,
                           i1,
                           "oriented_edge",
                           ach,
                           STANDARD_TYPE(StepShape_OrientedEdge),
                           anent1))
        aEdgeList->SetValue(i1, anent1);
    }
  }

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 1, ach, "representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 0, ach, "topological_representation_item"))
    return;

  ent->Init(aName, aEdgeList);
}

void RWStepShape_RWLoopAndPath::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepShape_LoopAndPath>& ent) const
{

  SW.StartEntity("LOOP");

  SW.StartEntity("PATH");

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->NbEdgeList(); i1++)
  {
    SW.Send(ent->EdgeListValue(i1));
  }
  SW.CloseSub();

  SW.StartEntity("REPRESENTATION_ITEM");

  SW.Send(ent->Name());

  SW.StartEntity("TOPOLOGICAL_REPRESENTATION_ITEM");
}

void RWStepShape_RWLoopAndPath::Share(const occ::handle<StepShape_LoopAndPath>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  int nbElem1 = ent->NbEdgeList();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->EdgeListValue(is1));
  }
}
