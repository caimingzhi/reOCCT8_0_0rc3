#pragma once

#include <Adaptor3d_Surface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <math_Vector.hpp>

class math_Matrix;

class BlendFunc_Corde
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BlendFunc_Corde(const occ::handle<Adaptor3d_Surface>& S,
                                  const occ::handle<Adaptor3d_Curve>&   CGuide);

  Standard_EXPORT void SetParam(const double Param);

  Standard_EXPORT void SetDist(const double Dist);

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F);

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D);

  Standard_EXPORT const gp_Pnt& PointOnS() const;

  Standard_EXPORT const gp_Pnt& PointOnGuide() const;

  Standard_EXPORT const gp_Vec& NPlan() const;

  Standard_EXPORT bool IsTangencyPoint() const;

  Standard_EXPORT const gp_Vec& TangentOnS() const;

  Standard_EXPORT const gp_Vec2d& Tangent2dOnS() const;

  Standard_EXPORT void DerFguide(const math_Vector& Sol, gp_Vec2d& DerF);

  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol);

private:
  occ::handle<Adaptor3d_Surface> surf;
  occ::handle<Adaptor3d_Curve>   guide;
  gp_Pnt                         pts;
  gp_Pnt2d                       pt2d;
  double                         dis;
  double                         normtg;
  double                         theD;
  gp_Pnt                         ptgui;
  gp_Vec                         nplan;
  gp_Vec                         d1gui;
  gp_Vec                         d2gui;
  gp_Vec                         tgs;
  gp_Vec2d                       tg2d;
  bool                           istangent;
};
