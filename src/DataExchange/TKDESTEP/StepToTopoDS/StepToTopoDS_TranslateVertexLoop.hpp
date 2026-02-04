#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepToTopoDS_TranslateVertexLoopError.hpp>
#include <TopoDS_Shape.hpp>
#include <StepToTopoDS_Root.hpp>
class StepShape_VertexLoop;
class StepToTopoDS_Tool;
class StepToTopoDS_NMTool;

class StepToTopoDS_TranslateVertexLoop : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_TranslateVertexLoop();

  Standard_EXPORT StepToTopoDS_TranslateVertexLoop(
    const occ::handle<StepShape_VertexLoop>& VL,
    StepToTopoDS_Tool&                       T,
    StepToTopoDS_NMTool&                     NMTool,
    const StepData_Factors&                  theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const occ::handle<StepShape_VertexLoop>& VL,
                            StepToTopoDS_Tool&                       T,
                            StepToTopoDS_NMTool&                     NMTool,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT const TopoDS_Shape& Value() const;

  Standard_EXPORT StepToTopoDS_TranslateVertexLoopError Error() const;

private:
  StepToTopoDS_TranslateVertexLoopError myError;
  TopoDS_Shape                          myResult;
};

