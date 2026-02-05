#include <GeomFill_Filling.hpp>
#include <gp_Pnt.hpp>

//=================================================================================================

GeomFill_Filling::GeomFill_Filling()
    : IsRational(false)
{
}

//=================================================================================================

int GeomFill_Filling::NbUPoles() const
{
  return myPoles->ColLength();
}

//=================================================================================================

int GeomFill_Filling::NbVPoles() const
{
  return myPoles->RowLength();
}

//=================================================================================================

void GeomFill_Filling::Poles(NCollection_Array2<gp_Pnt>& Poles) const
{
  Poles = myPoles->ChangeArray2();
}

//=================================================================================================

bool GeomFill_Filling::isRational() const
{
  return IsRational;
}

//=================================================================================================

void GeomFill_Filling::Weights(NCollection_Array2<double>& Weights) const
{
  Weights = myWeights->ChangeArray2();
}
