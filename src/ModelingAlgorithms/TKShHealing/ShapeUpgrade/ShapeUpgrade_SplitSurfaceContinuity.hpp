#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <ShapeUpgrade_SplitSurface.hpp>

//! Splits a Surface with a continuity criterion.
//! At the present moment C1 criterion is used only.
//! This tool works with tolerance. If C0 surface can be corrected
//! at a knot with given tolerance then the surface is corrected,
//! otherwise it is spltted at that knot.
class ShapeUpgrade_SplitSurfaceContinuity : public ShapeUpgrade_SplitSurface
{

public:
  //! Empty constructor.
  Standard_EXPORT ShapeUpgrade_SplitSurfaceContinuity();

  //! Sets criterion for splitting.
  Standard_EXPORT void SetCriterion(const GeomAbs_Shape Criterion);

  //! Sets tolerance.
  Standard_EXPORT void SetTolerance(const double Tol);

  Standard_EXPORT void Compute(const bool Segment) override;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_SplitSurfaceContinuity, ShapeUpgrade_SplitSurface)

private:
  GeomAbs_Shape myCriterion;
  double        myTolerance;
  int           myCont;
};

