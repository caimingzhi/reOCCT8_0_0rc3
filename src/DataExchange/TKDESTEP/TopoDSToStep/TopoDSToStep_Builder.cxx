#include <Message_ProgressScope.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepShape_ClosedShell.hpp>
#include <StepShape_ConnectedFaceSet.hpp>
#include <StepShape_Face.hpp>
#include <StepShape_FaceSurface.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_OpenShell.hpp>
#include <StepShape_TopologicalRepresentationItem.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDSToStep_Builder.hpp>
#include <TopoDSToStep_MakeStepFace.hpp>
#include <TopoDSToStep_MakeTessellatedItem.hpp>
#include <TopoDSToStep_Tool.hpp>
#include <Transfer_FinderProcess.hpp>

TopoDSToStep_Builder::TopoDSToStep_Builder()
    : myError(TopoDSToStep_BuilderOther)
{
  done = false;
}

TopoDSToStep_Builder::TopoDSToStep_Builder(const TopoDS_Shape&                        aShape,
                                           TopoDSToStep_Tool&                         aTool,
                                           const occ::handle<Transfer_FinderProcess>& FP,
                                           const int                    theTessellatedGeomParam,
                                           const StepData_Factors&      theLocalFactors,
                                           const Message_ProgressRange& theProgress)
{
  done = false;
  Init(aShape, aTool, FP, theTessellatedGeomParam, theLocalFactors, theProgress);
}

void TopoDSToStep_Builder::Init(const TopoDS_Shape&                        aShape,
                                TopoDSToStep_Tool&                         myTool,
                                const occ::handle<Transfer_FinderProcess>& FP,
                                const int                                  theTessellatedGeomParam,
                                const StepData_Factors&                    theLocalFactors,
                                const Message_ProgressRange&               theProgress)
{

  if (myTool.IsBound(aShape))
  {
    myError  = TopoDSToStep_BuilderDone;
    done     = true;
    myResult = myTool.Find(aShape);
    return;
  }

  switch (aShape.ShapeType())
  {
    case TopAbs_SHELL:
    {
      TopoDS_Shell myShell = TopoDS::Shell(aShape);
      myTool.SetCurrentShell(myShell);

      occ::handle<StepShape_FaceSurface>                    FS;
      occ::handle<StepShape_TopologicalRepresentationItem>  Fpms;
      NCollection_Sequence<occ::handle<Standard_Transient>> mySeq;

      TopExp_Explorer anExp;

      TopoDSToStep_MakeStepFace MkFace;

      Message_ProgressScope aPS(theProgress, nullptr, (theTessellatedGeomParam != 0) ? 2 : 1);

      int nbshapes = 0;
      for (anExp.Init(myShell, TopAbs_FACE); anExp.More(); anExp.Next())
        nbshapes++;
      Message_ProgressScope aPS1(aPS.Next(), nullptr, nbshapes);
      for (anExp.Init(myShell, TopAbs_FACE); anExp.More() && aPS1.More(); anExp.Next(), aPS1.Next())
      {
        const TopoDS_Face Face = TopoDS::Face(anExp.Current());

        MkFace.Init(Face, myTool, FP, theLocalFactors);

        if (MkFace.IsDone())
        {
          FS   = occ::down_cast<StepShape_FaceSurface>(MkFace.Value());
          Fpms = FS;
          mySeq.Append(Fpms);
        }
        else
        {
        }
      }
      if (!aPS1.More())
        return;

      int nbFaces = mySeq.Length();
      if (nbFaces >= 1)
      {
        occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>> aSet =
          new NCollection_HArray1<occ::handle<StepShape_Face>>(1, nbFaces);
        for (int i = 1; i <= nbFaces; i++)
        {
          aSet->SetValue(i, occ::down_cast<StepShape_Face>(mySeq.Value(i)));
        }
        occ::handle<StepShape_ConnectedFaceSet> CFSpms;
        if (myShell.Closed())
          CFSpms = new StepShape_ClosedShell();
        else
          CFSpms = new StepShape_OpenShell();
        occ::handle<TCollection_HAsciiString> aName = new TCollection_HAsciiString("");
        CFSpms->Init(aName, aSet);

        myTool.Bind(aShape, CFSpms);
        myResult = CFSpms;
        done     = true;
      }
      else
      {

        myError = TopoDSToStep_NoFaceMapped;
        done    = false;
      }

      if (theTessellatedGeomParam == 1 || (theTessellatedGeomParam == 2 && myResult.IsNull()))
      {
        TopoDSToStep_MakeTessellatedItem MkTessShell(myShell,
                                                     myTool,
                                                     FP,
                                                     theLocalFactors,
                                                     aPS.Next());
        if (MkTessShell.IsDone())
        {
          myTessellatedResult = MkTessShell.Value();
          myError             = TopoDSToStep_BuilderDone;
          done                = true;
        }
      }
      break;
    }

    case TopAbs_FACE:
    {
      const TopoDS_Face Face = TopoDS::Face(aShape);

      occ::handle<StepShape_FaceSurface>                   FS;
      occ::handle<StepShape_TopologicalRepresentationItem> Fpms;

      TopoDSToStep_MakeStepFace MkFace(Face, myTool, FP, theLocalFactors);

      TopoDSToStep_MakeTessellatedItem MkTessFace;

      if (theTessellatedGeomParam == 1 || (theTessellatedGeomParam == 2 && !MkFace.IsDone()))
      {
        Message_ProgressScope aPS(theProgress, nullptr, 1);

        MkTessFace.Init(Face, myTool, FP, true, theLocalFactors, aPS.Next());
      }

      if (MkFace.IsDone() || MkTessFace.IsDone())
      {
        if (MkFace.IsDone())
        {
          FS       = occ::down_cast<StepShape_FaceSurface>(MkFace.Value());
          Fpms     = FS;
          myResult = Fpms;
        }
        if (MkTessFace.IsDone())
        {
          myTessellatedResult = MkTessFace.Value();
        }
        myError = TopoDSToStep_BuilderDone;
        done    = true;
      }
      else
      {

        myError = TopoDSToStep_BuilderOther;

        done = false;
      }
      break;
    }
    default:
      break;
  }
}

const occ::handle<StepShape_TopologicalRepresentationItem>& TopoDSToStep_Builder::Value() const
{
  StdFail_NotDone_Raise_if(!done, "TopoDSToStep_Builder::Value() - no result");
  return myResult;
}

const occ::handle<StepVisual_TessellatedItem>& TopoDSToStep_Builder::TessellatedValue() const
{
  StdFail_NotDone_Raise_if(!done, "TopoDSToStep_Builder::TessellatedValue() - no result");
  return myTessellatedResult;
}

TopoDSToStep_BuilderError TopoDSToStep_Builder::Error() const
{
  return myError;
}
