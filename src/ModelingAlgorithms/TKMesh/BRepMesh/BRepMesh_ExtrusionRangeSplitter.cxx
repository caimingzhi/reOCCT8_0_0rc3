#include <BRepMesh_ExtrusionRangeSplitter.hpp>

int BRepMesh_ExtrusionRangeSplitter::getUndefinedIntervalNb(
  const occ::handle<Adaptor3d_Surface>& theSurface,
  const bool,
  const GeomAbs_Shape theContinuity) const
{

  const occ::handle<Adaptor3d_Curve> aCurve       = theSurface->BasisCurve();
  int                                aIntervalsNb = aCurve->NbIntervals(theContinuity);
  if (aIntervalsNb == 1)
  {
    const GeomAbs_CurveType aCurveType = aCurve->GetType();
    const bool              isBSplineCurve =
      aCurveType == GeomAbs_BezierCurve || aCurveType == GeomAbs_BSplineCurve;

    if (isBSplineCurve)
    {
      aIntervalsNb = aCurve->NbPoles() - 1;
    }
  }

  return aIntervalsNb;
}
