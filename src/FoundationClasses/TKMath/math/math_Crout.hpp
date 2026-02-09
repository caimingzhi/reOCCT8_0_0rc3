#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <Standard_OStream.hpp>

class math_Crout
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_Crout(const math_Matrix& A, const double MinPivot = 1.0e-20);

  bool IsDone() const;

  Standard_EXPORT void Solve(const math_Vector& B, math_Vector& X) const;

  const math_Matrix& Inverse() const;

  void Invert(math_Matrix& Inv) const;

  double Determinant() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  math_Matrix InvA;
  bool        Done;
  double      Det;
};

#include <StdFail_NotDone.hpp>

inline bool math_Crout::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_Crout& C)
{
  C.Dump(o);
  return o;
}

inline double math_Crout::Determinant() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return Det;
}

inline const math_Matrix& math_Crout::Inverse() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return InvA;
}

inline void math_Crout::Invert(math_Matrix& Inv) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  Inv = InvA;
}
