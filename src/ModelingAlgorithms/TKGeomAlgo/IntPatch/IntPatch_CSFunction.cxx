

#include <Adaptor3d_HSurfaceTool.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <IntPatch_CSFunction.hpp>
#include <IntPatch_HCurve2dTool.hpp>
#include <math_Matrix.hpp>

#ifndef OCCT_DEBUG
  #define No_Standard_RangeError
  #define No_Standard_OutOfRange
#endif

#define SURFACE1 (*((occ::handle<Adaptor3d_Surface>*)(surface1)))
#define SURFACE2 (*((occ::handle<Adaptor3d_Surface>*)(surface2)))
#define CURVE (*((occ::handle<Adaptor2d_Curve2d>*)(curve)))

IntPatch_CSFunction::IntPatch_CSFunction(const occ::handle<Adaptor3d_Surface>& S1,
                                         const occ::handle<Adaptor2d_Curve2d>& C,
                                         const occ::handle<Adaptor3d_Surface>& S2)
{
  surface1 = (void*)(&S1);
  surface2 = (void*)(&S2);
  curve    = (void*)(&C);
  f        = 0.;
}

int IntPatch_CSFunction::NbVariables() const
{
  return 3;
}

int IntPatch_CSFunction::NbEquations() const
{
  return 3;
}

bool IntPatch_CSFunction::Value(const math_Vector& X, math_Vector& F)
{

  gp_Pnt   Psurf(Adaptor3d_HSurfaceTool::Value(SURFACE1, X(1), X(2)));
  gp_Pnt2d p2d(IntPatch_HCurve2dTool::Value(CURVE, X(3)));
  gp_Pnt   Pcurv(Adaptor3d_HSurfaceTool::Value(SURFACE2, p2d.X(), p2d.Y()));

  F(1) = Psurf.X() - Pcurv.X();
  F(2) = Psurf.Y() - Pcurv.Y();
  F(3) = Psurf.Z() - Pcurv.Z();
  f    = F(1) * F(1) + F(2) * F(2) + F(3) * F(3);
  p    = gp_Pnt((Psurf.XYZ() + Pcurv.XYZ()) / 2.);
  return true;
}

bool IntPatch_CSFunction::Derivatives(const math_Vector& X, math_Matrix& D)
{
  gp_Pnt   Psurf, Pcurv;
  gp_Vec   D1u, D1v, D1w;
  gp_Pnt2d p2d;
  gp_Vec2d d2d;
  gp_Vec   d1u, d1v;

  Adaptor3d_HSurfaceTool::D1(SURFACE1, X(1), X(2), Psurf, D1u, D1v);
  IntPatch_HCurve2dTool::D1(CURVE, X(3), p2d, d2d);
  Adaptor3d_HSurfaceTool::D1(SURFACE2, p2d.X(), p2d.Y(), Pcurv, d1u, d1v);
  D1w.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);

  D(1, 1) = D1u.X();
  D(1, 2) = D1v.X();
  D(1, 3) = -D1w.X();
  D(2, 1) = D1u.Y();
  D(2, 2) = D1v.Y();
  D(2, 3) = -D1w.Y();
  D(3, 1) = D1u.Z();
  D(3, 2) = D1v.Z();
  D(3, 3) = -D1w.Z();
  return true;
}

bool IntPatch_CSFunction::Values(const math_Vector& X, math_Vector& F, math_Matrix& D)
{
  gp_Pnt Psurf, Pcurv;
  gp_Vec D1u, D1v, D1w;

  gp_Pnt2d p2d;
  gp_Vec2d d2d;
  gp_Vec   d1u, d1v;

  Adaptor3d_HSurfaceTool::D1(SURFACE1, X(1), X(2), Psurf, D1u, D1v);
  IntPatch_HCurve2dTool::D1(CURVE, X(3), p2d, d2d);
  Adaptor3d_HSurfaceTool::D1(SURFACE2, p2d.X(), p2d.Y(), Pcurv, d1u, d1v);
  D1w.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);

  D(1, 1) = D1u.X();
  D(1, 2) = D1v.X();
  D(1, 3) = -D1w.X();
  D(2, 1) = D1u.Y();
  D(2, 2) = D1v.Y();
  D(2, 3) = -D1w.Y();
  D(3, 1) = D1u.Z();
  D(3, 2) = D1v.Z();
  D(3, 3) = -D1w.Z();
  F(1)    = Psurf.X() - Pcurv.X();
  F(2)    = Psurf.Y() - Pcurv.Y();
  F(3)    = Psurf.Z() - Pcurv.Z();
  f       = F(1) * F(1) + F(2) * F(2) + F(3) * F(3);
  p       = gp_Pnt((Psurf.XYZ() + Pcurv.XYZ()) / 2.);
  return true;
}

const gp_Pnt& IntPatch_CSFunction::Point() const
{
  return p;
}

double IntPatch_CSFunction::Root() const
{
  return f;
}

const occ::handle<Adaptor3d_Surface>& IntPatch_CSFunction::AuxillarSurface() const
{
  return SURFACE1;
}

const occ::handle<Adaptor2d_Curve2d>& IntPatch_CSFunction::AuxillarCurve() const
{
  return CURVE;
}

#undef SURFACE1
#undef SURFACE2
#undef CURVE
