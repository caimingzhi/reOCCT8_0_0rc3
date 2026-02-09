

#include <GProp.hpp>

#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>

void GProp::HOperator(

  const gp_Pnt& G,
  const gp_Pnt& Q,
  const double  Mass,
  gp_Mat&       Operator

)
{

  gp_XYZ QG  = G.XYZ() - Q.XYZ();
  double Ixx = QG.Y() * QG.Y() + QG.Z() * QG.Z();
  double Iyy = QG.X() * QG.X() + QG.Z() * QG.Z();
  double Izz = QG.Y() * QG.Y() + QG.X() * QG.X();
  double Ixy = -QG.X() * QG.Y();
  double Iyz = -QG.Y() * QG.Z();
  double Ixz = -QG.X() * QG.Z();
  Operator.SetCols(gp_XYZ(Ixx, Ixy, Ixz), gp_XYZ(Ixy, Iyy, Iyz), gp_XYZ(Ixz, Iyz, Izz));
  Operator.Multiply(Mass);
}
