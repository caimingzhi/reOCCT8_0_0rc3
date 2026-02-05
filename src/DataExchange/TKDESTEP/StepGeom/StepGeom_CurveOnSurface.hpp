#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepGeom_Pcurve;
class StepGeom_SurfaceCurve;
class StepGeom_CompositeCurveOnSurface;

class StepGeom_CurveOnSurface : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a CurveOnSurface SelectType
  Standard_EXPORT StepGeom_CurveOnSurface();

  //! Recognizes a CurveOnSurface Kind Entity that is :
  //! 1 -> Pcurve
  //! 2 -> SurfaceCurve
  //! 3 -> CompositeCurveOnSurface
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a Pcurve (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_Pcurve> Pcurve() const;

  //! returns Value as a SurfaceCurve (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_SurfaceCurve> SurfaceCurve() const;

  //! returns Value as a CompositeCurveOnSurface (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_CompositeCurveOnSurface> CompositeCurveOnSurface() const;
};
