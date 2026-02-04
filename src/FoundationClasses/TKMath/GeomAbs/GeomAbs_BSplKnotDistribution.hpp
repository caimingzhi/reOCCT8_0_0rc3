#pragma once


//! This enumeration is used in the classes BSplineCurve and
//! BSplineSurface to describe the repartition of set of knots.
//! (comments in classes BSplineCurve and BSplineSurface)
enum GeomAbs_BSplKnotDistribution
{
  GeomAbs_NonUniform,
  GeomAbs_Uniform,
  GeomAbs_QuasiUniform,
  GeomAbs_PiecewiseBezier
};

