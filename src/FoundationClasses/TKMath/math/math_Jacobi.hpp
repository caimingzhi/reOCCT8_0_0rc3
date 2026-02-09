#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <Standard_OStream.hpp>

class math_Jacobi
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_Jacobi(const math_Matrix& A);

  bool IsDone() const;

  const math_Vector& Values() const;

  double Value(const int Num) const;

  const math_Matrix& Vectors() const;

  void Vector(const int Num, math_Vector& V) const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  bool        Done;
  math_Matrix AA;
  int         NbRotations;
  math_Vector EigenValues;
  math_Matrix EigenVectors;
};

#include <StdFail_NotDone.hpp>
#include <math_Vector.hpp>
#include <math_Matrix.hpp>

inline bool math_Jacobi::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_Jacobi& J)
{
  J.Dump(o);
  return o;
}

inline const math_Vector& math_Jacobi::Values() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return EigenValues;
}

inline double math_Jacobi::Value(const int Num) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return EigenValues(Num);
}

inline const math_Matrix& math_Jacobi::Vectors() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return EigenVectors;
}

inline void math_Jacobi::Vector(const int Num, math_Vector& V) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  V = EigenVectors.Col(Num);
}
