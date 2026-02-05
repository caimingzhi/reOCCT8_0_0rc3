#pragma once

#include <Adaptor3d_Surface.hpp>

class Geom_BSplineCurve;

//! Project a curve on a surface. The result
//! (a 3D Curve) will be an approximation
class ProjLib_ProjectOnSurface
{
public:
  DEFINE_STANDARD_ALLOC

  //! Create an empty projector.
  Standard_EXPORT ProjLib_ProjectOnSurface();

  //! Create a projector normally to the surface <S>.
  Standard_EXPORT ProjLib_ProjectOnSurface(const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT virtual ~ProjLib_ProjectOnSurface();

  //! Set the Surface to <S>.
  //! To compute the projection, you have to Load the Curve.
  Standard_EXPORT void Load(const occ::handle<Adaptor3d_Surface>& S);

  //! Compute the projection of the curve <C> on the Surface.
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
