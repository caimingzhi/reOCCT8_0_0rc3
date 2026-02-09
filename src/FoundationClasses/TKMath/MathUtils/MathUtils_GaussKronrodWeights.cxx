

#include "MathUtils_GaussKronrodWeights.hpp"
#include <math.hpp>

bool MathUtils::GetKronrodPointsAndWeights(int          theNbKronrod,
                                           math_Vector& thePoints,
                                           math_Vector& theWeights)
{
  return math::KronrodPointsAndWeights(theNbKronrod, thePoints, theWeights);
}

bool MathUtils::GetOrderedGaussPointsAndWeights(int          theNbGauss,
                                                math_Vector& thePoints,
                                                math_Vector& theWeights)
{
  return math::OrderedGaussPointsAndWeights(theNbGauss, thePoints, theWeights);
}
