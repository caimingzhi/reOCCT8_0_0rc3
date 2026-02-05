#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <Intf_Polygon2d.hpp>
class Standard_OutOfRange;
class Adaptor2d_Curve2d;
class Geom2dInt_Geom2dCurveTool;
class IntRes2d_Domain;
class Bnd_Box2d;
class gp_Pnt2d;

class Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter : public Intf_Polygon2d
{
public:
  DEFINE_STANDARD_ALLOC

  //! Compute a polygon on the domain of the curve.
  Standard_EXPORT Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter(const Adaptor2d_Curve2d& Curve,
                                                                     const int                NbPnt,
                                                                     const IntRes2d_Domain& Domain,
                                                                     const double           Tol);

  //! The current polygon is modified if most
  //! of the points of the polygon are
  //! outside the box <OtherBox>. In this
  //! situation, bounds are computed to build
  //! a polygon inside or near the OtherBox.
  Standard_EXPORT void ComputeWithBox(const Adaptor2d_Curve2d& Curve, const Bnd_Box2d& OtherBox);

  double DeflectionOverEstimation() const override;

  void SetDeflectionOverEstimation(const double x);

  void Closed(const bool clos);

  //! Returns True if the polyline is closed.
  bool Closed() const override { return ClosedPolygon; }

  //! Give the number of Segments in the polyline.
  int NbSegments() const override;

  //! Returns the points of the segment <Index> in the Polygon.
  Standard_EXPORT void Segment(const int theIndex,
                               gp_Pnt2d& theBegin,
                               gp_Pnt2d& theEnd) const override;

  //! Returns the parameter (On the curve)
  //! of the first point of the Polygon
  double InfParameter() const;

  //! Returns the parameter (On the curve)
  //! of the last point of the Polygon
  double SupParameter() const;

  Standard_EXPORT bool AutoIntersectionIsPossible() const;

  //! Give an approximation of the parameter on the curve
  //! according to the discretization of the Curve.
  Standard_EXPORT double ApproxParamOnCurve(const int Index, const double ParamOnLine) const;

  int CalculRegion(const double x,
                   const double y,
                   const double x1,
                   const double x2,
                   const double y1,
                   const double y2) const;

  Standard_EXPORT void Dump() const;

private:
  double                       TheDeflection;
  int                          NbPntIn;
  int                          TheMaxNbPoints;
  NCollection_Array1<gp_Pnt2d> ThePnts;
  NCollection_Array1<double>   TheParams;
  NCollection_Array1<int>      TheIndex;
  bool                         ClosedPolygon;
  double                       Binf;
  double                       Bsup;
};

#define TheCurve Adaptor2d_Curve2d
#define TheCurve_hxx <Adaptor2d_Curve2d.hpp>
#define TheCurveTool Geom2dInt_Geom2dCurveTool
#define TheCurveTool_hxx <Geom2dInt_Geom2dCurveTool.hpp>
#define IntCurve_Polygon2dGen Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter
#define IntCurve_Polygon2dGen_hxx <Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter.hpp>

#include <IntCurve_Polygon2dGen_1.hpp>

#undef TheCurve
#undef TheCurve_hxx
#undef TheCurveTool
#undef TheCurveTool_hxx
#undef IntCurve_Polygon2dGen
#undef IntCurve_Polygon2dGen_hxx
