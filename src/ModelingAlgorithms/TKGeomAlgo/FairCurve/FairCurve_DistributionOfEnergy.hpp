#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt2d.hpp>
#include <math_FunctionSet.hpp>

//! Abstract class to use the Energy of an FairCurve
class FairCurve_DistributionOfEnergy : public math_FunctionSet
{
public:
  DEFINE_STANDARD_ALLOC

  //! returns the number of variables of the function.
  Standard_EXPORT int NbVariables() const override;

  //! returns the number of equations of the function.
  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT void SetDerivativeOrder(const int DerivativeOrder);

protected:
  Standard_EXPORT FairCurve_DistributionOfEnergy(
    const int                                         BSplOrder,
    const occ::handle<NCollection_HArray1<double>>&   FlatKnots,
    const occ::handle<NCollection_HArray1<gp_Pnt2d>>& Poles,
    const int                                         DerivativeOrder,
    const int                                         NbValAux = 0);

  int                                        MyBSplOrder;
  occ::handle<NCollection_HArray1<double>>   MyFlatKnots;
  occ::handle<NCollection_HArray1<gp_Pnt2d>> MyPoles;
  int                                        MyDerivativeOrder;
  int                                        MyNbVar;
  int                                        MyNbEqua;
  int                                        MyNbValAux;
};
