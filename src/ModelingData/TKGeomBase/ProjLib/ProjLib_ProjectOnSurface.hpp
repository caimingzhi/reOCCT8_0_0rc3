#pragma once

#include <Adaptor3d_Surface.hpp>

class Geom_BSplineCurve;

class ProjLib_ProjectOnSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ProjLib_ProjectOnSurface();

  Standard_EXPORT ProjLib_ProjectOnSurface(const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT virtual ~ProjLib_ProjectOnSurface();

  Standard_EXPORT void Load(const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT void Load(const occ::handle<Adaptor3d_Curve>& C, const double Tolerance);

  bool IsDone() const { return myIsDone; }

  Standard_EXPORT occ::handle<Geom_BSplineCurve> BSpline() const;

private:
  occ::handle<Adaptor3d_Curve>   myCurve;
  occ::handle<Adaptor3d_Surface> mySurface;
  double                         myTolerance;
  bool                           myIsDone;
  occ::handle<Geom_BSplineCurve> myResult;
};
