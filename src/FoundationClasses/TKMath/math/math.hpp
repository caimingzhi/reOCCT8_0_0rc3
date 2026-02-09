#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Vector.hpp>

class math
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static int GaussPointsMax();

  Standard_EXPORT static void GaussPoints(const int Index, math_Vector& Points);

  Standard_EXPORT static void GaussWeights(const int Index, math_Vector& Weights);

  Standard_EXPORT static int KronrodPointsMax();

  Standard_EXPORT static bool OrderedGaussPointsAndWeights(const int    Index,
                                                           math_Vector& Points,
                                                           math_Vector& Weights);

  Standard_EXPORT static bool KronrodPointsAndWeights(const int    Index,
                                                      math_Vector& Points,
                                                      math_Vector& Weights);
};
