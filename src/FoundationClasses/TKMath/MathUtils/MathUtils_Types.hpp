#pragma once

#include <math_Vector.hpp>
#include <math_Matrix.hpp>

#include <array>
#include <optional>

namespace MathUtils
{

  enum class Status
  {
    OK,
    NotConverged,
    MaxIterations,
    NumericalError,
    InvalidInput,
    InfiniteSolutions,
    NoSolution,
    NotPositiveDefinite,
    Singular
  };

  struct ScalarResult
  {
    Status                Status       = Status::NotConverged;
    size_t                NbIterations = 0;
    std::optional<double> Root;
    std::optional<double> Value;
    std::optional<double> Derivative;

    bool IsDone() const { return Status == Status::OK; }

    explicit operator bool() const { return IsDone(); }
  };

  struct PolyResult
  {
    Status                Status  = Status::NotConverged;
    size_t                NbRoots = 0;
    std::array<double, 4> Roots   = {0.0, 0.0, 0.0, 0.0};

    bool IsDone() const { return Status == Status::OK; }

    explicit operator bool() const { return IsDone(); }

    double operator[](int theIndex) const { return Roots[theIndex]; }
  };

  struct VectorResult
  {
    Status                     Status       = Status::NotConverged;
    size_t                     NbIterations = 0;
    std::optional<math_Vector> Solution;
    std::optional<double>      Value;
    std::optional<math_Vector> Gradient;
    std::optional<math_Matrix> Jacobian;

    bool IsDone() const { return Status == Status::OK; }

    explicit operator bool() const { return IsDone(); }
  };

  struct LinearResult
  {
    Status                     Status = Status::NotConverged;
    std::optional<math_Vector> Solution;
    std::optional<double>      Determinant;

    bool IsDone() const { return Status == Status::OK; }

    explicit operator bool() const { return IsDone(); }
  };

  struct EigenResult
  {
    Status                     Status       = Status::NotConverged;
    size_t                     NbIterations = 0;
    std::optional<math_Vector> EigenValues;
    std::optional<math_Matrix> EigenVectors;

    bool IsDone() const { return Status == Status::OK; }

    explicit operator bool() const { return IsDone(); }
  };

  struct DecompResult
  {
    Status                     Status = Status::NotConverged;
    std::optional<math_Matrix> L;
    std::optional<math_Matrix> U;
    std::optional<math_Vector> D;
    std::optional<double>      Determinant;

    bool IsDone() const { return Status == Status::OK; }

    explicit operator bool() const { return IsDone(); }
  };

  struct IntegResult
  {
    Status                Status       = Status::NotConverged;
    size_t                NbIterations = 0;
    size_t                NbPoints     = 0;
    std::optional<double> Value;
    std::optional<double> AbsoluteError;
    std::optional<double> RelativeError;

    bool IsDone() const { return Status == Status::OK; }

    explicit operator bool() const { return IsDone(); }
  };

  struct InverseResult
  {
    Status                     Status = Status::NotConverged;
    std::optional<math_Matrix> Inverse;
    std::optional<double>      Determinant;

    bool IsDone() const { return Status == Status::OK; }

    explicit operator bool() const { return IsDone(); }
  };

} // namespace MathUtils
