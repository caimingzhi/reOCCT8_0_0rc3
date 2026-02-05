#include <BRep_Builder.hpp>
#include <Message_ProgressScope.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepShape_ConnectedFaceSet.hpp>
#include <StepShape_FaceSurface.hpp>
#include <StepToTopoDS_NMTool.hpp>
#include <StepToTopoDS_Tool.hpp>
#include <StepToTopoDS_TranslateFace.hpp>
#include <StepToTopoDS_TranslateShell.hpp>
#include <StepVisual_TessellatedShell.hpp>
#include <StepVisual_TriangulatedFace.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <Transfer_TransientProcess.hpp>
#include <TransferBRep_ShapeBinder.hpp>

//=================================================================================================

StepToTopoDS_TranslateShell::StepToTopoDS_TranslateShell()
    : myError(StepToTopoDS_TranslateShellOther)
{
  done = false;
}

// ============================================================================
// Method  : Init
// Purpose : Init with a ConnectedFaceSet and a Tool
// ============================================================================

void StepToTopoDS_TranslateShell::Init(const occ::handle<StepShape_ConnectedFaceSet>& CFS,
                                       StepToTopoDS_Tool&                             aTool,
                                       StepToTopoDS_NMTool&                           NMTool,
                                       const StepData_Factors&      theLocalFactors,
                                       const Message_ProgressRange& theProgress)
{
  // bug15697
  if (CFS.IsNull())
    return;

  if (!aTool.IsBound(CFS))
  {

    BRep_Builder                           B;
    occ::handle<Transfer_TransientProcess> TP = aTool.TransientProcess();

    int          NbFc = CFS->NbCfsFaces();
    TopoDS_Shell Sh;
    B.MakeShell(Sh);
    TopoDS_Face                 F;
    TopoDS_Shape                S;
    occ::handle<StepShape_Face> StepFace;

    StepToTopoDS_TranslateFace myTranFace;
    myTranFace.SetPrecision(Precision()); // gka
    myTranFace.SetMaxTol(MaxTol());

    Message_ProgressScope PS(theProgress, "Face", NbFc);
    for (int i = 1; i <= NbFc && PS.More(); i++, PS.Next())
    {
#ifdef OCCT_DEBUG
      std::cout << "Processing Face : " << i << std::endl;
#endif
      StepFace                                 = CFS->CfsFacesValue(i);
      occ::handle<StepShape_FaceSurface> theFS = occ::down_cast<StepShape_FaceSurface>(StepFace);
      if (!theFS.IsNull())
      {
        myTranFace.Init(theFS, aTool, NMTool, theLocalFactors);
        if (myTranFace.IsDone())
        {
          S = myTranFace.Value();
          F = TopoDS::Face(S);
          B.Add(Sh, F);
        }
        else
        { // Warning only + add FaceSurface file Identifier
          TP->AddWarning(theFS, " a Face from Shell not mapped to TopoDS");
        }
      }
      else
      { // Warning : add identifier
        TP->AddWarning(StepFace, " Face is not of FaceSurface Type; not mapped to TopoDS");
      }
    }
    Sh.Closed(BRep_Tool::IsClosed(Sh));
    myResult = Sh;
    aTool.Bind(CFS, myResult);
    myError = StepToTopoDS_TranslateShellDone;
    done    = true;
  }
  else
  {
    myResult = TopoDS::Shell(aTool.Find(CFS));
    myError  = StepToTopoDS_TranslateShellDone;
    done     = true;
  }
}

// ============================================================================
// Method  : Init
// Purpose : Init with a ConnectedFaceSet and a Tool
// ============================================================================

void StepToTopoDS_TranslateShell::Init(const occ::handle<StepVisual_TessellatedShell>& theTSh,
                                       StepToTopoDS_Tool&                              theTool,
                                       StepToTopoDS_NMTool&                            theNMTool,
                                       const bool              theReadTessellatedWhenNoBRepOnly,
                                       bool&                   theHasGeom,
                                       const StepData_Factors& theLocalFactors,
                                       const Message_ProgressRange& theProgress)
{
  if (theTSh.IsNull())
    return;

  BRep_Builder aB;
  TopoDS_Shell aSh;

  int                   aNb = theTSh->NbItems();
  Message_ProgressScope aPS(theProgress, "Face", theTSh->HasTopologicalLink() ? aNb + 1 : aNb);

  occ::handle<Transfer_TransientProcess> aTP = theTool.TransientProcess();

  if (theTSh->HasTopologicalLink())
  {
    occ::handle<TransferBRep_ShapeBinder> aBinder =
      occ::down_cast<TransferBRep_ShapeBinder>(aTP->Find(theTSh->TopologicalLink()));
    if (!aBinder.IsNull())
    {
      aSh        = aBinder->Shell();
      theHasGeom = true;
    }
  }

  bool aNewShell = false;
  if (aSh.IsNull())
  {
    aB.MakeShell(aSh);
    aNewShell  = true;
    theHasGeom = false;
  }

  StepToTopoDS_TranslateFace aTranTF;
  aTranTF.SetPrecision(Precision());
  aTranTF.SetMaxTol(MaxTol());

  for (int i = 1; i <= aNb && aPS.More(); i++, aPS.Next())
  {
#ifdef OCCT_DEBUG
    std::cout << "Processing Face : " << i << std::endl;
#endif
    occ::handle<StepVisual_TessellatedStructuredItem> anItem = theTSh->ItemsValue(i);
    if (anItem->IsKind(STANDARD_TYPE(StepVisual_TessellatedFace)))
    {
      occ::handle<StepVisual_TessellatedFace> aTFace =
        occ::down_cast<StepVisual_TessellatedFace>(anItem);
      bool aHasFaceGeom = false;
      aTranTF.Init(aTFace,
                   theTool,
                   theNMTool,
                   theReadTessellatedWhenNoBRepOnly,
                   aHasFaceGeom,
                   theLocalFactors);
      if (aTranTF.IsDone())
      {
        if (aNewShell)
        {
          aB.Add(aSh, TopoDS::Face(aTranTF.Value()));
        }
        theHasGeom &= aHasFaceGeom;
      }
      else
      {
        aTP->AddWarning(anItem, " Triangulated face if not mapped to TopoDS");
      }
    }
    else
    {
      aTP->AddWarning(anItem, " Face is not of TriangulatedFace Type; not mapped to TopoDS");
    }
  }

  aSh.Closed(BRep_Tool::IsClosed(aSh));
  myResult = aSh;
  myError  = StepToTopoDS_TranslateShellDone;
  done     = true;
}

// ============================================================================
// Method  : Value
// Purpose : Return the mapped Shape
// ============================================================================

const TopoDS_Shape& StepToTopoDS_TranslateShell::Value() const
{
  StdFail_NotDone_Raise_if(!done, "StepToTopoDS_TranslateShell::Value() - no result");
  return myResult;
}

// ============================================================================
// Method  : Error
// Purpose : Return the TranslateShell Error code
// ============================================================================

StepToTopoDS_TranslateShellError StepToTopoDS_TranslateShell::Error() const
{
  return myError;
}
