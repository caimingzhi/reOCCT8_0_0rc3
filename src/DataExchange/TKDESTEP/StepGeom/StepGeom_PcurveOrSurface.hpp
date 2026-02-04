#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepGeom_Pcurve;
class StepGeom_Surface;

class StepGeom_PcurveOrSurface : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a PcurveOrSurface SelectType
  Standard_EXPORT StepGeom_PcurveOrSurface();

  //! Recognizes a PcurveOrSurface Kind Entity that is :
  //! 1 -> Pcurve
  //! 2 -> Surface
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a Pcurve (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_Pcurve> Pcurve() const;

  //! returns Value as a Surface (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_Surface> Surface() const;
};

