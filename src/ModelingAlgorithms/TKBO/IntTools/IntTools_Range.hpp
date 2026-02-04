#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>

//! The class describes the 1-d range
//! [myFirst, myLast].
class IntTools_Range
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT IntTools_Range();

  //! Initialize me by range boundaries
  Standard_EXPORT IntTools_Range(const double aFirst, const double aLast);

  //! Modifier
  Standard_EXPORT void SetFirst(const double aFirst);

  //! Modifier
  Standard_EXPORT void SetLast(const double aLast);

  //! Selector
  Standard_EXPORT double First() const;

  //! Selector
  Standard_EXPORT double Last() const;

  //! Selector
  Standard_EXPORT void Range(double& aFirst, double& aLast) const;

private:
  double myFirst;
  double myLast;
};

