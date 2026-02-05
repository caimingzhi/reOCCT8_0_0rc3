#include <Approx_SweepFunction.hpp>
#include <BRepBlend_AppSurface.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>

BRepBlend_AppSurface::BRepBlend_AppSurface(const occ::handle<Approx_SweepFunction>& Func,
                                           const double                             First,
                                           const double                             Last,
                                           const double                             Tol3d,
                                           const double                             Tol2d,
                                           const double                             TolAngular,
                                           const GeomAbs_Shape                      Continuity,
                                           const int                                Degmax,
                                           const int                                Segmax)
    : approx(Func)
{
  int           Nb2d = Func->Nb2dCurves();
  int           NbPolSect, NbKnotSect, udeg;
  GeomAbs_Shape continuity = Continuity;

  // (1) Verification de la possibilite de derivation
  if (continuity != GeomAbs_C0)
  {
    if (Nb2d == 0)
      Nb2d = 1;
    Func->SectionShape(NbPolSect, NbKnotSect, udeg);
    NCollection_Array1<double>   W(1, NbPolSect);
    NCollection_Array1<gp_Pnt>   P(1, NbPolSect);
    NCollection_Array1<gp_Pnt2d> P2d(1, Nb2d);
    NCollection_Array1<gp_Vec>   V(1, NbPolSect);
    NCollection_Array1<gp_Vec2d> V2d(1, Nb2d);
    bool                         Ok;
    if (continuity == GeomAbs_C2)
    {
      Ok = Func->D2(First, First, Last, P, V, V, P2d, V2d, V2d, W, W, W);
      if (!Ok)
      {
        continuity = GeomAbs_C1;
      }
    }
    if (continuity == GeomAbs_C1)
    {
      Ok = (Func->D1(First, First, Last, P, V, P2d, V2d, W, W));
      if (!Ok)
      {
        continuity = GeomAbs_C0;
      }
    }
  }

  // (2) Approximation
  approx.Perform(First, Last, Tol3d, Tol3d, Tol2d, TolAngular, continuity, Degmax, Segmax);
}

void BRepBlend_AppSurface::SurfShape(int& UDegree,
                                     int& VDegree,
                                     int& NbUPoles,
                                     int& NbVPoles,
                                     int& NbUKnots,
                                     int& NbVKnots) const
{
  approx.SurfShape(UDegree, VDegree, NbUPoles, NbVPoles, NbUKnots, NbVKnots);
}

void BRepBlend_AppSurface::Surface(NCollection_Array2<gp_Pnt>& TPoles,
                                   NCollection_Array2<double>& TWeights,
                                   NCollection_Array1<double>& TUKnots,
                                   NCollection_Array1<double>& TVKnots,
                                   NCollection_Array1<int>&    TUMults,
                                   NCollection_Array1<int>&    TVMults) const

{
  approx.Surface(TPoles, TWeights, TUKnots, TVKnots, TUMults, TVMults);
}

double BRepBlend_AppSurface::MaxErrorOnSurf() const
{
  return approx.MaxErrorOnSurf();
}

void BRepBlend_AppSurface::Curves2dShape(int& Degree, int& NbPoles, int& NbKnots) const
{
  approx.Curves2dShape(Degree, NbPoles, NbKnots);
}

void BRepBlend_AppSurface::Curve2d(const int                     Index,
                                   NCollection_Array1<gp_Pnt2d>& TPoles,
                                   NCollection_Array1<double>&   TKnots,
                                   NCollection_Array1<int>&      TMults) const
{
  approx.Curve2d(Index, TPoles, TKnots, TMults);
}

double BRepBlend_AppSurface::Max2dError(const int Index) const
{
  return approx.Max2dError(Index);
}

double BRepBlend_AppSurface::TolCurveOnSurf(const int Index) const
{
  return approx.TolCurveOnSurf(Index);
}

void BRepBlend_AppSurface::TolReached(double& Tol3d, double& Tol2d) const
{
  Tol3d = approx.MaxErrorOnSurf();
  Tol2d = 0;
  for (int ii = 1; ii <= approx.NbCurves2d(); ii++)
  {
    Tol2d = std::max(Tol2d, approx.Max2dError(ii));
  }
}

void BRepBlend_AppSurface::Dump(Standard_OStream& o) const
{
  approx.Dump(o);
}
