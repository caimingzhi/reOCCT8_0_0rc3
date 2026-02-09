#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWEdgeBasedWireframeModel.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_EdgeBasedWireframeModel.hpp>
#include <StepShape_ConnectedEdgeSet.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepShape_RWEdgeBasedWireframeModel::RWStepShape_RWEdgeBasedWireframeModel() = default;

void RWStepShape_RWEdgeBasedWireframeModel::ReadStep(
  const occ::handle<StepData_StepReaderData>&           data,
  const int                                             num,
  occ::handle<Interface_Check>&                         ach,
  const occ::handle<StepShape_EdgeBasedWireframeModel>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "edge_based_wireframe_model"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedEdgeSet>>> aEbwmBoundary;
  int                                                                       sub2 = 0;
  if (data->ReadSubList(num, 2, "ebwm_boundary", ach, sub2))
  {
    int num2      = sub2;
    int nb0       = data->NbParams(num2);
    aEbwmBoundary = new NCollection_HArray1<occ::handle<StepShape_ConnectedEdgeSet>>(1, nb0);
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      occ::handle<StepShape_ConnectedEdgeSet> anIt0;
      data->ReadEntity(num2,
                       i0,
                       "ebwm_boundary",
                       ach,
                       STANDARD_TYPE(StepShape_ConnectedEdgeSet),
                       anIt0);
      aEbwmBoundary->SetValue(i0, anIt0);
    }
  }

  ent->Init(aRepresentationItem_Name, aEbwmBoundary);
}

void RWStepShape_RWEdgeBasedWireframeModel::WriteStep(
  StepData_StepWriter&                                  SW,
  const occ::handle<StepShape_EdgeBasedWireframeModel>& ent) const
{

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->EbwmBoundary()->Length(); i1++)
  {
    occ::handle<StepShape_ConnectedEdgeSet> Var0 = ent->EbwmBoundary()->Value(i1);
    SW.Send(Var0);
  }
  SW.CloseSub();
}

void RWStepShape_RWEdgeBasedWireframeModel::Share(
  const occ::handle<StepShape_EdgeBasedWireframeModel>& ent,
  Interface_EntityIterator&                             iter) const
{

  for (int i1 = 1; i1 <= ent->EbwmBoundary()->Length(); i1++)
  {
    occ::handle<StepShape_ConnectedEdgeSet> Var0 = ent->EbwmBoundary()->Value(i1);
    iter.AddItem(Var0);
  }
}
