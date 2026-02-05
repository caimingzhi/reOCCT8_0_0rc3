#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Vector.hpp>
#include <math_IntegerVector.hpp>
class math_Matrix;

//! Parallel Approximation in n curves.
//! This package gives all the algorithms used to approximate a MultiLine
//! described by the tool MLineTool.
//! The result of the approximation will be a MultiCurve.
class AppParCurves
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void BernsteinMatrix(const int          NbPoles,
                                              const math_Vector& U,
                                              math_Matrix&       A);

  Standard_EXPORT static void Bernstein(const int          NbPoles,
                                        const math_Vector& U,
                                        math_Matrix&       A,
                                        math_Matrix&       DA);

  Standard_EXPORT static void SecondDerivativeBernstein(const double U, math_Vector& DDA);

  Standard_EXPORT static void SplineFunction(const int           NbPoles,
                                             const int           Degree,
                                             const math_Vector&  Parameters,
                                             const math_Vector&  FlatKnots,
                                             math_Matrix&        A,
                                             math_Matrix&        DA,
                                             math_IntegerVector& Index);
};
