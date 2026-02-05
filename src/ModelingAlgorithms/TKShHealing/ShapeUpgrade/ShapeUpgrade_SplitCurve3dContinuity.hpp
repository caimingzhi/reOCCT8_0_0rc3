#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <ShapeUpgrade_SplitCurve3d.hpp>
class Geom_Curve;

//! Corrects/splits a 2d curve with a continuity criterion.
//! Tolerance is used to correct the curve at a knot that respects
//! geometrically the criterion, in order to reduce the
//! multiplicity of the knot.
class ShapeUpgrade_SplitCurve3dContinuity : public ShapeUpgrade_SplitCurve3d
{

public:
  //! Empty constructor.
  Standard_EXPORT ShapeUpgrade_SplitCurve3dContinuity();

  //! Sets criterion for splitting.
  Standard_EXPORT void SetCriterion(const GeomAbs_Shape Criterion);

  //! Sets tolerance.
  Standard_EXPORT void SetTolerance(const double Tol);

  //! Calculates points for correction/splitting of the curve
  Standard_EXPORT void Compute() override;

  Standard_EXPORT const occ::handle<Geom_Curve>& GetCurve() const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_SplitCurve3dContinuity, ShapeUpgrade_SplitCurve3d)

private:
  GeomAbs_Shape myCriterion;
  double        myTolerance;
  int           myCont;
};
