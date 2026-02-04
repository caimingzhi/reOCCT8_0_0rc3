#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <AdvApprox_Cutting.hpp>
#include <Standard_Boolean.hpp>

//! inherits class Cutting; contains a list of preferential points (di)i
//! if Cutting is necessary in [a,b], we cut at the di nearest from (a+b)/2.
class AdvApprox_PrefCutting : public AdvApprox_Cutting
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AdvApprox_PrefCutting(const NCollection_Array1<double>& CutPnts);

  Standard_EXPORT bool Value(const double a, const double b, double& cuttingvalue) const override;

private:
  NCollection_Array1<double> myPntOfCutting;
};

