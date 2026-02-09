

#include <BRep_Builder.hpp>
#include <Message_ProgressScope.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepShape_ConnectedFaceSet.hpp>
#include <StepShape_FaceSurface.hpp>
#include <StepToTopoDS_NMTool.hpp>
#include <StepToTopoDS_Tool.hpp>
#include <StepToTopoDS_TranslateFace.hpp>
#include <StepToTopoDS_TranslateSolid.hpp>
#include <StepVisual_TessellatedFace.hpp>
#include <StepVisual_TessellatedSolid.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <Transfer_TransientProcess.hpp>
#include <TransferBRep_ShapeBinder.hpp>

StepToTopoDS_TranslateSolid::StepToTopoDS_TranslateSolid()
    : myError(StepToTopoDS_TranslateSolidOther)
{
  done = false;
}

void StepToTopoDS_TranslateSolid::Init(const occ::handle<StepVisual_TessellatedSolid>& theTSo,
                                       const occ::handle<Transfer_TransientProcess>&   theTP,
                                       StepToTopoDS_Tool&                              theTool,
                                       StepToTopoDS_NMTool&                            theNMTool,
                                       const bool              theReadTessellatedWhenNoBRepOnly,
                                       bool&                   theHasGeom,
                                       const StepData_Factors& theLocalFactors,
                                       const Message_ProgressRange& theProgress)
{
  if (theTSo.IsNull())
    return;

  BRep_Builder aB;
  TopoDS_Shell aSh;
  TopoDS_Solid aSo;

  int                   aNb = theTSo->NbItems();
  Message_ProgressScope aPS(theProgress, "Face", aNb);

  if (theTSo->HasGeometricLink() && theTP->IsBound(theTSo->GeometricLink()))
  {
    occ::handle<TransferBRep_ShapeBinder> aBinder =
      occ::down_cast<TransferBRep_ShapeBinder>(theTP->Find(theTSo->GeometricLink()));
    if (aBinder)
      aSo = aBinder->Solid();
  }

  bool aNewSolid = false;
  if (aSo.IsNull())
  {
    aB.MakeShell(aSh);
    aB.MakeSolid(aSo);
    aNewSolid  = true;
    theHasGeom = false;
  }

  occ::handle<Transfer_TransientProcess> aTP = theTool.TransientProcess();

  StepToTopoDS_TranslateFace aTranTF;
  aTranTF.SetPrecision(Precision());
  aTranTF.SetMaxTol(MaxTol());

  for (int i = 1; i <= aNb && aPS.More(); i++, aPS.Next())
  {
#ifdef OCCT_DEBUG
    std::cout << "Processing Face : " << i << std::endl;
#endif
    occ::handle<StepVisual_TessellatedStructuredItem> anItem = theTSo->ItemsValue(i);
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
        if (aNewSolid)
        {
          aB.Add(aSh, TopoDS::Face(aTranTF.Value()));
        }
        theHasGeom &= aHasFaceGeom;
      }
      else
      {
        aTP->AddWarning(anItem, " Tessellated face if not mapped to TopoDS");
      }
    }
    else
    {
      aTP->AddWarning(anItem, " Face is not of TessellatedFace Type; not mapped to TopoDS");
    }
  }

  if (aNewSolid)
  {
    aB.Add(aSo, aSh);
  }

  myResult = aSo;
  myError  = StepToTopoDS_TranslateSolidDone;
  done     = true;
}

const TopoDS_Shape& StepToTopoDS_TranslateSolid::Value() const
{
  StdFail_NotDone_Raise_if(!done, "StepToTopoDS_TranslateSolid::Value() - no result");
  return myResult;
}

StepToTopoDS_TranslateSolidError StepToTopoDS_TranslateSolid::Error() const
{
  return myError;
}
