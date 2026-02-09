

#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve2d.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepTopAdaptor_HVertex.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepTopAdaptor_HVertex, Adaptor3d_HVertex)

BRepTopAdaptor_HVertex::BRepTopAdaptor_HVertex(const TopoDS_Vertex&                    V,
                                               const occ::handle<BRepAdaptor_Curve2d>& C)
    : myVtx(V),
      myCurve(C)
{
}

gp_Pnt2d BRepTopAdaptor_HVertex::Value()
{

  return gp_Pnt2d(RealFirst(), RealFirst());
}

double BRepTopAdaptor_HVertex::Parameter(const occ::handle<Adaptor2d_Curve2d>& C)
{
  occ::handle<BRepAdaptor_Curve2d> brhc = occ::down_cast<BRepAdaptor_Curve2d>(C);
  return BRep_Tool::Parameter(myVtx, brhc->Edge(), brhc->Face());
}

double BRepTopAdaptor_HVertex::Resolution(const occ::handle<Adaptor2d_Curve2d>& C)
{
  occ::handle<BRepAdaptor_Curve2d> brhc = occ::down_cast<BRepAdaptor_Curve2d>(C);
  const TopoDS_Face&               F    = brhc->Face();
  BRepAdaptor_Surface              S(F, false);
  double                           tv = BRep_Tool::Tolerance(myVtx);
  double                           pp, p = BRep_Tool::Parameter(myVtx, brhc->Edge(), brhc->Face());
  TopAbs_Orientation               Or = Orientation();
  gp_Pnt2d                         p2d;
  gp_Vec2d                         v2d;
  C->D1(p, p2d, v2d);
  gp_Pnt P, P1;
  gp_Vec DU, DV, DC;
  S.D1(p2d.X(), p2d.Y(), P, DU, DV);
  DC.SetLinearForm(v2d.X(), DU, v2d.Y(), DV);
  double ResUV, mag = DC.Magnitude();

  double URes   = S.UResolution(tv);
  double VRes   = S.VResolution(tv);
  double tURes  = C->Resolution(URes);
  double tVRes  = C->Resolution(VRes);
  double ResUV1 = std::max(tURes, tVRes);

  if (mag < 1e-12)
  {

    return (ResUV1);
  }

  if (tv > 1.e7 * mag)
    ResUV = 1.e7;
  else
    ResUV = tv / mag;

  if (Or == TopAbs_REVERSED)
    pp = p + ResUV;
  else
    pp = p - ResUV;

  double UMin = C->FirstParameter();
  double UMax = C->LastParameter();
  if (pp > UMax)
    pp = UMax;
  if (pp < UMin)
    pp = UMin;

  C->D0(pp, p2d);
  S.D0(p2d.X(), p2d.Y(), P1);

  double Dist = P.Distance(P1);
  if ((Dist > 1e-12) && ((Dist > 1.1 * tv) || (Dist < 0.8 * tv)))
  {

    double Dist1;
    if (Or == TopAbs_REVERSED)
      pp = p + tv / Dist;
    else
      pp = p - tv / Dist;

    if (pp > UMax)
      pp = UMax;
    if (pp < UMin)
      pp = UMin;

    C->D1(pp, p2d, v2d);
    S.D1(p2d.X(), p2d.Y(), P1, DU, DV);
    DC.SetLinearForm(v2d.X(), DU, v2d.Y(), DV);
    Dist1 = P.Distance(P1);
    if (std::abs(Dist1 - tv) < std::abs(Dist - tv))
    {

      ResUV = tv / Dist;
      Dist  = Dist1;
    }

    mag = DC.Magnitude();
    if (tv > 1.e7 * mag)
      mag = tv * 1.e-7;
    if (Or == TopAbs_REVERSED)
      pp = p + tv / mag;
    else
      pp = p - tv / mag;

    if (pp > UMax)
      pp = UMax;
    if (pp < UMin)
      pp = UMin;

    C->D0(pp, p2d);
    S.D0(p2d.X(), p2d.Y(), P1);
    Dist1 = P.Distance(P1);
    if (std::abs(Dist1 - tv) < std::abs(Dist - tv))
    {

      ResUV = tv / mag;
      Dist  = Dist1;
    }
  }

  return std::min(ResUV, ResUV1);
}

TopAbs_Orientation BRepTopAdaptor_HVertex::Orientation()
{
  return myVtx.Orientation();
}

bool BRepTopAdaptor_HVertex::IsSame(const occ::handle<Adaptor3d_HVertex>& Other)
{
  occ::handle<BRepTopAdaptor_HVertex> brhv = occ::down_cast<BRepTopAdaptor_HVertex>(Other);
  return myVtx.IsSame(brhv->Vertex());
}
