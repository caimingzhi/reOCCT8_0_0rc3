#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Status.hpp>
#include <math_Vector.hpp>
#include <Standard_OStream.hpp>
class math_MultipleVarFunctionWithGradient;

class math_BFGS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_BFGS(const int    NbVariables,
                            const double Tolerance    = 1.0e-8,
                            const int    NbIterations = 200,
                            const double ZEPS         = 1.0e-12);

  Standard_EXPORT virtual ~math_BFGS();

  Standard_EXPORT void SetBoundary(const math_Vector& theLeftBorder,
                                   const math_Vector& theRightBorder);

  Standard_EXPORT void Perform(math_MultipleVarFunctionWithGradient& F,
                               const math_Vector&                    StartingPoint);

  Standard_EXPORT virtual bool IsSolutionReached(math_MultipleVarFunctionWithGradient& F) const;

  bool IsDone() const;

  const math_Vector& Location() const;

  void Location(math_Vector& Loc) const;

  double Minimum() const;

  const math_Vector& Gradient() const;

  void Gradient(math_Vector& Grad) const;

  int NbIterations() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

protected:
  math_Status TheStatus;
  math_Vector TheLocation;
  math_Vector TheGradient;
  double      PreviousMinimum;
  double      TheMinimum;
  double      XTol;
  double      EPSZ;
  int         nbiter;
  bool        myIsBoundsDefined;
  math_Vector myLeft;
  math_Vector myRight;

private:
  bool Done;
  int  Itermax;
};

#include <StdFail_NotDone.hpp>
#include <math_Vector.hpp>

inline bool math_BFGS::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_BFGS& B)
{
  B.Dump(o);
  return o;
}

inline const math_Vector& math_BFGS::Location() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheLocation;
}

inline void math_BFGS::Location(math_Vector& Loc) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  Loc = TheLocation;
}

inline double math_BFGS::Minimum() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheMinimum;
}

inline const math_Vector& math_BFGS::Gradient() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheGradient;
}

inline void math_BFGS::Gradient(math_Vector& Grad) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  Grad = TheGradient;
}

inline int math_BFGS::NbIterations() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return nbiter;
}
