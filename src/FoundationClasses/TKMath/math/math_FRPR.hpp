#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_Vector.hpp>
#include <math_Status.hpp>
#include <Standard_OStream.hpp>
class math_MultipleVarFunctionWithGradient;

class math_FRPR
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_FRPR(const math_MultipleVarFunctionWithGradient& theFunction,
                            const double                                theTolerance,
                            const int                                   theNbIterations = 200,
                            const double                                theZEPS         = 1.0e-12);

  Standard_EXPORT virtual ~math_FRPR();

  Standard_EXPORT void Perform(math_MultipleVarFunctionWithGradient& theFunction,
                               const math_Vector&                    theStartingPoint);

  virtual bool IsSolutionReached(math_MultipleVarFunctionWithGradient& theFunction);

  bool IsDone() const;

  const math_Vector& Location() const;

  void Location(math_Vector& Loc) const;

  double Minimum() const;

  const math_Vector& Gradient() const;

  void Gradient(math_Vector& Grad) const;

  int NbIterations() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

protected:
  math_Vector TheLocation;
  math_Vector TheGradient;
  double      TheMinimum;
  double      PreviousMinimum;
  double      XTol;
  double      EPSZ;

private:
  bool        Done;
  int         Iter;
  int         State;
  math_Status TheStatus;
  int         Itermax;
};

#include <StdFail_NotDone.hpp>
#include <math_Vector.hpp>

inline bool math_FRPR::IsSolutionReached(math_MultipleVarFunctionWithGradient&)
{
  return 2.0 * fabs(TheMinimum - PreviousMinimum)
         <= XTol * (fabs(TheMinimum) + fabs(PreviousMinimum) + EPSZ);
}

inline bool math_FRPR::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_FRPR& Fr)
{
  Fr.Dump(o);
  return o;
}

inline const math_Vector& math_FRPR::Location() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheLocation;
}

inline void math_FRPR::Location(math_Vector& Loc) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  Loc = TheLocation;
}

inline const math_Vector& math_FRPR::Gradient() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheGradient;
}

inline void math_FRPR::Gradient(math_Vector& Grad) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  Grad = TheGradient;
}

inline double math_FRPR::Minimum() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheMinimum;
}

inline int math_FRPR::NbIterations() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return Iter;
}
