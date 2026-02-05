#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array1.hpp>
class BRepAdaptor_Curve;
class gp_Pnt;
class gp_Vec;

//! Provides the required methods to instantiate
//! CGProps from GProp with a Curve from BRepAdaptor.
class BRepGProp_EdgeTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns the parametric value of the start point of
  //! the curve. The curve is oriented from the start point
  //! to the end point.
  Standard_EXPORT static double FirstParameter(const BRepAdaptor_Curve& C);

  //! Returns the parametric value of the end point of
  //! the curve. The curve is oriented from the start point
  //! to the end point.
  Standard_EXPORT static double LastParameter(const BRepAdaptor_Curve& C);

  //! Returns the number of Gauss points required to do
  //! the integration with a good accuracy using the
  //! Gauss method. For a polynomial curve of degree n
  //! the maxima of accuracy is obtained with an order
  //! of integration equal to 2*n-1.
  Standard_EXPORT static int IntegrationOrder(const BRepAdaptor_Curve& C);

  //! Returns the point of parameter U on the loaded curve.
  Standard_EXPORT static gp_Pnt Value(const BRepAdaptor_Curve& C, const double U);

  //! Returns the point of parameter U and the first derivative
  //! at this point.
  Standard_EXPORT static void D1(const BRepAdaptor_Curve& C, const double U, gp_Pnt& P, gp_Vec& V1);

  //! Returns the number of intervals for continuity
  //! <S>. May be one if Continuity(me) >= <S>
  Standard_EXPORT static int NbIntervals(const BRepAdaptor_Curve& C, const GeomAbs_Shape S);

  //! Stores in <T> the parameters bounding the intervals
  //! of continuity <S>.
  //!
  //! The array must provide enough room to accommodate
  //! for the parameters. i.e. T.Length() > NbIntervals()
  Standard_EXPORT static void Intervals(const BRepAdaptor_Curve&    C,
                                        NCollection_Array1<double>& T,
                                        const GeomAbs_Shape         S);
};
