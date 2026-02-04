#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDSToStep_Root.hpp>
#include <Message_ProgressRange.hpp>

class StepData_Factors;
class StepVisual_TessellatedItem;
class TopoDS_Face;
class TopoDS_Shell;
class Transfer_FinderProcess;

//! This class implements the mapping between
//! Face, Shell fromTopoDS and TriangulatedFace from StepVisual.
class TopoDSToStep_MakeTessellatedItem : public TopoDSToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopoDSToStep_MakeTessellatedItem();

  Standard_EXPORT TopoDSToStep_MakeTessellatedItem(
    const TopoDS_Face&                         theFace,
    TopoDSToStep_Tool&                         theTool,
    const occ::handle<Transfer_FinderProcess>& theFP,
    const bool                                 theToPreferSurfaceSet,
    const StepData_Factors&                    theLocalFactors,
    const Message_ProgressRange&               theProgress = Message_ProgressRange());

  Standard_EXPORT TopoDSToStep_MakeTessellatedItem(
    const TopoDS_Shell&                        theShell,
    TopoDSToStep_Tool&                         theTool,
    const occ::handle<Transfer_FinderProcess>& theFP,
    const StepData_Factors&                    theLocalFactors,
    const Message_ProgressRange&               theProgress = Message_ProgressRange());

  Standard_EXPORT void Init(const TopoDS_Face&                         theFace,
                            TopoDSToStep_Tool&                         theTool,
                            const occ::handle<Transfer_FinderProcess>& theFP,
                            const bool                                 theToPreferSurfaceSet,
                            const StepData_Factors&                    theLocalFactors,
                            const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void Init(const TopoDS_Shell&                        theShell,
                            TopoDSToStep_Tool&                         theTool,
                            const occ::handle<Transfer_FinderProcess>& theFP,
                            const StepData_Factors&                    theLocalFactors,
                            const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT const occ::handle<StepVisual_TessellatedItem>& Value() const;

private:
  occ::handle<StepVisual_TessellatedItem> theTessellatedItem;
};

