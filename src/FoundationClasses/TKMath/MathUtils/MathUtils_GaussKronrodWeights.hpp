#pragma once

#include <Standard_Macro.hpp>
#include <math_Vector.hpp>

namespace MathUtils
{

  Standard_EXPORT bool GetKronrodPointsAndWeights(int          theNbKronrod,
                                                  math_Vector& thePoints,
                                                  math_Vector& theWeights);

  Standard_EXPORT bool GetOrderedGaussPointsAndWeights(int          theNbGauss,
                                                       math_Vector& thePoints,
                                                       math_Vector& theWeights);

} // namespace MathUtils
