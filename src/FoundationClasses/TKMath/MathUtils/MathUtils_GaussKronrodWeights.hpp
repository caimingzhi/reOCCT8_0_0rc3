#pragma once

//! @file MathUtils_GaussKronrodWeights.hpp
//! Wrapper for accessing Gauss-Kronrod quadrature weights.
//! This header isolates the old class math from the new namespace MathUtils.
//! Implementation is in MathUtils_GaussKronrodWeights.cxx to avoid conflicts.

#include <Standard_Macro.hpp>
#include <math_Vector.hpp>

//! Core utilities for modern math solvers.
namespace MathUtils
{

  //! Get Gauss-Kronrod points and weights.
  //! @param theNbKronrod number of Kronrod points (should be 2n+1)
  //! @param thePoints output vector for points
  //! @param theWeights output vector for weights
  //! @return true if successful
  Standard_EXPORT bool GetKronrodPointsAndWeights(int          theNbKronrod,
                                                  math_Vector& thePoints,
                                                  math_Vector& theWeights);

  //! Get ordered Gauss points and weights.
  //! @param theNbGauss number of Gauss points
  //! @param thePoints output vector for points
  //! @param theWeights output vector for weights
  //! @return true if successful
  Standard_EXPORT bool GetOrderedGaussPointsAndWeights(int          theNbGauss,
                                                       math_Vector& thePoints,
                                                       math_Vector& theWeights);

} // namespace MathUtils
