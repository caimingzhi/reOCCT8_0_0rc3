#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <ShapeUpgrade_ShapeDivide.hpp>
class TopoDS_Shape;

//! Splits all surfaces of revolution, cylindrical, toroidal,
//! conical, spherical surfaces in the given shape so that
//! each resulting segment covers not more than defined number
//! of degrees (to segments less than 90).
class ShapeUpgrade_ShapeDivideAngle : public ShapeUpgrade_ShapeDivide
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  Standard_EXPORT ShapeUpgrade_ShapeDivideAngle(const double MaxAngle);

  //! Initialize by a Shape.
  Standard_EXPORT ShapeUpgrade_ShapeDivideAngle(const double MaxAngle, const TopoDS_Shape& S);

  //! Resets tool for splitting face with given angle
  Standard_EXPORT void InitTool(const double MaxAngle);

  //! Set maximal angle (calls InitTool)
  Standard_EXPORT void SetMaxAngle(const double MaxAngle);

  //! Returns maximal angle
  Standard_EXPORT double MaxAngle() const;
};
