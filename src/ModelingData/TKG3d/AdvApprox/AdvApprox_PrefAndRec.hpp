#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <AdvApprox_Cutting.hpp>
#include <Standard_Boolean.hpp>

//! inherits class Cutting; contains a list of preferential points (pi)i
//! and a list of Recommended points used in cutting management.
//! if Cutting is necessary in [a,b], we cut at the di nearest from (a+b)/2
class AdvApprox_PrefAndRec : public AdvApprox_Cutting
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AdvApprox_PrefAndRec(const NCollection_Array1<double>& RecomendedCut,
                                       const NCollection_Array1<double>& PrefferedCut,
                                       const double                      Weight = 5);

  //! cuting value is
  //! - the recommended point nerest of (a+b)/2
  //! if pi is in ]a,b[ or else
  //! -  the preferential point nearest of (a+b) / 2
  //! if pi is in ](r*a+b)/(r+1) , (a+r*b)/(r+1)[ where r = Weight
  //! -  or (a+b)/2 else.
  Standard_EXPORT bool Value(const double a, const double b, double& cuttingvalue) const override;

private:
  NCollection_Array1<double> myRecCutting;
  NCollection_Array1<double> myPrefCutting;
  double                     myWeight;
};

