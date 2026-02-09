#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomAbs_Shape.hpp>
#include <ShapeUpgrade_ShapeDivide.hpp>
class TopoDS_Shape;
class ShapeUpgrade_FaceDivide;

class ShapeUpgrade_ShapeDivideContinuity : public ShapeUpgrade_ShapeDivide
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeUpgrade_ShapeDivideContinuity();

  Standard_EXPORT ShapeUpgrade_ShapeDivideContinuity(const TopoDS_Shape& S);

  Standard_EXPORT void SetTolerance(const double Tol);

  Standard_EXPORT void SetTolerance2d(const double Tol);

  Standard_EXPORT void SetBoundaryCriterion(const GeomAbs_Shape Criterion = GeomAbs_C1);

  Standard_EXPORT void SetPCurveCriterion(const GeomAbs_Shape Criterion = GeomAbs_C1);

  Standard_EXPORT void SetSurfaceCriterion(const GeomAbs_Shape Criterion = GeomAbs_C1);

protected:
  Standard_EXPORT occ::handle<ShapeUpgrade_FaceDivide> GetSplitFaceTool() const override;

private:
  GeomAbs_Shape myCurve3dCriterion;
  GeomAbs_Shape myCurve2dCriterion;
  GeomAbs_Shape mySurfaceCriterion;
  double        myTolerance3d;
  double        myTolerance2d;
};
