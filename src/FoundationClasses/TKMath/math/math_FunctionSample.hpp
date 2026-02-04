#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>

//! This class gives a default sample (constant difference
//! of parameter) for a function defined between
//! two bound A,B.
class math_FunctionSample
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_FunctionSample(const double A, const double B, const int N);

  //! Returns the bounds of parameters.
  Standard_EXPORT virtual void Bounds(double& A, double& B) const;

  //! Returns the number of sample points.
  Standard_EXPORT int NbPoints() const;

  //! Returns the value of parameter of the point of
  //! range Index : A + ((Index-1)/(NbPoints-1))*B.
  //! An exception is raised if Index<=0 or Index>NbPoints.
  Standard_EXPORT virtual double GetParameter(const int Index) const;

private:
  double a;
  double b;
  int    n;
};

