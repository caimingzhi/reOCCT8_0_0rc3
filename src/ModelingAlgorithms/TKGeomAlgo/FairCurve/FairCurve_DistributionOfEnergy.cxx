#include <FairCurve_DistributionOfEnergy.hpp>

int FairCurve_DistributionOfEnergy::NbVariables() const
{
  return MyNbVar;
}

int FairCurve_DistributionOfEnergy::NbEquations() const
{
  return MyNbEqua;
}

FairCurve_DistributionOfEnergy::FairCurve_DistributionOfEnergy(
  const int                                         BSplOrder,
  const occ::handle<NCollection_HArray1<double>>&   FlatKnots,
  const occ::handle<NCollection_HArray1<gp_Pnt2d>>& Poles,
  const int                                         DerivativeOrder,
  const int                                         NbValAux)
    : MyBSplOrder(BSplOrder),
      MyFlatKnots(FlatKnots),
      MyPoles(Poles),
      MyDerivativeOrder(DerivativeOrder),
      MyNbValAux(NbValAux)
{
  MyNbVar = 1;
  SetDerivativeOrder(DerivativeOrder);
}

void FairCurve_DistributionOfEnergy::SetDerivativeOrder(const int DerivativeOrder)
{
  MyNbEqua = 1;
  if (DerivativeOrder >= 1)
    MyNbEqua += 2 * MyPoles->Length() + MyNbValAux;
  if (DerivativeOrder >= 2)
    MyNbEqua = MyNbEqua + (MyNbEqua - 1) * MyNbEqua / 2;
  MyDerivativeOrder = DerivativeOrder;
}
