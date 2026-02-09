#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Real.hpp>
#include <math_Vector.hpp>
#include <NCollection_Array2.hpp>

class math_EigenValuesSearcher
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_EigenValuesSearcher(const NCollection_Array1<double>& theDiagonal,
                                           const NCollection_Array1<double>& theSubdiagonal);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int Dimension() const;

  Standard_EXPORT double EigenValue(const int theIndex) const;

  Standard_EXPORT math_Vector EigenVector(const int theIndex) const;

private:
  NCollection_Array1<double> myDiagonal;
  NCollection_Array1<double> mySubdiagonal;
  bool                       myIsDone;
  int                        myN;
  NCollection_Array1<double> myEigenValues;
  NCollection_Array2<double> myEigenVectors;
};
