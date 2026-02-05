#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Face.hpp>
#include <StepToTopoDS_Root.hpp>
class StepGeom_CurveBoundedSurface;
class Transfer_TransientProcess;

//! Translate curve_bounded_surface into TopoDS_Face
class StepToTopoDS_TranslateCurveBoundedSurface : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Create empty tool
  Standard_EXPORT StepToTopoDS_TranslateCurveBoundedSurface();

  //! Translate surface
  Standard_EXPORT StepToTopoDS_TranslateCurveBoundedSurface(
    const occ::handle<StepGeom_CurveBoundedSurface>& CBS,
    const occ::handle<Transfer_TransientProcess>&    TP,
    const StepData_Factors&                          theLocalFactors = StepData_Factors());

  //! Translate surface
  Standard_EXPORT bool Init(const occ::handle<StepGeom_CurveBoundedSurface>& CBS,
                            const occ::handle<Transfer_TransientProcess>&    TP,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  //! Returns result of last translation or null wire if failed.
  Standard_EXPORT const TopoDS_Face& Value() const;

private:
  TopoDS_Face myFace;
};
