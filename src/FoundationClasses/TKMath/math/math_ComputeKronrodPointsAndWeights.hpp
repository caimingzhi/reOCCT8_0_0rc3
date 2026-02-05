#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <math_Vector.hpp>

class math_ComputeKronrodPointsAndWeights
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_ComputeKronrodPointsAndWeights(const int Number);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT math_Vector Points() const;

  Standard_EXPORT math_Vector Weights() const;

private:
  occ::handle<NCollection_HArray1<double>> myPoints;
  occ::handle<NCollection_HArray1<double>> myWeights;
  bool                                     myIsDone;
};
