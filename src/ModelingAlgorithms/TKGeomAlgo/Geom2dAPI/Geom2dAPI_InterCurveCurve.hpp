#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2dInt_GInter.hpp>
#include <Standard_Integer.hpp>
class Geom2d_Curve;
class gp_Pnt2d;

class Geom2dAPI_InterCurveCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dAPI_InterCurveCurve();

  Standard_EXPORT Geom2dAPI_InterCurveCurve(const occ::handle<Geom2d_Curve>& C1,
                                            const occ::handle<Geom2d_Curve>& C2,
                                            const double                     Tol = 1.0e-6);

  Standard_EXPORT Geom2dAPI_InterCurveCurve(const occ::handle<Geom2d_Curve>& C1,
                                            const double                     Tol = 1.0e-6);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C1,
                            const occ::handle<Geom2d_Curve>& C2,
                            const double                     Tol = 1.0e-6);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C1, const double Tol = 1.0e-6);

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT gp_Pnt2d Point(const int Index) const;

  Standard_EXPORT int NbSegments() const;

  Standard_EXPORT void Segment(const int                  Index,
                               occ::handle<Geom2d_Curve>& Curve1,
                               occ::handle<Geom2d_Curve>& Curve2) const;

  const Geom2dInt_GInter& Intersector() const;

private:
  bool                      myIsDone;
  occ::handle<Geom2d_Curve> myCurve1;
  occ::handle<Geom2d_Curve> myCurve2;
  Geom2dInt_GInter          myIntersector;
};

inline const Geom2dInt_GInter& Geom2dAPI_InterCurveCurve::Intersector() const
{
  return myIntersector;
}
