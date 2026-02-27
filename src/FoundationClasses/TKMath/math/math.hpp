#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Vector.hpp>

namespace math
{
  Standard_EXPORT int GaussPointsMax();

  Standard_EXPORT void GaussPoints(const int Index, math_Vector& Points);

  Standard_EXPORT void GaussWeights(const int Index, math_Vector& Weights);

  Standard_EXPORT int KronrodPointsMax();

  Standard_EXPORT bool OrderedGaussPointsAndWeights(const int    Index,
                                    math_Vector& Points,
                                    math_Vector& Weights);

  Standard_EXPORT bool KronrodPointsAndWeights(const int    Index,
                               math_Vector& Points,
                               math_Vector& Weights);
};
