#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Matrix.hpp>
#include <math_IntegerVector.hpp>
#include <math_Vector.hpp>
#include <Standard_OStream.hpp>
#include <Message_ProgressRange.hpp>

class math_Gauss
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_Gauss(const math_Matrix&           A,
                             const double                 MinPivot    = 1.0e-20,
                             const Message_ProgressRange& theProgress = Message_ProgressRange());

  bool IsDone() const { return Done; }

  Standard_EXPORT void Solve(const math_Vector& B, math_Vector& X) const;

  Standard_EXPORT void Solve(math_Vector& B) const;

  Standard_EXPORT double Determinant() const;

  Standard_EXPORT void Invert(math_Matrix& Inv) const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

protected:
  math_Matrix        LU;
  math_IntegerVector Index;
  double             D;
  bool               Done;
};

inline Standard_OStream& operator<<(Standard_OStream& o, const math_Gauss& mG)
{
  mG.Dump(o);
  return o;
}
