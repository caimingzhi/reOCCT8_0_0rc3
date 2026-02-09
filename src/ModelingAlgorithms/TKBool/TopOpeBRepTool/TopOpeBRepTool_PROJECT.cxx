#include <TopOpeBRepTool_PROJECT.hpp>

#include <Geom_Surface.hpp>
#include <GeomAPI_ProjectPointOnCurve.hpp>
#include <GeomAPI_ProjectPointOnSurf.hpp>
#include <BRepLib_MakeVertex.hpp>
#include <BRepExtrema_ExtPF.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Curve2d.hpp>
#include <gp_Pnt.hpp>
#include <BRep_Tool.hpp>
#include <Precision.hpp>

#include <TopOpeBRepTool_GEOMETRY.hpp>

Standard_EXPORT void FUN_tool_bounds(const TopoDS_Edge& E, double& f, double& l)
{
  BRepAdaptor_Curve BAC(E);
  f = BAC.FirstParameter();
  l = BAC.LastParameter();
}

Standard_EXPORT int FUN_tool_getindex(const Extrema_ExtPC& ponc)
{
  double Dist2, Dist2Min = ponc.SquareDistance(1);
  int    myIndex = 1, n = ponc.NbExt();

  for (int i = 2; i <= n; i++)
  {
    Dist2 = ponc.SquareDistance(i);
    if (Dist2 < Dist2Min)
    {
      Dist2Min = Dist2;
      myIndex  = i;
    }
  }
  return myIndex;
}

Standard_EXPORT int FUN_tool_getindex(const Extrema_ExtPC2d& ponc)
{
  double Dist2, Dist2Min = ponc.SquareDistance(1);
  int    myIndex = 1, n = ponc.NbExt();

  for (int i = 2; i <= n; i++)
  {
    Dist2 = ponc.SquareDistance(i);
    if (Dist2 < Dist2Min)
    {
      Dist2Min = Dist2;
      myIndex  = i;
    }
  }
  return myIndex;
}

Standard_EXPORT bool FUN_tool_projPonC(const gp_Pnt&            P,
                                       const double             tole,
                                       const BRepAdaptor_Curve& BAC,
                                       const double             pmin,
                                       const double             pmax,
                                       double&                  param,
                                       double&                  dist)
{

  Extrema_ExtPC ponc(P, BAC, pmin, pmax);
  bool          ok    = ponc.IsDone();
  int           nbext = 0;
  if (ok)
  {
    nbext = ponc.NbExt();
    ok    = (nbext > 0);
  }
  if (!ok)
  {
    for (int i = 1; i <= 2; i++)
    {
      double par  = (i == 1) ? pmin : pmax;
      gp_Pnt pt   = BAC.Value(par);
      double d2   = pt.SquareDistance(P);
      bool   onpt = (d2 < tole * tole);
      if (onpt)
      {
        param = par;
        dist  = sqrt(d2);
        return true;
      }
    }
    return false;
  }
  int i = FUN_tool_getindex(ponc);
  param = ponc.Point(i).Parameter();
  dist  = sqrt(ponc.SquareDistance(i));
  return true;
}

Standard_EXPORT bool FUN_tool_projPonC(const gp_Pnt&            P,
                                       const BRepAdaptor_Curve& BAC,
                                       const double             pmin,
                                       const double             pmax,
                                       double&                  param,
                                       double&                  dist)
{

  double tole = BAC.Tolerance();
  bool   ok   = FUN_tool_projPonC(P, tole, BAC, pmin, pmax, param, dist);
  return ok;
}

Standard_EXPORT bool FUN_tool_projPonC(const gp_Pnt&            P,
                                       const BRepAdaptor_Curve& BAC,
                                       double&                  param,
                                       double&                  dist)
{

  double tole = BAC.Tolerance();
  double pmin = BAC.FirstParameter();
  double pmax = BAC.LastParameter();
  bool   ok   = FUN_tool_projPonC(P, tole, BAC, pmin, pmax, param, dist);
  return ok;
}

Standard_EXPORT bool FUN_tool_projPonC2D(const gp_Pnt&              P,
                                         const double               tole,
                                         const BRepAdaptor_Curve2d& BAC2D,
                                         const double               pmin,
                                         const double               pmax,
                                         double&                    param,
                                         double&                    dist)
{

  bool ok = false;

  gp_Pnt2d           P2D;
  const TopoDS_Face& F = BAC2D.Face();
  ok                   = FUN_tool_projPonF(P, F, P2D, dist);
  if (!ok)
    return false;

  Extrema_ExtPC2d ponc2d(P2D, BAC2D, pmin, pmax);
  ok        = ponc2d.IsDone();
  int nbext = ponc2d.NbExt();
  if (ok)
    ok = (nbext > 0);
  if (!ok)
  {
    for (int i = 1; i <= 2; i++)
    {
      double   par  = (i == 1) ? pmin : pmax;
      gp_Pnt2d pt2d = BAC2D.Value(par);
      double   d2   = pt2d.SquareDistance(P2D);
      bool     onpt = (d2 < tole * tole);
      if (onpt)
      {
        param = par;
        dist  = sqrt(d2);
        return true;
      }
    }
    return false;
  }

  int i = FUN_tool_getindex(ponc2d);
  param = ponc2d.Point(i).Parameter();
  dist  = sqrt(ponc2d.SquareDistance(i));
  return true;
}

Standard_EXPORT bool FUN_tool_projPonC2D(const gp_Pnt&              P,
                                         const BRepAdaptor_Curve2d& BAC2D,
                                         const double               pmin,
                                         const double               pmax,
                                         double&                    param,
                                         double&                    dist)
{

  double tole = BRep_Tool::Tolerance(BAC2D.Edge());
  bool   ok   = FUN_tool_projPonC2D(P, tole, BAC2D, pmin, pmax, param, dist);
  return ok;
}

Standard_EXPORT bool FUN_tool_projPonC2D(const gp_Pnt&              P,
                                         const BRepAdaptor_Curve2d& BAC2D,
                                         double&                    param,
                                         double&                    dist)
{

  double tole = BRep_Tool::Tolerance(BAC2D.Edge());
  double pmin = BAC2D.FirstParameter();
  double pmax = BAC2D.LastParameter();
  bool   ok   = FUN_tool_projPonC2D(P, tole, BAC2D, pmin, pmax, param, dist);
  return ok;
}

Standard_EXPORT bool FUN_tool_projPonS(const gp_Pnt&                    P,
                                       const occ::handle<Geom_Surface>& S,
                                       gp_Pnt2d&                        UV,
                                       double&                          dist,
                                       const Extrema_ExtFlag            anExtFlag,
                                       const Extrema_ExtAlgo            anExtAlgo)
{
  double                     UMin, UMax, VMin, VMax;
  GeomAPI_ProjectPointOnSurf PonS;

  S->Bounds(UMin, UMax, VMin, VMax);
  PonS.Init(S, UMin, UMax, VMin, VMax, anExtAlgo);
  Extrema_ExtPS& anExtPS = const_cast<Extrema_ExtPS&>(PonS.Extrema());
  anExtPS.SetFlag(anExtFlag);

  PonS.Perform(P);

  if (!PonS.Extrema().IsDone())
    return false;
  if (PonS.NbPoints() == 0)
    return false;
  dist = PonS.LowerDistance();
  double U, V;
  PonS.LowerDistanceParameters(U, V);
  UV.SetCoord(U, V);
  return true;
}

Standard_EXPORT bool FUN_tool_projPonE(const gp_Pnt&      P,
                                       const double       tole,
                                       const TopoDS_Edge& E,
                                       double&            param,
                                       double&            dist)
{
  dist = 1.;
  BRepAdaptor_Curve BAC(E);
  double            first = BAC.FirstParameter();
  double            last  = BAC.LastParameter();
  bool              ok    = FUN_tool_projPonC(P, tole, BAC, first, last, param, dist);
  if (!ok)
    return false;

  double f, l;
  FUN_tool_bounds(E, f, l);
  double tolp = Precision::Parametric(Precision::Confusion());
  bool   onf  = std::abs(f - param) < tolp;
  if (onf)
    param = f;
  bool onl = std::abs(l - param) < tolp;
  if (onl)
    param = l;
  return true;
}

Standard_EXPORT bool FUN_tool_projPonE(const gp_Pnt&      P,
                                       const TopoDS_Edge& E,
                                       double&            param,
                                       double&            dist)
{
  double tole = BRep_Tool::Tolerance(E);
  bool   ok   = FUN_tool_projPonE(P, tole, E, param, dist);
  return ok;
}

Standard_EXPORT bool FUN_tool_projPonboundedF(const gp_Pnt&      P,
                                              const TopoDS_Face& F,
                                              gp_Pnt2d&          UV,
                                              double&            dist)
{
  dist = 1.;

  BRepLib_MakeVertex mv(P);
  TopoDS_Vertex      V = mv.Vertex();
  BRepExtrema_ExtPF  PonF(V, F);
  if (!PonF.IsDone())
    return false;
  int npt = PonF.NbExt();
  if (npt == 0)
    return false;

  double dmin2 = 1.e14;
  int    imin  = 0;
  for (int i = 1; i <= npt; i++)
  {
    double d2 = PonF.SquareDistance(i);
    if (d2 < dmin2)
    {
      imin  = i;
      dmin2 = d2;
    }
  }
  if (imin == 0)
    return false;

  double u, v;
  PonF.Parameter(imin, u, v);
  dist = sqrt(dmin2);
  UV   = gp_Pnt2d(u, v);
  return true;
}

Standard_EXPORT bool FUN_tool_projPonF(const gp_Pnt&         P,
                                       const TopoDS_Face&    F,
                                       gp_Pnt2d&             UV,
                                       double&               dist,
                                       const Extrema_ExtFlag anExtFlag,
                                       const Extrema_ExtAlgo anExtAlgo)
{
  dist                         = 1.;
  occ::handle<Geom_Surface> S  = BRep_Tool::Surface(F);
  bool                      ok = FUN_tool_projPonS(P, S, UV, dist, anExtFlag, anExtAlgo);
  return ok;
}
