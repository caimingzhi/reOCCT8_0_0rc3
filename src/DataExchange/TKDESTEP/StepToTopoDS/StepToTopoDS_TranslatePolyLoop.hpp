#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepToTopoDS_TranslatePolyLoopError.hpp>
#include <TopoDS_Shape.hpp>
#include <StepToTopoDS_Root.hpp>
class StepShape_PolyLoop;
class StepToTopoDS_Tool;
class Geom_Surface;
class TopoDS_Face;

class StepToTopoDS_TranslatePolyLoop : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_TranslatePolyLoop();

  Standard_EXPORT StepToTopoDS_TranslatePolyLoop(
    const occ::handle<StepShape_PolyLoop>& PL,
    StepToTopoDS_Tool&                     T,
    const occ::handle<Geom_Surface>&       S,
    const TopoDS_Face&                     F,
    const StepData_Factors&                theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const occ::handle<StepShape_PolyLoop>& PL,
                            StepToTopoDS_Tool&                     T,
                            const occ::handle<Geom_Surface>&       S,
                            const TopoDS_Face&                     F,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT const TopoDS_Shape& Value() const;

  Standard_EXPORT StepToTopoDS_TranslatePolyLoopError Error() const;

private:
  StepToTopoDS_TranslatePolyLoopError myError;
  TopoDS_Shape                        myResult;
};
