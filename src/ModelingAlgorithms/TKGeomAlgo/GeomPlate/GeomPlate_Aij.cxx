#include <GeomPlate_Aij.hpp>
#include <GeomPlate_BuildAveragePlane.hpp>
#include <gp_Vec.hpp>

GeomPlate_Aij::GeomPlate_Aij()
    : Ind1(0),
      Ind2(0)
{
}

GeomPlate_Aij::GeomPlate_Aij(const int anInd1, const int anInd2, const gp_Vec& aVec)
{
  Ind1 = anInd1;
  Ind2 = anInd2;
  Vec  = aVec;
}
