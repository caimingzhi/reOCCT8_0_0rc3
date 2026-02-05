#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepBasic_ProductRelatedProductCategory.hpp>
#include <STEPConstruct_Assembly.hpp>
#include <StepGeom_CompositeCurve.hpp>
#include <StepGeom_CompositeCurveSegment.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_Surface.hpp>
#include <StepRepr_MappedItem.hpp>
#include <StepRepr_RepresentationMap.hpp>
#include <StepRepr_ShapeRepresentationRelationship.hpp>
#include <STEPSelections_Counter.hpp>
#include <StepShape_BrepWithVoids.hpp>
#include <StepShape_ClosedShell.hpp>
#include <StepShape_ConnectedFaceSet.hpp>
#include <StepShape_ContextDependentShapeRepresentation.hpp>
#include <StepShape_FaceSurface.hpp>
#include <StepShape_FacetedBrep.hpp>
#include <StepShape_FacetedBrepAndBrepWithVoids.hpp>
#include <StepShape_GeometricSet.hpp>
#include <StepShape_GeometricSetSelect.hpp>
#include <StepShape_ManifoldSolidBrep.hpp>
#include <StepShape_OpenShell.hpp>
#include <StepShape_ShapeDefinitionRepresentation.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <StepShape_ShellBasedSurfaceModel.hpp>

STEPSelections_Counter::STEPSelections_Counter()
{
  myNbFaces  = 0;
  myNbShells = 0;
  myNbSolids = 0;
  myNbWires  = 0;
  myNbEdges  = 0;
}

void STEPSelections_Counter::Count(const Interface_Graph&                 graph,
                                   const occ::handle<Standard_Transient>& start)
{
  if (start.IsNull())
    return;

  if (start->IsKind(STANDARD_TYPE(StepBasic_ProductRelatedProductCategory)))
    return;

  if (start->IsKind(STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation)))
  {
    DeclareAndCast(StepShape_ShapeDefinitionRepresentation, sdr, start);
    Count(graph, sdr->UsedRepresentation());
    Interface_EntityIterator subs = graph.Shareds(start);
    for (subs.Start(); subs.More(); subs.Next())
    {
      DeclareAndCast(StepShape_ContextDependentShapeRepresentation, anitem, subs.Value());
      if (anitem.IsNull())
        continue;
      Count(graph, anitem);
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
      Count(graph, anitem);
    }
    return;
  }

  if (start->IsKind(STANDARD_TYPE(StepShape_FacetedBrep)))
  {
    DeclareAndCast(StepShape_FacetedBrep, fbr, start);
    myMapOfSolids.Add(start);
    myNbSolids++;
    AddShell(fbr->Outer());
    return;
  }

  if (start->IsKind(STANDARD_TYPE(StepShape_BrepWithVoids)))
  {
    DeclareAndCast(StepShape_BrepWithVoids, brwv, start);
    myMapOfSolids.Add(start);
    myNbSolids++;
    AddShell(brwv->Outer());
    int nbvoids = brwv->NbVoids();
    for (int i = 1; i <= nbvoids; i++)
      AddShell(brwv->VoidsValue(i));
    return;
  }

  if (start->IsKind(STANDARD_TYPE(StepShape_ManifoldSolidBrep)))
  {
    DeclareAndCast(StepShape_ManifoldSolidBrep, msbr, start);
    myMapOfSolids.Add(start);
    myNbSolids++;
    AddShell(msbr->Outer());
    return;
  }

  if (start->IsKind(STANDARD_TYPE(StepShape_ShellBasedSurfaceModel)))
  {
    DeclareAndCast(StepShape_ShellBasedSurfaceModel, sbsm, start);
    int nbItems = sbsm->NbSbsmBoundary();
    for (int i = 1; i <= nbItems; i++)
    {
      occ::handle<StepShape_OpenShell> osh = sbsm->SbsmBoundaryValue(i).OpenShell();
      if (!osh.IsNull())
        AddShell(osh);
      occ::handle<StepShape_ClosedShell> csh = sbsm->SbsmBoundaryValue(i).ClosedShell();
      if (!csh.IsNull())
        AddShell(csh);
    }
    return;
  }

  if (start->IsKind(STANDARD_TYPE(StepShape_FacetedBrepAndBrepWithVoids)))
  {
    DeclareAndCast(StepShape_FacetedBrepAndBrepWithVoids, fbwv, start);
    myMapOfSolids.Add(start);
    myNbSolids++;
    AddShell(fbwv->Outer());
    int nbvoids = fbwv->NbVoids();
    for (int i = 1; i <= nbvoids; i++)
      AddShell(fbwv->VoidsValue(i));
    return;
  }

  if (start->IsKind(STANDARD_TYPE(StepShape_GeometricSet)))
  {
    DeclareAndCast(StepShape_GeometricSet, gs, start);
    int nbElem = gs->NbElements();
    for (int i = 1; i <= nbElem; i++)
    {
      StepShape_GeometricSetSelect           aGSS   = gs->ElementsValue(i);
      const occ::handle<Standard_Transient>& ent    = aGSS.Value();
      occ::handle<StepGeom_CompositeCurve>   ccurve = occ::down_cast<StepGeom_CompositeCurve>(ent);
      if (!ccurve.IsNull())
      {
        myNbWires++;
        myMapOfWires.Add(ccurve);
        AddCompositeCurve(ccurve);
      }
      else if (ent->IsKind(STANDARD_TYPE(StepGeom_Curve)))
      {
        myNbEdges++;
        myMapOfEdges.Add(ent);
      }
      else if (ent->IsKind(STANDARD_TYPE(StepGeom_Surface)))
      {
        myNbFaces++;
        myMapOfFaces.Add(ent);
      }
    }
  }

  if (start->IsKind(STANDARD_TYPE(StepRepr_MappedItem)))
  {
    DeclareAndCast(StepRepr_MappedItem, mi, start);
    Count(graph, mi->MappingTarget());
    occ::handle<StepRepr_RepresentationMap> map = mi->MappingSource();
    if (map.IsNull())
      return;
    Count(graph, map->MappedRepresentation());
    return;
  }

  if (start->IsKind(STANDARD_TYPE(StepShape_FaceSurface)))
  {
    myNbFaces++;
    myMapOfFaces.Add(start);
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
        Count(graph, SDR);
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
      Count(graph, anitem);
    }
    return;
  }
}

void STEPSelections_Counter::Clear()
{
  myMapOfFaces.Clear();
  myMapOfShells.Clear();
  myMapOfSolids.Clear();
  myMapOfWires.Clear();
  myMapOfEdges.Clear();
  myNbFaces  = 0;
  myNbShells = 0;
  myNbSolids = 0;
  myNbWires  = 0;
  myNbEdges  = 0;
}

void STEPSelections_Counter::AddShell(const occ::handle<StepShape_ConnectedFaceSet>& cfs)
{
  myMapOfShells.Add(cfs);
  myNbShells++;
  int nbf = cfs->NbCfsFaces();
  for (int i = 1; i <= nbf; i++)
    myMapOfFaces.Add(cfs->CfsFacesValue(i));
  myNbFaces += nbf;
  return;
}

void STEPSelections_Counter::AddCompositeCurve(const occ::handle<StepGeom_CompositeCurve>& ccurve)
{
  int nbs = ccurve->NbSegments();
  for (int i = 1; i <= nbs; i++)
  {
    //  #ifdef AIX   CKY : common code for all platforms: Handle() not Handle()&
    occ::handle<StepGeom_CompositeCurveSegment> ccs = ccurve->SegmentsValue(i);
    occ::handle<StepGeom_Curve>                 crv = ccs->ParentCurve();

    if (crv->IsKind(STANDARD_TYPE(StepGeom_CompositeCurve)))
      AddCompositeCurve(occ::down_cast<StepGeom_CompositeCurve>(crv));
    else
    {
      myNbEdges++;
      myMapOfEdges.Add(crv);
    }
  }
}
