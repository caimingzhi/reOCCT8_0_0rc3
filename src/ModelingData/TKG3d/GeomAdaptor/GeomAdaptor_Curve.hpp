#pragma once

#include <Adaptor3d_Curve.hpp>
#include <BSplCLib_Cache.hpp>
#include <Geom_Curve.hpp>
#include <GeomAbs_Shape.hpp>
#include <gp_Dir.hpp>
#include <Precision.hpp>
#include <Standard_NullObject.hpp>
#include <Standard_ConstructionError.hpp>

#include <variant>

class Geom_BSplineCurve;

class GeomAdaptor_Curve : public Adaptor3d_Curve
{
  DEFINE_STANDARD_RTTIEXT(GeomAdaptor_Curve, Adaptor3d_Curve)
public:
  struct OffsetData
  {
    occ::handle<GeomAdaptor_Curve> BasisAdaptor;
    double                         Offset = 0.0;
    gp_Dir                         Direction;
  };

  struct BezierData
  {
    mutable occ::handle<BSplCLib_Cache> Cache;
  };

  struct BSplineData
  {
    occ::handle<Geom_BSplineCurve>      Curve;
    mutable occ::handle<BSplCLib_Cache> Cache;
  };

  using CurveDataVariant = std::variant<std::monostate, OffsetData, BezierData, BSplineData>;

public:
  GeomAdaptor_Curve()
      : myTypeCurve(GeomAbs_OtherCurve),
        myFirst(0.0),
        myLast(0.0)
  {
  }

  GeomAdaptor_Curve(const occ::handle<Geom_Curve>& theCurve) { Load(theCurve); }

  GeomAdaptor_Curve(const occ::handle<Geom_Curve>& theCurve,
                    const double                   theUFirst,
                    const double                   theULast)
  {
    Load(theCurve, theUFirst, theULast);
  }

  Standard_EXPORT occ::handle<Adaptor3d_Curve> ShallowCopy() const override;

  Standard_EXPORT void Reset();

  void Load(const occ::handle<Geom_Curve>& theCurve)
  {
    if (theCurve.IsNull())
    {
      throw Standard_NullObject();
    }
    load(theCurve, theCurve->FirstParameter(), theCurve->LastParameter());
  }

  void Load(const occ::handle<Geom_Curve>& theCurve, const double theUFirst, const double theULast)
  {
    if (theCurve.IsNull())
    {
      throw Standard_NullObject();
    }
    if (theUFirst > theULast + Precision::Confusion())
    {
      throw Standard_ConstructionError();
    }
    load(theCurve, theUFirst, theULast);
  }

  const occ::handle<Geom_Curve>& Curve() const { return myCurve; }

  double FirstParameter() const override { return myFirst; }

  double LastParameter() const override { return myLast; }

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT occ::handle<Adaptor3d_Curve> Trim(const double First,
                                                    const double Last,
                                                    const double Tol) const override;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT double Period() const override;

  Standard_EXPORT gp_Pnt Value(const double U) const final;

  Standard_EXPORT void D0(const double U, gp_Pnt& P) const final;

  Standard_EXPORT void D1(const double U, gp_Pnt& P, gp_Vec& V) const final;

  Standard_EXPORT void D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const final;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt&      P,
                          gp_Vec&      V1,
                          gp_Vec&      V2,
                          gp_Vec&      V3) const final;

  Standard_EXPORT gp_Vec DN(const double U, const int N) const final;

  Standard_EXPORT double Resolution(const double R3d) const override;

  GeomAbs_CurveType GetType() const override { return myTypeCurve; }

  Standard_EXPORT gp_Lin Line() const override;

  Standard_EXPORT gp_Circ Circle() const override;

  Standard_EXPORT gp_Elips Ellipse() const override;

  Standard_EXPORT gp_Hypr Hyperbola() const override;

  Standard_EXPORT gp_Parab Parabola() const override;

  Standard_EXPORT int Degree() const override;

  Standard_EXPORT bool IsRational() const override;

  Standard_EXPORT int NbPoles() const override;

  Standard_EXPORT int NbKnots() const override;

  Standard_EXPORT occ::handle<Geom_BezierCurve> Bezier() const override;

  Standard_EXPORT occ::handle<Geom_BSplineCurve> BSpline() const override;

  Standard_EXPORT occ::handle<Geom_OffsetCurve> OffsetCurve() const override;

  friend class GeomAdaptor_Surface;

private:
  Standard_EXPORT GeomAbs_Shape LocalContinuity(const double U1, const double U2) const;

  Standard_EXPORT void load(const occ::handle<Geom_Curve>& C,
                            const double                   UFirst,
                            const double                   ULast);

  bool IsBoundary(const double theU, int& theSpanStart, int& theSpanFinish) const;

  void RebuildCache(const double theParameter) const;

private:
  occ::handle<Geom_Curve> myCurve;
  GeomAbs_CurveType       myTypeCurve;
  double                  myFirst;
  double                  myLast;
  CurveDataVariant        myCurveData;
};
