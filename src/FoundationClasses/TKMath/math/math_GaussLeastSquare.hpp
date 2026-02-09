#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Matrix.hpp>
#include <math_IntegerVector.hpp>
#include <math_Vector.hpp>
#include <Standard_OStream.hpp>

class math_GaussLeastSquare
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_GaussLeastSquare(const math_Matrix& A, const double MinPivot = 1.0e-20);

  bool IsDone() const;

  Standard_EXPORT void Solve(const math_Vector& B, math_Vector& X) const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

protected:
  bool               Singular{};
  math_Matrix        LU;
  math_Matrix        A2;
  math_IntegerVector Index;
  double             D{};

private:
  bool Done;
};

inline bool math_GaussLeastSquare::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_GaussLeastSquare& G)
{
  G.Dump(o);
  return o;
}
