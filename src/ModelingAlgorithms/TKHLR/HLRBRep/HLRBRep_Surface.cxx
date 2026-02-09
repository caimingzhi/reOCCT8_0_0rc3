#include <gp_Vec.hpp>
#include <GProp_PEquation.hpp>
#include <HLRAlgo_Projector.hpp>
#include <HLRBRep_Surface.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <TopoDS_Face.hpp>

HLRBRep_Surface::HLRBRep_Surface()
    : myType(GeomAbs_OtherSurface),
      myProj(nullptr)
{
}

void HLRBRep_Surface::Surface(const TopoDS_Face& F)
{

  mySurf.Initialize(F, true);
  GeomAbs_SurfaceType typ = HLRBRep_BSurfaceTool::GetType(mySurf);
  switch (typ)
  {

    case GeomAbs_Plane:
    case GeomAbs_Cylinder:
    case GeomAbs_Cone:
    case GeomAbs_Sphere:
    case GeomAbs_Torus:

      myType = typ;
      break;

    case GeomAbs_BezierSurface:
      if (HLRBRep_BSurfaceTool::UDegree(mySurf) == 1 && HLRBRep_BSurfaceTool::VDegree(mySurf) == 1)
      {
        myType = GeomAbs_Plane;
      }
      else
        myType = typ;
      break;

    default:
      myType = GeomAbs_OtherSurface;
      break;
  }
}

bool HLRBRep_Surface::SideRowsOfPoles(const double                tol,
                                      const int                   nbuPoles,
                                      const int                   nbvPoles,
                                      NCollection_Array2<gp_Pnt>& Pnt) const
{
  int            iu, iv;
  double         x0, y0, x, y, z;
  bool           result;
  double         tole = (double)tol;
  const gp_Trsf& T    = myProj->Transformation();

  for (iu = 1; iu <= nbuPoles; iu++)
  {

    for (iv = 1; iv <= nbvPoles; iv++)
      Pnt(iu, iv).Transform(T);
  }
  result = true;

  for (iu = 1; iu <= nbuPoles && result; iu++)
  {
    Pnt(iu, 1).Coord(x0, y0, z);

    for (iv = 2; iv <= nbvPoles && result; iv++)
    {
      Pnt(iu, iv).Coord(x, y, z);
      result = std::abs(x - x0) < tole && std::abs(y - y0) < tole;
    }
  }
  if (result)
    return result;
  result = true;

  for (iv = 1; iv <= nbvPoles && result; iv++)
  {
    Pnt(1, iv).Coord(x0, y0, z);

    for (iu = 2; iu <= nbuPoles && result; iu++)
    {
      Pnt(iu, iv).Coord(x, y, z);
      result = std::abs(x - x0) < tole && std::abs(y - y0) < tole;
    }
  }
  if (result)
    return result;

  NCollection_Array1<gp_Pnt> p(1, nbuPoles * nbvPoles);
  int                        i = 0;

  for (iu = 1; iu <= nbuPoles; iu++)
  {

    for (iv = 1; iv <= nbvPoles; iv++)
    {
      i++;
      p(i) = Pnt(iu, iv);
    }
  }

  GProp_PEquation Pl(p, (double)tol);
  if (Pl.IsPlanar())
    result = std::abs(Pl.Plane().Axis().Direction().Z()) < 0.0001;

  return result;
}

bool HLRBRep_Surface::IsSide(const double tolF, const double toler) const
{
  gp_Pnt Pt;
  gp_Vec D;
  double r;

  if (myType == GeomAbs_Plane)
  {
    gp_Pln Pl = Plane();
    gp_Ax1 A  = Pl.Axis();
    Pt        = A.Location();
    D         = A.Direction();
    Pt.Transform(myProj->Transformation());
    D.Transform(myProj->Transformation());
    if (myProj->Perspective())
    {
      r = D.Z() * myProj->Focus() - (D.X() * Pt.X() + D.Y() * Pt.Y() + D.Z() * Pt.Z());
    }
    else
      r = D.Z();
    return std::abs(r) < toler;
  }
  else if (myType == GeomAbs_Cylinder)
  {
    if (myProj->Perspective())
      return false;
    gp_Cylinder Cyl = HLRBRep_BSurfaceTool::Cylinder(mySurf);
    gp_Ax1      A   = Cyl.Axis();
    D               = A.Direction();
    D.Transform(myProj->Transformation());
    r = std::sqrt(D.X() * D.X() + D.Y() * D.Y());
    return r < toler;
  }
  else if (myType == GeomAbs_Cone)
  {
    if (!myProj->Perspective())
      return false;
    gp_Cone Con = HLRBRep_BSurfaceTool::Cone(mySurf);
    Pt          = Con.Apex();
    Pt.Transform(myProj->Transformation());
    double tol = 0.001;
    return Pt.IsEqual(gp_Pnt(0, 0, myProj->Focus()), tol);
  }
  else if (myType == GeomAbs_BezierSurface)
  {
    if (myProj->Perspective())
      return false;
    int                        nu = HLRBRep_BSurfaceTool::NbUPoles(mySurf);
    int                        nv = HLRBRep_BSurfaceTool::NbVPoles(mySurf);
    NCollection_Array2<gp_Pnt> Pnt(1, nu, 1, nv);
    HLRBRep_BSurfaceTool::Bezier(mySurf)->Poles(Pnt);
    return SideRowsOfPoles(tolF, nu, nv, Pnt);
  }
  else if (myType == GeomAbs_BSplineSurface)
  {
    if (myProj->Perspective())
      return false;
    int                        nu = HLRBRep_BSurfaceTool::NbUPoles(mySurf);
    int                        nv = HLRBRep_BSurfaceTool::NbVPoles(mySurf);
    NCollection_Array2<gp_Pnt> Pnt(1, nu, 1, nv);
    NCollection_Array2<double> W(1, nu, 1, nv);
    HLRBRep_BSurfaceTool::BSpline(mySurf)->Poles(Pnt);
    HLRBRep_BSurfaceTool::BSpline(mySurf)->Weights(W);
    return SideRowsOfPoles(tolF, nu, nv, Pnt);
  }
  else
    return false;
}

bool HLRBRep_Surface::IsAbove(const bool back, const HLRBRep_Curve* A, const double tol) const
{
  bool planar = (myType == GeomAbs_Plane);
  if (planar)
  {
    gp_Pln Pl = Plane();
    double a, b, c, d;
    Pl.Coefficients(a, b, c, d);
    double u, u1, u2, dd, x, y, z;
    gp_Pnt P;
    u1 = A->Parameter3d(A->FirstParameter());
    u2 = A->Parameter3d(A->LastParameter());
    u  = u1;
    A->D0(u, P);
    P.Coord(x, y, z);
    dd = a * x + b * y + c * z + d;
    if (back)
      dd = -dd;
    if (dd < -tol)
      return false;
    if (A->GetType() != GeomAbs_Line)
    {
      int    nbPnt = 30;
      double step  = (u2 - u1) / (nbPnt + 1);
      for (int i = 1; i <= nbPnt; i++)
      {
        u += step;
        A->D0(u, P);
        P.Coord(x, y, z);
        dd = a * x + b * y + c * z + d;
        if (back)
          dd = -dd;
        if (dd < -tol)
          return false;
      }
    }
    u = u2;
    A->D0(u, P);
    P.Coord(x, y, z);
    dd = a * x + b * y + c * z + d;
    if (back)
      dd = -dd;
    if (dd < -tol)
      return false;
    return true;
  }
  else
    return false;
}

gp_Pnt HLRBRep_Surface::Value(const double U, const double V) const
{
  gp_Pnt P;
  D0(U, V, P);
  return P;
}

gp_Pln HLRBRep_Surface::Plane() const
{
  GeomAbs_SurfaceType typ = HLRBRep_BSurfaceTool::GetType(mySurf);
  switch (typ)
  {
    case GeomAbs_BezierSurface:
    {
      gp_Pnt P;
      gp_Vec D1U;
      gp_Vec D1V;
      D1(0.5, 0.5, P, D1U, D1V);
      return gp_Pln(P, gp_Dir(D1U.Crossed(D1V)));
    }

    default:
      return HLRBRep_BSurfaceTool::Plane(mySurf);
  }
}
