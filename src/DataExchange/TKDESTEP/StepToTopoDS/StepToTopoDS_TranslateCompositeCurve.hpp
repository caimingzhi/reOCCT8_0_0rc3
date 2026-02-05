#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Wire.hpp>
#include <StepToTopoDS_Root.hpp>
class StepGeom_CompositeCurve;
class Transfer_TransientProcess;
class StepGeom_Surface;
class Geom_Surface;

//! Translate STEP entity composite_curve to TopoDS_Wire
//! If surface is given, the curve is assumed to lie on that
//! surface and in case if any segment of it is a
//! curve_on_surface, the pcurve for that segment will be taken.
//! Note: a segment of composite_curve may be itself
//! composite_curve. Only one-level protection against
//! cyclic references is implemented.
class StepToTopoDS_TranslateCompositeCurve : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepToTopoDS_TranslateCompositeCurve();

  //! Translates standalone composite_curve
  Standard_EXPORT StepToTopoDS_TranslateCompositeCurve(
    const occ::handle<StepGeom_CompositeCurve>&   CC,
    const occ::handle<Transfer_TransientProcess>& TP,
    const StepData_Factors&                       theLocalFactors = StepData_Factors());

  //! Translates composite_curve lying on surface
  Standard_EXPORT StepToTopoDS_TranslateCompositeCurve(
    const occ::handle<StepGeom_CompositeCurve>&   CC,
    const occ::handle<Transfer_TransientProcess>& TP,
    const occ::handle<StepGeom_Surface>&          S,
    const occ::handle<Geom_Surface>&              Surf,
    const StepData_Factors&                       theLocalFactors = StepData_Factors());

  //! Translates standalone composite_curve
  Standard_EXPORT bool Init(const occ::handle<StepGeom_CompositeCurve>&   CC,
                            const occ::handle<Transfer_TransientProcess>& TP,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  //! Translates composite_curve lying on surface
  Standard_EXPORT bool Init(const occ::handle<StepGeom_CompositeCurve>&   CC,
                            const occ::handle<Transfer_TransientProcess>& TP,
                            const occ::handle<StepGeom_Surface>&          S,
                            const occ::handle<Geom_Surface>&              Surf,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  //! Returns result of last translation or null wire if failed.
  Standard_EXPORT const TopoDS_Wire& Value() const;

  //! Returns True if composite_curve contains a segment with infinite parameters.
  bool IsInfiniteSegment() const;

private:
  TopoDS_Wire myWire;
  bool        myInfiniteSegment;
};

#include <StepToTopoDS_TranslateCompositeCurve.hpp>

//=================================================================================================

inline bool StepToTopoDS_TranslateCompositeCurve::IsInfiniteSegment() const
{
  return myInfiniteSegment;
}
