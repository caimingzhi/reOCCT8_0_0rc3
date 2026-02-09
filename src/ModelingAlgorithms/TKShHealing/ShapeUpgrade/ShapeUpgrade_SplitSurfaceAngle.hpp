#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <ShapeUpgrade_SplitSurface.hpp>

class ShapeUpgrade_SplitSurfaceAngle : public ShapeUpgrade_SplitSurface
{

public:
  Standard_EXPORT ShapeUpgrade_SplitSurfaceAngle(const double MaxAngle);

  Standard_EXPORT void SetMaxAngle(const double MaxAngle);

  Standard_EXPORT double MaxAngle() const;

  Standard_EXPORT void Compute(const bool Segment) override;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_SplitSurfaceAngle, ShapeUpgrade_SplitSurface)

private:
  double myMaxAngle;
};
