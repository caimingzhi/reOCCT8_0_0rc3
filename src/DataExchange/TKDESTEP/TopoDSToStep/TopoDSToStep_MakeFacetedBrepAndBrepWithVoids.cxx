#include <BRepClass3d.hpp>
#include <Message_ProgressScope.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Transient.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepData_StepModel.hpp>
#include <StepShape_ClosedShell.hpp>
#include <StepShape_FacetedBrepAndBrepWithVoids.hpp>
#include <StepShape_OrientedClosedShell.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_TopologicalRepresentationItem.hpp>
#include <StepVisual_TessellatedStructuredItem.hpp>
#include <StepVisual_TessellatedShell.hpp>
#include <StepVisual_TessellatedSolid.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>
#include <TopoDSToStep.hpp>
#include <TopoDSToStep_Builder.hpp>
#include <TopoDSToStep_MakeFacetedBrepAndBrepWithVoids.hpp>
#include <TopoDSToStep_Tool.hpp>
#include <Transfer_FinderProcess.hpp>
#include <TransferBRep_ShapeMapper.hpp>

TopoDSToStep_MakeFacetedBrepAndBrepWithVoids::TopoDSToStep_MakeFacetedBrepAndBrepWithVoids(
  const TopoDS_Solid&                        aSolid,
  const occ::handle<Transfer_FinderProcess>& FP,
  const StepData_Factors&                    theLocalFactors,
  const Message_ProgressRange&               theProgress)
{
  done = false;
  TopoDS_Iterator                                                                             It;
  NCollection_DataMap<TopoDS_Shape, occ::handle<Standard_Transient>, TopTools_ShapeMapHasher> aMap;
  NCollection_Sequence<occ::handle<Standard_Transient>>                                       S;
  TopoDS_Shell aOutShell;

  occ::handle<StepShape_TopologicalRepresentationItem>                         aItem;
  occ::handle<StepShape_ClosedShell>                                           aOuter, aCShell;
  occ::handle<StepShape_OrientedClosedShell>                                   aOCShell;
  occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedClosedShell>>> aVoids;
  NCollection_Sequence<occ::handle<Standard_Transient>>                        aTessShells;

  aOutShell = BRepClass3d::OuterShell(aSolid);

  occ::handle<StepData_StepModel> aStepModel = occ::down_cast<StepData_StepModel>(FP->Model());
  TopoDSToStep_Builder            StepB;
  TopoDSToStep_Tool               aTool(aStepModel);

  if (!aOutShell.IsNull())
  {
    int nbshapes = 0;
    for (It.Initialize(aSolid); It.More(); It.Next())
      if (It.Value().ShapeType() == TopAbs_SHELL)
        nbshapes++;
    Message_ProgressScope aPS(theProgress, nullptr, nbshapes);
    for (It.Initialize(aSolid); It.More() && aPS.More(); It.Next())
    {
      if (It.Value().ShapeType() == TopAbs_SHELL)
      {
        Message_ProgressRange aRange       = aPS.Next();
        TopoDS_Shell          CurrentShell = TopoDS::Shell(It.Value());
        if (It.Value().Closed())
        {

          aTool.Init(aMap, false, aStepModel->InternalParameters.WriteSurfaceCurMode);
          StepB.Init(CurrentShell, aTool, FP, false, theLocalFactors, aRange);
          TopoDSToStep::AddResult(FP, aTool);

          if (StepB.IsDone())
          {
            aCShell = occ::down_cast<StepShape_ClosedShell>(StepB.Value());
            if (aOutShell.IsEqual(It.Value()))
              aOuter = aCShell;
            else
              S.Append(aCShell);
            occ::handle<StepVisual_TessellatedItem> aTessShell = StepB.TessellatedValue();
            if (!aTessShell.IsNull())
            {
              aTessShells.Append(aTessShell);
            }
          }
          else
          {
            occ::handle<TransferBRep_ShapeMapper> errShape =
              new TransferBRep_ShapeMapper(CurrentShell);
            FP->AddWarning(errShape, " Shell from Solid not mapped to FacetedBrepAndBrepWithVoids");
          }
        }
        else
        {
          done = false;
          occ::handle<TransferBRep_ShapeMapper> errShape =
            new TransferBRep_ShapeMapper(CurrentShell);
          FP->AddWarning(errShape,
                         " Shell from Solid not closed; not mapped to FacetedBrepAndBrepWithVoids");
        }
      }
    }
    if (!aPS.More())
      return;
  }
  int N = S.Length();
  if (N >= 1)
  {
    aVoids = new NCollection_HArray1<occ::handle<StepShape_OrientedClosedShell>>(1, N);
    occ::handle<TCollection_HAsciiString> aName = new TCollection_HAsciiString("");
    for (int i = 1; i <= N; i++)
    {
      aOCShell = new StepShape_OrientedClosedShell();
      aOCShell->Init(aName, occ::down_cast<StepShape_ClosedShell>(S.Value(i)), true);
      aVoids->SetValue(i, aOCShell);
    }
    theFacetedBrepAndBrepWithVoids = new StepShape_FacetedBrepAndBrepWithVoids();
    theFacetedBrepAndBrepWithVoids->Init(aName, aOuter, aVoids);

    if (!aTessShells.IsEmpty())
    {
      occ::handle<StepVisual_TessellatedSolid> aTessSolid = new StepVisual_TessellatedSolid();
      occ::handle<TCollection_HAsciiString>    aTessName  = new TCollection_HAsciiString("");
      int                                      aNbItems   = 0;
      for (NCollection_Sequence<occ::handle<Standard_Transient>>::Iterator anIt(aTessShells);
           anIt.More();
           anIt.Next())
      {
        occ::handle<StepVisual_TessellatedShell> aTessShell =
          occ::down_cast<StepVisual_TessellatedShell>(anIt.Value());
        aNbItems += aTessShell->NbItems();
      }
      occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>> anItems =
        new NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>(1, aNbItems);
      for (NCollection_Sequence<occ::handle<Standard_Transient>>::Iterator anIt(aTessShells);
           anIt.More();
           anIt.Next())
      {
        occ::handle<StepVisual_TessellatedShell> aTessShell =
          occ::down_cast<StepVisual_TessellatedShell>(anIt.Value());
        for (int i = 1; i <= aTessShell->NbItems(); ++i)
        {
          anItems->SetValue(i, aTessShell->ItemsValue(i));
        }
      }
      bool aHasGeomLink = !theFacetedBrepAndBrepWithVoids.IsNull();
      aTessSolid->Init(aTessName, anItems, aHasGeomLink, theFacetedBrepAndBrepWithVoids);
      theTessellatedItem = aTessSolid;
    }

    done = true;
  }
  else
  {
    done                                           = false;
    occ::handle<TransferBRep_ShapeMapper> errShape = new TransferBRep_ShapeMapper(aSolid);
    FP->AddWarning(errShape,
                   " Solid contains no Shell to be mapped to FacetedBrepAndBrepWithVoids");
  }
}

const occ::handle<StepShape_FacetedBrepAndBrepWithVoids>&
  TopoDSToStep_MakeFacetedBrepAndBrepWithVoids::Value() const
{
  StdFail_NotDone_Raise_if(!done,
                           "TopoDSToStep_MakeFacetedBrepAndBrepWithVoids::Value() - no result");
  return theFacetedBrepAndBrepWithVoids;
}

const occ::handle<StepVisual_TessellatedItem>& TopoDSToStep_MakeFacetedBrepAndBrepWithVoids::
  TessellatedValue() const
{
  StdFail_NotDone_Raise_if(
    !done,
    "TopoDSToStep_MakeFacetedBrepAndBrepWithVoids::TessellatedValue() - no result");
  return theTessellatedItem;
}
