#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AdvApprox_Cutting.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>

//! if Cutting is necessary in [a,b], we cut at (a+b) / 2.
class AdvApprox_DichoCutting : public AdvApprox_Cutting
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AdvApprox_DichoCutting();

  Standard_EXPORT bool Value(const double a, const double b, double& cuttingvalue) const override;
};
