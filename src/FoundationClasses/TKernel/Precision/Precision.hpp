#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Real.hpp>

class Precision
{
public:
  DEFINE_STANDARD_ALLOC

  static constexpr double Angular() { return 1.e-12; }

  static constexpr double Confusion() { return 1.e-7; }

  static constexpr double SquareConfusion() { return Confusion() * Confusion(); }

  static constexpr double Computational() { return RealEpsilon(); }

  static constexpr double SquareComputational() { return Computational() * Computational(); }

  static constexpr double Intersection() { return Confusion() * 0.01; }

  static constexpr double Approximation() { return Confusion() * 10.0; }

  static constexpr double Parametric(const double P, const double T) { return P / T; }

  static constexpr double PConfusion(const double T) { return Parametric(Confusion(), T); }

  static constexpr double SquarePConfusion() { return PConfusion() * PConfusion(); }

  static constexpr double PIntersection(const double T) { return Parametric(Intersection(), T); }

  static constexpr double PApproximation(const double T) { return Parametric(Approximation(), T); }

  static constexpr double Parametric(const double P) { return P * 0.01; }

  static constexpr double PConfusion() { return Confusion() * 0.01; }

  static constexpr double PIntersection() { return Intersection() * 0.01; }

  static constexpr double PApproximation() { return Approximation() * 0.01; }

  static inline bool IsInfinite(const double R)
  {
    return std::abs(R) >= (0.5 * Precision::Infinite());
  }

  static constexpr bool IsPositiveInfinite(const double R)
  {
    return R >= (0.5 * Precision::Infinite());
  }

  static constexpr bool IsNegativeInfinite(const double R)
  {
    return R <= -(0.5 * Precision::Infinite());
  }

  static constexpr double Infinite() { return 2.e+100; }
};
