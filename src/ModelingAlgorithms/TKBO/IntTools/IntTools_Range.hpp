#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>

class IntTools_Range
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_Range();

  Standard_EXPORT IntTools_Range(const double aFirst, const double aLast);

  Standard_EXPORT void SetFirst(const double aFirst);

  Standard_EXPORT void SetLast(const double aLast);

  Standard_EXPORT double First() const;

  Standard_EXPORT double Last() const;

  Standard_EXPORT void Range(double& aFirst, double& aLast) const;

private:
  double myFirst;
  double myLast;
};
