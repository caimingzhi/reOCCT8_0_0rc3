#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <ShapeUpgrade_SplitCurve2d.hpp>

class ShapeUpgrade_SplitCurve2dContinuity : public ShapeUpgrade_SplitCurve2d
{

public:
  Standard_EXPORT ShapeUpgrade_SplitCurve2dContinuity();

  Standard_EXPORT void SetCriterion(const GeomAbs_Shape Criterion);

  Standard_EXPORT void SetTolerance(const double Tol);

  Standard_EXPORT void Compute() override;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_SplitCurve2dContinuity, ShapeUpgrade_SplitCurve2d)

private:
  GeomAbs_Shape myCriterion;
  int           myCont;
  double        myTolerance;
};
