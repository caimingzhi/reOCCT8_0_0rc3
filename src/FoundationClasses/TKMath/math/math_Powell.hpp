#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_Vector.hpp>
#include <Standard_Integer.hpp>
#include <math_Status.hpp>
#include <math_Matrix.hpp>
#include <Standard_OStream.hpp>
class math_MultipleVarFunction;

class math_Powell
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_Powell(const math_MultipleVarFunction& theFunction,
                              const double                    theTolerance,
                              const int                       theNbIterations = 200,
                              const double                    theZEPS         = 1.0e-12);

  Standard_EXPORT virtual ~math_Powell();

  Standard_EXPORT void Perform(math_MultipleVarFunction& theFunction,
                               const math_Vector&        theStartingPoint,
                               const math_Matrix&        theStartingDirections);

  virtual bool IsSolutionReached(math_MultipleVarFunction& theFunction);

  bool IsDone() const;

  const math_Vector& Location() const;

  void Location(math_Vector& Loc) const;

  double Minimum() const;

  int NbIterations() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

protected:
  math_Vector TheLocation;
  double      TheMinimum;
  double      TheLocationError;
  double      PreviousMinimum;
  double      XTol;
  double      EPSZ;

private:
  bool        Done;
  int         Iter;
  math_Status TheStatus;
  math_Matrix TheDirections;
  int         State;
  int         Itermax;
};

#include <StdFail_NotDone.hpp>
#include <math_Vector.hpp>

inline bool math_Powell::IsSolutionReached(math_MultipleVarFunction&)
{
  return 2.0 * fabs(PreviousMinimum - TheMinimum)
         <= XTol * (fabs(PreviousMinimum) + fabs(TheMinimum) + EPSZ);
}

inline bool math_Powell::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_Powell& P)
{
  P.Dump(o);
  return o;
}

inline const math_Vector& math_Powell::Location() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheLocation;
}

inline void math_Powell::Location(math_Vector& Loc) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  Loc = TheLocation;
}

inline double math_Powell::Minimum() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheMinimum;
}

inline int math_Powell::NbIterations() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return Iter;
}
