#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepToTopoDS_TranslateVertexError.hpp>
#include <TopoDS_Shape.hpp>
#include <StepToTopoDS_Root.hpp>
class StepShape_Vertex;
class StepToTopoDS_Tool;
class StepToTopoDS_NMTool;

class StepToTopoDS_TranslateVertex : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_TranslateVertex();

  Standard_EXPORT StepToTopoDS_TranslateVertex(
    const occ::handle<StepShape_Vertex>& V,
    StepToTopoDS_Tool&                   T,
    StepToTopoDS_NMTool&                 NMTool,
    const StepData_Factors&              theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const occ::handle<StepShape_Vertex>& V,
                            StepToTopoDS_Tool&                   T,
                            StepToTopoDS_NMTool&                 NMTool,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT const TopoDS_Shape& Value() const;

  Standard_EXPORT StepToTopoDS_TranslateVertexError Error() const;

private:
  StepToTopoDS_TranslateVertexError myError;
  TopoDS_Shape                      myResult;
};
