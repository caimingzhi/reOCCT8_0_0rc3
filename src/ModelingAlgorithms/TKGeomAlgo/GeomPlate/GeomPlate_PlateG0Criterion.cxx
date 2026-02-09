#include <AdvApp2Var_Context.hpp>
#include <AdvApp2Var_Patch.hpp>
#include <GeomPlate_PlateG0Criterion.hpp>
#include <gp_Pnt.hpp>
#include <gp_XY.hpp>
#include <PLib.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

GeomPlate_PlateG0Criterion::GeomPlate_PlateG0Criterion(const NCollection_Sequence<gp_XY>&  Data,
                                                       const NCollection_Sequence<gp_XYZ>& G0Data,
                                                       const double                        Maximum,
                                                       const AdvApp2Var_CriterionType      Type,
                                                       const AdvApp2Var_CriterionRepartition Repart)
{
  myData        = Data;
  myXYZ         = G0Data;
  myMaxValue    = Maximum;
  myType        = Type;
  myRepartition = Repart;
}

void GeomPlate_PlateG0Criterion::Value(AdvApp2Var_Patch& P, const AdvApp2Var_Context& C) const
{
  double  UInt[2], VInt[2];
  int     MaxNbCoeff[2], NbCoeff[2];
  double* adrCoeff = nullptr;
  adrCoeff         = (double*)&P.Coefficients(1, C)->ChangeArray1()(P.Coefficients(1, C)->Lower());

  MaxNbCoeff[0] = C.ULimit();
  MaxNbCoeff[1] = C.VLimit();
  NbCoeff[0]    = P.NbCoeffInU();
  NbCoeff[1]    = P.NbCoeffInV();
  UInt[0]       = P.U0();
  UInt[1]       = P.U1();
  VInt[0]       = P.V0();
  VInt[1]       = P.V1();

  double up, vp, dist = 0.;

  int                        dimension = 3 * NbCoeff[1];
  NCollection_Array1<double> Patch(1, NbCoeff[0] * dimension);
  NCollection_Array1<double> Curve(1, dimension);
  NCollection_Array1<double> Point(1, 3);
  double*                    Coeffs = (double*)&Patch.ChangeValue(1);
  double*                    Digit  = (double*)&Point.ChangeValue(1);

  int k1, k2, pos, ll = 1;
  for (k1 = 1; k1 <= NbCoeff[0]; k1++)
  {

    pos = 3 * (MaxNbCoeff[1]) * (k1 - 1);
    for (k2 = 1; k2 <= NbCoeff[1]; k2++, pos += 3)
    {
      Patch(ll)     = adrCoeff[pos];
      Patch(ll + 1) = adrCoeff[pos + 1];
      Patch(ll + 2) = adrCoeff[pos + 2];
      ll += 3;
    }
  }

  int i, NbCtr = myData.Length();
  for (i = 1; i <= NbCtr; i++)
  {
    gp_XY P2d = myData.Value(i);

    gp_Pnt P3d;
    if (UInt[0] < P2d.X() && P2d.X() < UInt[1] && VInt[0] < P2d.Y() && P2d.Y() < VInt[1])
    {

      up = (2 * P2d.X() - UInt[0] - UInt[1]) / (UInt[1] - UInt[0]);
      vp = (2 * P2d.Y() - VInt[0] - VInt[1]) / (VInt[1] - VInt[0]);
      PLib::EvalPoly2Var(up, vp, 0, 0, NbCoeff[0] - 1, NbCoeff[1] - 1, 3, Coeffs[0], Digit[0]);

      P3d.SetCoord(1, Digit[0]);
      P3d.SetCoord(2, Digit[1]);
      P3d.SetCoord(3, Digit[2]);
      double x = (P3d.Coord(1) - myXYZ.Value(i).Coord(1)),
             y = (P3d.Coord(2) - myXYZ.Value(i).Coord(2)),
             z = (P3d.Coord(3) - myXYZ.Value(i).Coord(3)), DistTmp = x * x + y * y + z * z;
      if (DistTmp > dist)
      {
        dist = DistTmp;
      }
    }
  }
  P.SetCritValue(std::sqrt(dist));
}

bool GeomPlate_PlateG0Criterion::IsSatisfied(const AdvApp2Var_Patch& P) const
{
  return (P.CritValue() < myMaxValue);
}
