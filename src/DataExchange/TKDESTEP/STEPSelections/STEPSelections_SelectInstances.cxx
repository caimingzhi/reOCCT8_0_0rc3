#include <Interface_EntityIterator.hpp>
#include <Interface_HGraph.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <STEPConstruct_Assembly.hpp>
#include <StepRepr_MappedItem.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_ShapeRepresentationRelationship.hpp>
#include <STEPSelections_SelectInstances.hpp>
#include <StepShape_BrepWithVoids.hpp>
#include <StepShape_ContextDependentShapeRepresentation.hpp>
#include <StepShape_FaceSurface.hpp>
#include <StepShape_FacetedBrep.hpp>
#include <StepShape_FacetedBrepAndBrepWithVoids.hpp>
#include <StepShape_GeometricSet.hpp>
#include <StepShape_ManifoldSolidBrep.hpp>
#include <StepShape_ShapeDefinitionRepresentation.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <StepShape_ShellBasedSurfaceModel.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_IndexedMap.hpp>

IMPLEMENT_STANDARD_RTTIEXT(STEPSelections_SelectInstances, IFSelect_SelectExplore)

namespace
{
  thread_local occ::handle<Interface_HGraph> myGraph;
  thread_local Interface_EntityIterator      myEntities;
} // namespace

STEPSelections_SelectInstances::STEPSelections_SelectInstances()
    : IFSelect_SelectExplore(-1)
{
}

static void AddAllSharings(const occ::handle<Standard_Transient>& start,
                           const Interface_Graph&                 graph,
                           Interface_EntityIterator&              explored)
{
  if (start.IsNull())
    return;
  Interface_EntityIterator subs = graph.Shareds(start);
  for (subs.Start(); subs.More(); subs.Next())
  {
    explored.AddItem(subs.Value());
    AddAllSharings(subs.Value(), graph, explored);
  }
}

static void AddInstances(const occ::handle<Standard_Transient>& start,
                         const Interface_Graph&                 graph,
                         Interface_EntityIterator&              explored)
{
  if (start.IsNull())
    return;

  explored.AddItem(start);
  if (start->IsKind(STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation)))
  {
    DeclareAndCast(StepShape_ShapeDefinitionRepresentation, sdr, start);
    AddInstances(sdr->UsedRepresentation(), graph, explored);
    Interface_EntityIterator subs = graph.Shareds(start);
    for (subs.Start(); subs.More(); subs.Next())
    {
      DeclareAndCast(StepShape_ContextDependentShapeRepresentation, anitem, subs.Value());
      if (anitem.IsNull())
        continue;
      AddInstances(anitem, graph, explored);
    }
    return;
  }

  if (start->IsKind(STANDARD_TYPE(StepShape_ShapeRepresentation)))
  {
    DeclareAndCast(StepShape_ShapeRepresentation, sr, start);
    int nb = sr->NbItems();
    for (int i = 1; i <= nb; i++)
    {
      occ::handle<StepRepr_RepresentationItem> anitem = sr->ItemsValue(i);
      AddInstances(anitem, graph, explored);
    }
    return;
  }

  if (start->IsKind(STANDARD_TYPE(StepShape_FacetedBrep))
      || start->IsKind(STANDARD_TYPE(StepShape_BrepWithVoids))
      || start->IsKind(STANDARD_TYPE(StepShape_ManifoldSolidBrep))
      || start->IsKind(STANDARD_TYPE(StepShape_ShellBasedSurfaceModel))
      || start->IsKind(STANDARD_TYPE(StepShape_FacetedBrepAndBrepWithVoids))
      || start->IsKind(STANDARD_TYPE(StepShape_GeometricSet))
      || start->IsKind(STANDARD_TYPE(StepShape_FaceSurface))
      || start->IsKind(STANDARD_TYPE(StepRepr_MappedItem)))
  {
    AddAllSharings(start, graph, explored);
    return;
  }

  if (start->IsKind(STANDARD_TYPE(StepShape_ContextDependentShapeRepresentation)))
  {
    DeclareAndCast(StepShape_ContextDependentShapeRepresentation, CDSR, start);
    occ::handle<StepRepr_RepresentationRelationship> SRR = CDSR->RepresentationRelation();
    if (SRR.IsNull())
      return;

    occ::handle<StepRepr_Representation> rep;
    bool SRRReversed = STEPConstruct_Assembly::CheckSRRReversesNAUO(graph, CDSR);
    if (SRRReversed)
      rep = SRR->Rep2();
    else
      rep = SRR->Rep1();

    Interface_EntityIterator subs = graph.Sharings(rep);
    for (subs.Start(); subs.More(); subs.Next())
      if (subs.Value()->IsKind(STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation)))
      {
        DeclareAndCast(StepShape_ShapeDefinitionRepresentation, SDR, subs.Value());
        AddInstances(SDR, graph, explored);
      }
    //???
    return;
  }

  if (start->IsKind(STANDARD_TYPE(StepRepr_ShapeRepresentationRelationship)))
  {
    DeclareAndCast(StepRepr_ShapeRepresentationRelationship, und, start);
    for (int i = 1; i <= 2; i++)
    {
      occ::handle<Standard_Transient> anitem;
      if (i == 1)
        anitem = und->Rep1();
      if (i == 2)
        anitem = und->Rep2();
      AddInstances(anitem, graph, explored);
    }
    return;
  }
}

Interface_EntityIterator STEPSelections_SelectInstances::RootResult(const Interface_Graph& G) const
{
  if (myGraph.IsNull() || (G.Model() != myGraph->Graph().Model()))
  {
    Interface_EntityIterator roots = G.RootEntities();
    myGraph                        = new Interface_HGraph(G);
    myEntities.Destroy();
    for (roots.Start(); roots.More(); roots.Next())
      AddInstances(roots.Value(), G, myEntities);
  }

  if (HasInput() || HasAlternate())
  {
    Interface_EntityIterator                                select     = InputResult(G);
    int                                                     nbSelected = select.NbEntities();
    NCollection_IndexedMap<occ::handle<Standard_Transient>> filter(nbSelected);
    for (select.Start(); select.More(); select.Next())
      filter.Add(select.Value());
    Interface_EntityIterator result;
    for (myEntities.Start(); myEntities.More(); myEntities.Next())
      if (filter.Contains(myEntities.Value()))
        result.AddItem(myEntities.Value());
    return result;
  }
  else
    return myEntities;
}

bool STEPSelections_SelectInstances::Explore(const int,
                                             const occ::handle<Standard_Transient>&,
                                             const Interface_Graph&,
                                             Interface_EntityIterator&) const
{
  return false;
}

bool STEPSelections_SelectInstances::HasUniqueResult() const
{
  return true;
}

TCollection_AsciiString STEPSelections_SelectInstances::ExploreLabel() const
{
  return TCollection_AsciiString("Instances");
}
