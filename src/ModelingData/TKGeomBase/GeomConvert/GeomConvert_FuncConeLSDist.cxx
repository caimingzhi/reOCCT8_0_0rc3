

#include <GeomConvert_FuncConeLSDist.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Ax3.hpp>
#include <math_Vector.hpp>
#include <ElSLib.hpp>

GeomConvert_FuncConeLSDist::GeomConvert_FuncConeLSDist(
  const occ::handle<NCollection_HArray1<gp_XYZ>>& thePoints,
  const gp_Dir&                                   theDir)
    : myPoints(thePoints),
      myDir(theDir)
{
}

int GeomConvert_FuncConeLSDist::NbVariables() const
{
  return 5;
}

bool GeomConvert_FuncConeLSDist::Value(const math_Vector& X, double& F)
{
  gp_Pnt aLoc(X(1), X(2), X(3));
  double aSemiAngle = X(4), anR = X(5);
  gp_Ax3 aPos(aLoc, myDir);

  F = 0.;
  int i;
  for (i = myPoints->Lower(); i <= myPoints->Upper(); ++i)
  {
    double u, v;
    gp_Pnt aPi(myPoints->Value(i));
    ElSLib::ConeParameters(aPos, anR, aSemiAngle, aPi, u, v);
    gp_Pnt aPp;
    ElSLib::ConeD0(u, v, aPos, anR, aSemiAngle, aPp);
    F += aPi.SquareDistance(aPp);
  }

  return true;
}
