#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>

class math_SVD
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_SVD(const math_Matrix& A);

  bool IsDone() const;

  Standard_EXPORT void Solve(const math_Vector& B, math_Vector& X, const double Eps = 1.0e-6);

  Standard_EXPORT void PseudoInverse(math_Matrix& Inv, const double Eps = 1.0e-6);

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  bool        Done;
  math_Matrix U;
  math_Matrix V;
  math_Vector Diag;
  int         RowA;
};

inline bool math_SVD::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_SVD& S)
{
  S.Dump(o);
  return o;
}
