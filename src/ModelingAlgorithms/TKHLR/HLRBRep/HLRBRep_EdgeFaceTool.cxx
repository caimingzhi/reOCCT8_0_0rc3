#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve2d.hpp>
#include <BRepExtrema_ExtPF.hpp>
#include <BRepLib_MakeVertex.hpp>
#include <gp.hpp>
#include <gp_Dir.hpp>
#include <HLRBRep_EdgeFaceTool.hpp>
#include <HLRBRep_Surface.hpp>
#include <TopoDS_Vertex.hpp>

double HLRBRep_EdgeFaceTool::CurvatureValue(const HLRBRep_SurfacePtr F,
                                            const double             U,
                                            const double             V,
                                            const gp_Dir&            Tg)
{
  gp_Pnt P;
  gp_Vec D1U, D1V, D2U, D2V, D2UV;
  ((HLRBRep_Surface*)F)->D2(U, V, P, D1U, D1V, D2U, D2V, D2UV);
  double d1ut   = D1U * Tg;
  double d1vt   = D1V * Tg;
  double d1ud1v = D1U * D1V;
  double nmu2   = D1U * D1U;
  double nmv2   = D1V * D1V;
  double det    = nmu2 * nmv2 - d1ud1v * d1ud1v;
  if (det > gp::Resolution())
  {
    double alfa     = (d1ut * nmv2 - d1vt * d1ud1v) / det;
    double beta     = (d1vt * nmu2 - d1ut * d1ud1v) / det;
    double alfa2    = alfa * alfa;
    double beta2    = beta * beta;
    double alfabeta = alfa * beta;
    gp_Vec Nm       = D1U ^ D1V;
    Nm.Normalize();
    double N = (Nm * D2U) * alfa2 + 2 * (Nm * D2UV) * alfabeta + (Nm * D2V) * beta2;
    double D = nmu2 * alfa2 + 2 * d1ud1v * alfabeta + nmv2 * beta2;
    return N / D;
  }
  return 0.;
}

bool HLRBRep_EdgeFaceTool::UVPoint(const double             Par,
                                   const HLRBRep_CurvePtr   E,
                                   const HLRBRep_SurfacePtr F,
                                   double&                  U,
                                   double&                  V)
{
  double pfbid, plbid;
  if (BRep_Tool::CurveOnSurface(((HLRBRep_Curve*)E)->Curve().Edge(),
                                ((HLRBRep_Surface*)F)->Surface().Face(),
                                pfbid,
                                plbid)
        .IsNull())
  {
    BRepExtrema_ExtPF proj(BRepLib_MakeVertex(((HLRBRep_Curve*)E)->Value3D(Par)),
                           ((HLRBRep_Surface*)F)->Surface().Face());
    int               i, index = 0;
    double            dist2 = RealLast();
    const int         n     = proj.NbExt();
    for (i = 1; i <= n; i++)
    {
      const double newdist2 = proj.SquareDistance(i);
      if (newdist2 < dist2)
      {
        dist2 = newdist2;
        index = i;
      }
    }
    if (index == 0)
      return false;

    proj.Parameter(index, U, V);
  }
  else
  {
    BRepAdaptor_Curve2d PC(((HLRBRep_Curve*)E)->Curve().Edge(),
                           ((HLRBRep_Surface*)F)->Surface().Face());
    gp_Pnt2d            P2d;
    PC.D0(Par, P2d);
    U = P2d.X();
    V = P2d.Y();
  }
  return true;
}
