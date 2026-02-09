#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Face.hpp>
#include <StepToTopoDS_Root.hpp>
class StepGeom_CurveBoundedSurface;
class Transfer_TransientProcess;

class StepToTopoDS_TranslateCurveBoundedSurface : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_TranslateCurveBoundedSurface();

  Standard_EXPORT StepToTopoDS_TranslateCurveBoundedSurface(
    const occ::handle<StepGeom_CurveBoundedSurface>& CBS,
    const occ::handle<Transfer_TransientProcess>&    TP,
    const StepData_Factors&                          theLocalFactors = StepData_Factors());

  Standard_EXPORT bool Init(const occ::handle<StepGeom_CurveBoundedSurface>& CBS,
                            const occ::handle<Transfer_TransientProcess>&    TP,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT const TopoDS_Face& Value() const;

private:
  TopoDS_Face myFace;
};
