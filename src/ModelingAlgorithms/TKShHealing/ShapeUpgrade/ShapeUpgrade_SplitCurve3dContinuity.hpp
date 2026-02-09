#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <ShapeUpgrade_SplitCurve3d.hpp>
class Geom_Curve;

class ShapeUpgrade_SplitCurve3dContinuity : public ShapeUpgrade_SplitCurve3d
{

public:
  Standard_EXPORT ShapeUpgrade_SplitCurve3dContinuity();

  Standard_EXPORT void SetCriterion(const GeomAbs_Shape Criterion);

  Standard_EXPORT void SetTolerance(const double Tol);

  Standard_EXPORT void Compute() override;

  Standard_EXPORT const occ::handle<Geom_Curve>& GetCurve() const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_SplitCurve3dContinuity, ShapeUpgrade_SplitCurve3d)

private:
  GeomAbs_Shape myCriterion;
  double        myTolerance;
  int           myCont;
};
