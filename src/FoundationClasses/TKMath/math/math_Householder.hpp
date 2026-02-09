#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <Standard_OStream.hpp>

class math_Householder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_Householder(const math_Matrix& A,
                                   const math_Matrix& B,
                                   const double       EPS = 1.0e-20);

  Standard_EXPORT math_Householder(const math_Matrix& A,
                                   const math_Matrix& B,
                                   const int          lowerArow,
                                   const int          upperArow,
                                   const int          lowerAcol,
                                   const int          upperAcol,
                                   const double       EPS = 1.0e-20);

  Standard_EXPORT math_Householder(const math_Matrix& A,
                                   const math_Vector& B,
                                   const double       EPS = 1.0e-20);

  bool IsDone() const;

  void Value(math_Vector& sol, const int Index = 1) const;

  const math_Matrix& AllValues() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

protected:
  Standard_EXPORT void Perform(const math_Matrix& A, const math_Matrix& B, const double EPS);

private:
  math_Matrix Sol;
  math_Matrix Q;
  bool        Done;
  int         mylowerArow;
  int         myupperArow;
  int         mylowerAcol;
  int         myupperAcol;
};

#include <StdFail_NotDone.hpp>

inline bool math_Householder::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_Householder& H)
{
  H.Dump(o);
  return o;
}

inline void math_Householder::Value(math_Vector& sol, const int Index) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  Standard_OutOfRange_Raise_if((Index < 1) || (Index > Sol.ColNumber()), " ");
  sol = Sol.Col(Index);
}

inline const math_Matrix& math_Householder::AllValues() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return Sol;
}
