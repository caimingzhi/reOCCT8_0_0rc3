#pragma once


#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Curve.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <GCPnts_DistFunction.hpp>
#include <GCPnts_DistFunction2d.hpp>

//! Auxiliary tool to resolve 2D/3D curve classes.
template <class TheCurve>
struct GCPnts_TCurveTypes
{
};

//! Auxiliary tool to resolve 3D curve classes.
template <>
struct GCPnts_TCurveTypes<Adaptor3d_Curve>
{
  typedef gp_Pnt                Point;
  typedef Geom_BezierCurve      BezierCurve;
  typedef Geom_BSplineCurve     BSplineCurve;
  typedef GCPnts_DistFunction   DistFunction;
  typedef GCPnts_DistFunctionMV DistFunctionMV;
};

//! Auxiliary tool to resolve 2D curve classes.
template <>
struct GCPnts_TCurveTypes<Adaptor2d_Curve2d>
{
  typedef gp_Pnt2d                Point;
  typedef Geom2d_BezierCurve      BezierCurve;
  typedef Geom2d_BSplineCurve     BSplineCurve;
  typedef GCPnts_DistFunction2d   DistFunction;
  typedef GCPnts_DistFunction2dMV DistFunctionMV;
};

