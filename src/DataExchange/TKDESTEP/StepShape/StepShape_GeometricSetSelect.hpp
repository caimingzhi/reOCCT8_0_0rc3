#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepGeom_Point;
class StepGeom_Curve;
class StepGeom_Surface;

class StepShape_GeometricSetSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a GeometricSetSelect SelectType
  Standard_EXPORT StepShape_GeometricSetSelect();

  //! Recognizes a GeometricSetSelect Kind Entity that is :
  //! 1 -> Point
  //! 2 -> Curve
  //! 3 -> Surface
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a Point (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_Point> Point() const;

  //! returns Value as a Curve (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_Curve> Curve() const;

  //! returns Value as a Surface (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_Surface> Surface() const;
};

