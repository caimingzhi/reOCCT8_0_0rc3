#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <BSplCLib_Cache.hpp>
#include <Geom2d_Curve.hpp>
#include <GeomAbs_CurveType.hpp>
#include <GeomAbs_Shape.hpp>
#include <gp_Pnt2d.hpp>
#include <Precision.hpp>
#include <Standard_NullObject.hpp>
#include <NCollection_Array1.hpp>

#include <variant>

class gp_Vec2d;
class gp_Lin2d;
class gp_Circ2d;
class gp_Elips2d;
class gp_Hypr2d;
class gp_Parab2d;
class Geom2d_BezierCurve;
class Geom2d_BSplineCurve;

class Geom2dAdaptor_Curve : public Adaptor2d_Curve2d
{
  DEFINE_STANDARD_RTTIEXT(Geom2dAdaptor_Curve, Adaptor2d_Curve2d)
public:
  struct OffsetData
  {
    occ::handle<Geom2dAdaptor_Curve> BasisAdaptor;
    double                           Offset = 0.0;
  };

  struct BezierData
  {
    mutable occ::handle<BSplCLib_Cache> Cache;
  };

  struct BSplineData
  {
    occ::handle<Geom2d_BSplineCurve>    Curve;
    mutable occ::handle<BSplCLib_Cache> Cache;
  };

  using CurveDataVariant = std::variant<std::monostate, OffsetData, BezierData, BSplineData>;

public:
  Standard_EXPORT Geom2dAdaptor_Curve();

  Standard_EXPORT Geom2dAdaptor_Curve(const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT Geom2dAdaptor_Curve(const occ::handle<Geom2d_Curve>& C,
                                      const double                     UFirst,
                                      const double                     ULast);

  Standard_EXPORT occ::handle<Adaptor2d_Curve2d> ShallowCopy() const override;

  Standard_EXPORT void Reset();

  void Load(const occ::handle<Geom2d_Curve>& theCurve)
  {
    if (theCurve.IsNull())
    {
      throw Standard_NullObject();
    }
    load(theCurve, theCurve->FirstParameter(), theCurve->LastParameter());
  }

  void Load(const occ::handle<Geom2d_Curve>& theCurve,
            const double                     theUFirst,
            const double                     theULast)
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

  const occ::handle<Geom2d_Curve>& Curve() const { return myCurve; }

  double FirstParameter() const override { return myFirst; }

  double LastParameter() const override { return myLast; }

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT occ::handle<Adaptor2d_Curve2d> Trim(const double First,
                                                      const double Last,
                                                      const double Tol) const override;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT double Period() const override;

  Standard_EXPORT gp_Pnt2d Value(const double U) const override;

  Standard_EXPORT void D0(const double U, gp_Pnt2d& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt2d& P, gp_Vec2d& V) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt2d&    P,
                          gp_Vec2d&    V1,
                          gp_Vec2d&    V2,
                          gp_Vec2d&    V3) const override;

  Standard_EXPORT gp_Vec2d DN(const double U, const int N) const override;

  Standard_EXPORT double Resolution(const double Ruv) const override;

  GeomAbs_CurveType GetType() const override { return myTypeCurve; }

  Standard_EXPORT gp_Lin2d Line() const override;

  Standard_EXPORT gp_Circ2d Circle() const override;

  Standard_EXPORT gp_Elips2d Ellipse() const override;

  Standard_EXPORT gp_Hypr2d Hyperbola() const override;

  Standard_EXPORT gp_Parab2d Parabola() const override;

  Standard_EXPORT int Degree() const override;

  Standard_EXPORT bool IsRational() const override;

  Standard_EXPORT int NbPoles() const override;

  Standard_EXPORT int NbKnots() const override;

  Standard_EXPORT int NbSamples() const override;

  Standard_EXPORT occ::handle<Geom2d_BezierCurve> Bezier() const override;

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> BSpline() const override;

private:
  Standard_EXPORT GeomAbs_Shape LocalContinuity(const double U1, const double U2) const;

  Standard_EXPORT void load(const occ::handle<Geom2d_Curve>& C,
                            const double                     UFirst,
                            const double                     ULast);

  bool IsBoundary(const double theU, int& theSpanStart, int& theSpanFinish) const;

  void RebuildCache(const double theParameter) const;

protected:
  occ::handle<Geom2d_Curve> myCurve;
  GeomAbs_CurveType         myTypeCurve;
  double                    myFirst;
  double                    myLast;
  CurveDataVariant          myCurveData;
};
