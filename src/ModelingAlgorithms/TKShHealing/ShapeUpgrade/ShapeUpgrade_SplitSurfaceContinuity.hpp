#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <ShapeUpgrade_SplitSurface.hpp>

class ShapeUpgrade_SplitSurfaceContinuity : public ShapeUpgrade_SplitSurface
{

public:
  Standard_EXPORT ShapeUpgrade_SplitSurfaceContinuity();

  Standard_EXPORT void SetCriterion(const GeomAbs_Shape Criterion);

  Standard_EXPORT void SetTolerance(const double Tol);

  Standard_EXPORT void Compute(const bool Segment) override;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_SplitSurfaceContinuity, ShapeUpgrade_SplitSurface)

private:
  GeomAbs_Shape myCriterion;
  double        myTolerance;
  int           myCont;
};
