#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <gp_Pnt2d.hpp>

class Bisector_PointOnBis
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Bisector_PointOnBis();

  Standard_EXPORT Bisector_PointOnBis(const double    Param1,
                                      const double    Param2,
                                      const double    ParamBis,
                                      const double    Distance,
                                      const gp_Pnt2d& Point);

  Standard_EXPORT void ParamOnC1(const double Param);

  Standard_EXPORT void ParamOnC2(const double Param);

  Standard_EXPORT void ParamOnBis(const double Param);

  Standard_EXPORT void Distance(const double Distance);

  Standard_EXPORT void IsInfinite(const bool Infinite);

  Standard_EXPORT void Point(const gp_Pnt2d& P);

  Standard_EXPORT double ParamOnC1() const;

  Standard_EXPORT double ParamOnC2() const;

  Standard_EXPORT double ParamOnBis() const;

  Standard_EXPORT double Distance() const;

  Standard_EXPORT gp_Pnt2d Point() const;

  Standard_EXPORT bool IsInfinite() const;

  Standard_EXPORT void Dump() const;

private:
  double   param1;
  double   param2;
  double   paramBis;
  double   distance;
  bool     infinite;
  gp_Pnt2d point;
};
