#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepGeom_BoundaryCurve;
class StepGeom_DegeneratePcurve;

//! Representation of STEP SELECT type SurfaceBoundary
class StepGeom_SurfaceBoundary : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepGeom_SurfaceBoundary();

  //! Recognizes a kind of SurfaceBoundary select type
  //! 1 -> BoundaryCurve from StepGeom
  //! 2 -> DegeneratePcurve from StepGeom
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as BoundaryCurve (or Null if another type)
  Standard_EXPORT occ::handle<StepGeom_BoundaryCurve> BoundaryCurve() const;

  //! Returns Value as DegeneratePcurve (or Null if another type)
  Standard_EXPORT occ::handle<StepGeom_DegeneratePcurve> DegeneratePcurve() const;
};

