#include <Intf.hpp>

#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>

void Intf::PlaneEquation(const gp_Pnt& P1,
                         const gp_Pnt& P2,
                         const gp_Pnt& P3,
                         gp_XYZ&       NormalVector,
                         double&       PolarDistance)
{
  gp_XYZ v1       = P2.XYZ() - P1.XYZ();
  gp_XYZ v2       = P3.XYZ() - P2.XYZ();
  gp_XYZ v3       = P1.XYZ() - P3.XYZ();
  NormalVector    = (v1 ^ v2) + (v2 ^ v3) + (v3 ^ v1);
  double aNormLen = NormalVector.Modulus();
  if (aNormLen < gp::Resolution())
  {
    PolarDistance = 0.;
  }
  else
  {
    NormalVector.Divide(aNormLen);
    PolarDistance = NormalVector * P1.XYZ();
  }
}

bool Intf::Contain(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3, const gp_Pnt& ThePnt)
{
  gp_XYZ v1 = (P2.XYZ() - P1.XYZ()) ^ (ThePnt.XYZ() - P1.XYZ());
  gp_XYZ v2 = (P3.XYZ() - P2.XYZ()) ^ (ThePnt.XYZ() - P2.XYZ());
  gp_XYZ v3 = (P1.XYZ() - P3.XYZ()) ^ (ThePnt.XYZ() - P3.XYZ());
  return v1 * v2 >= 0. && v2 * v3 >= 0. && v3 * v1 >= 0.;
}
