#include <ChFiKPart_ComputeData_CS.hpp>
#include <gp_Ax3.hpp>
#include <gp_Vec.hpp>
#include <gp_Pnt.hpp>
#include <gp_Dir.hpp>
#include <ElCLib.hpp>

void ChFiKPart_CornerSpine(const occ::handle<Adaptor3d_Surface>& S1,
                           const occ::handle<Adaptor3d_Surface>& S2,
                           const gp_Pnt2d&                       P1S1,
                           const gp_Pnt2d& /*P2S1*/,
                           const gp_Pnt2d& P1S2,
                           const gp_Pnt2d& P2S2,
                           const double    R,
                           gp_Cylinder&    cyl,
                           gp_Circ&        circ,
                           double&         First,
                           double&         Last)

{
  gp_Ax3 ax = S1->Plane().Position();
  gp_Vec V1(ax.XDirection());
  gp_Vec V2(ax.YDirection());
  gp_Pnt P;
  gp_Vec du, dv;
  S2->D1(P1S2.X(), P1S2.Y(), P, du, dv);
  gp_Vec V(P, S1->Value(P1S1.X(), P1S1.Y()));
  V = V.Dot(V1) * V1 + V.Dot(V2) * V2;
  V.Normalize();
  gp_Pnt P2 = S2->Value(P2S2.X(), P2S2.Y());
  gp_Vec Vorien(P, P2);
  gp_Pnt cent;
  gp_Dir dx(V);
  if (V.Dot(Vorien) >= 0.)
  {
    cent.SetCoord(P.X() + R * V.X(), P.Y() + R * V.Y(), P.Z() + R * V.Z());
    dx.Reverse();
  }
  else
  {
    cent.SetCoord(P.X() - R * V.X(), P.Y() - R * V.Y(), P.Z() - R * V.Z());
  }
  gp_Dir dy(gp_Vec(cent, P2));
  dy = (dx ^ dy) ^ dx;
  gp_Ax2 circax2(cent, dx ^ dy, dx);
  gp_Ax3 cylax3(circax2);
  if ((du ^ dv).Dot(dx) < 0.)
    cylax3.ZReverse();
  First = 0.;
  Last  = ElCLib::CircleParameter(circax2, P2);
  circ.SetPosition(circax2);
  circ.SetRadius(R);
  cyl.SetPosition(cylax3);
  cyl.SetRadius(R);
}
