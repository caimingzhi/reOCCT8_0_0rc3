#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <AdvApprox_Cutting.hpp>
#include <Standard_Boolean.hpp>

class AdvApprox_PrefAndRec : public AdvApprox_Cutting
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AdvApprox_PrefAndRec(const NCollection_Array1<double>& RecomendedCut,
                                       const NCollection_Array1<double>& PrefferedCut,
                                       const double                      Weight = 5);

  Standard_EXPORT bool Value(const double a, const double b, double& cuttingvalue) const override;

private:
  NCollection_Array1<double> myRecCutting;
  NCollection_Array1<double> myPrefCutting;
  double                     myWeight;
};
