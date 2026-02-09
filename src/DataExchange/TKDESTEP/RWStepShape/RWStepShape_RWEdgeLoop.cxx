

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include "RWStepShape_RWEdgeLoop.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_EdgeLoop.hpp>
#include <StepShape_OrientedEdge.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepShape_RWEdgeLoop::RWStepShape_RWEdgeLoop() = default;

void RWStepShape_RWEdgeLoop::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                      const int                                   num,
                                      occ::handle<Interface_Check>&               ach,
                                      const occ::handle<StepShape_EdgeLoop>&      ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "edge_loop"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>> aEdgeList;
  occ::handle<StepShape_OrientedEdge>                                   anent;
  int                                                                   nsub1;
  if (data->ReadSubList(num, 2, "edge_list", ach, nsub1))
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
                           anent))
        aEdgeList->SetValue(i1, anent);
    }
  }

  ent->Init(aName, aEdgeList);
}

void RWStepShape_RWEdgeLoop::WriteStep(StepData_StepWriter&                   SW,
                                       const occ::handle<StepShape_EdgeLoop>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->NbEdgeList(); i1++)
  {
    SW.Send(ent->EdgeListValue(i1));
  }
  SW.CloseSub();
}

void RWStepShape_RWEdgeLoop::Share(const occ::handle<StepShape_EdgeLoop>& ent,
                                   Interface_EntityIterator&              iter) const
{

  int nbElem1 = ent->NbEdgeList();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->EdgeListValue(is1));
  }
}

void RWStepShape_RWEdgeLoop::Check(const occ::handle<StepShape_EdgeLoop>& ent,
                                   const Interface_ShareTool&,
                                   occ::handle<Interface_Check>& ach) const
{

  bool headToTail = true;

  int nbEdg = ent->NbEdgeList();
  if (nbEdg == 0)
  {
    ach->AddFail("Edge loop contains empty edge list");
    return;
  }
  occ::handle<StepShape_OrientedEdge> theOE     = ent->EdgeListValue(1);
  occ::handle<StepShape_Vertex>       theVxFrst = theOE->EdgeStart();
  occ::handle<StepShape_Vertex>       theVxLst  = theOE->EdgeEnd();
  if ((nbEdg == 1) && (theVxFrst != theVxLst))
  {
    ach->AddFail(
      "Edge loop composed of single Edge : Start and End Vertex of edge are not identical");
  }
  for (int i = 2; i <= nbEdg; i++)
  {
    theOE                                   = ent->EdgeListValue(i);
    occ::handle<StepShape_Vertex> theVxStrt = theOE->EdgeStart();
    if (theVxStrt != theVxLst)
    {
      headToTail = false;
    }
    theVxLst = theOE->EdgeEnd();
    if (theVxStrt == theVxLst)
    {
      ach->AddWarning("One edge_curve contains identical vertices");
    }
  }
  if (theVxFrst != theVxLst)
  {
    headToTail = false;
  }
  if (!headToTail)
  {
    ach->AddFail("Error : Path does not head to tail");
  }
}
