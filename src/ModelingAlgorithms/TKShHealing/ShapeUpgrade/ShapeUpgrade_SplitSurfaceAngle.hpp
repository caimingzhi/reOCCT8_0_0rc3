#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <ShapeUpgrade_SplitSurface.hpp>

//! Splits a surfaces of revolution, cylindrical, toroidal,
//! conical, spherical so that each resulting segment covers
//! not more than defined number of degrees.
class ShapeUpgrade_SplitSurfaceAngle : public ShapeUpgrade_SplitSurface
{

public:
  //! Empty constructor.
  Standard_EXPORT ShapeUpgrade_SplitSurfaceAngle(const double MaxAngle);

  //! Set maximal angle
  Standard_EXPORT void SetMaxAngle(const double MaxAngle);

  //! Returns maximal angle
  Standard_EXPORT double MaxAngle() const;

  //! Performs splitting of the supporting surface(s).
  //! First defines splitting values, then calls inherited method.
  Standard_EXPORT void Compute(const bool Segment) override;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_SplitSurfaceAngle, ShapeUpgrade_SplitSurface)

private:
  double myMaxAngle;
};
