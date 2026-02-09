#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

enum StepToTopoDS_TranslateSolidError
{
  StepToTopoDS_TranslateSolidDone,
  StepToTopoDS_TranslateSolidOther
};

#include <TopoDS_Shape.hpp>
#include <StepToTopoDS_Root.hpp>
#include <Message_ProgressRange.hpp>

class StepShape_ConnectedFaceSet;
class StepVisual_TessellatedSolid;
class StepToTopoDS_Tool;
class StepToTopoDS_NMTool;
class Transfer_TransientProcess;

class StepToTopoDS_TranslateSolid : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_TranslateSolid();

  Standard_EXPORT void Init(const occ::handle<StepVisual_TessellatedSolid>& theTSo,
                            const occ::handle<Transfer_TransientProcess>&   theTP,
                            StepToTopoDS_Tool&                              theTool,
                            StepToTopoDS_NMTool&                            theNMTool,
                            const bool                   theReadTessellatedWhenNoBRepOnly,
                            bool&                        theHasGeom,
                            const StepData_Factors&      theLocalFactors = StepData_Factors(),
                            const Message_ProgressRange& theProgress     = Message_ProgressRange());

  Standard_EXPORT const TopoDS_Shape& Value() const;

  Standard_EXPORT StepToTopoDS_TranslateSolidError Error() const;

private:
  StepToTopoDS_TranslateSolidError myError;
  TopoDS_Shape                     myResult;
};
