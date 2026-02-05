#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepToTopoDS_TranslateShellError.hpp>
#include <TopoDS_Shape.hpp>
#include <StepToTopoDS_Root.hpp>
#include <Message_ProgressRange.hpp>

class StepShape_ConnectedFaceSet;
class StepVisual_TessellatedShell;
class StepToTopoDS_Tool;
class StepToTopoDS_NMTool;

class StepToTopoDS_TranslateShell : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_TranslateShell();

  Standard_EXPORT void Init(const occ::handle<StepShape_ConnectedFaceSet>& CFS,
                            StepToTopoDS_Tool&                             T,
                            StepToTopoDS_NMTool&                           NMTool,
                            const StepData_Factors&      theLocalFactors = StepData_Factors(),
                            const Message_ProgressRange& theProgress     = Message_ProgressRange());

  Standard_EXPORT void Init(const occ::handle<StepVisual_TessellatedShell>& theTSh,
                            StepToTopoDS_Tool&                              theTool,
                            StepToTopoDS_NMTool&                            theNMTool,
                            const bool                   theReadTessellatedWhenNoBRepOnly,
                            bool&                        theHasGeom,
                            const StepData_Factors&      theLocalFactors = StepData_Factors(),
                            const Message_ProgressRange& theProgress     = Message_ProgressRange());

  Standard_EXPORT const TopoDS_Shape& Value() const;

  Standard_EXPORT StepToTopoDS_TranslateShellError Error() const;

private:
  StepToTopoDS_TranslateShellError myError;
  TopoDS_Shape                     myResult;
};
