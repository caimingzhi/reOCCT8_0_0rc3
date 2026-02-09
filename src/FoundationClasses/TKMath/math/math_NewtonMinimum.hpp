#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Precision.hpp>
#include <math_Status.hpp>
#include <math_Vector.hpp>
#include <math_Matrix.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class math_MultipleVarFunctionWithHessian;

class math_NewtonMinimum
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_NewtonMinimum(const math_MultipleVarFunctionWithHessian& theFunction,
                                     const double theTolerance       = Precision::Confusion(),
                                     const int    theNbIterations    = 40,
                                     const double theConvexity       = 1.0e-6,
                                     const bool   theWithSingularity = true);

  Standard_EXPORT void Perform(math_MultipleVarFunctionWithHessian& theFunction,
                               const math_Vector&                   theStartingPoint);

  Standard_EXPORT virtual ~math_NewtonMinimum();

  virtual bool IsConverged() const;

  bool IsDone() const;

  bool IsConvex() const;

  const math_Vector& Location() const;

  void Location(math_Vector& Loc) const;

  Standard_EXPORT void SetBoundary(const math_Vector& theLeftBorder,
                                   const math_Vector& theRightBorder);

  double Minimum() const;

  const math_Vector& Gradient() const;

  void Gradient(math_Vector& Grad) const;

  int NbIterations() const;

  math_Status GetStatus() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

protected:
  math_Status TheStatus;
  math_Vector TheLocation;
  math_Vector TheGradient;
  math_Vector TheStep;
  math_Matrix TheHessian;
  double      PreviousMinimum;
  double      TheMinimum;
  double      MinEigenValue;
  double      XTol;
  double      CTol;
  int         nbiter;
  bool        NoConvexTreatement;
  bool        Convex;
  bool        myIsBoundsDefined;
  math_Vector myLeft;
  math_Vector myRight;

private:
  bool Done;
  int  Itermax;
};

#include <StdFail_NotDone.hpp>

inline bool math_NewtonMinimum::IsConverged() const
{
  return ((TheStep.Norm() <= XTol)
          || (std::abs(TheMinimum - PreviousMinimum) <= XTol * std::abs(PreviousMinimum)));
}

inline bool math_NewtonMinimum::IsDone() const
{
  return Done;
}

inline const math_Vector& math_NewtonMinimum::Location() const
{
  StdFail_NotDone_Raise_if(!Done, "NewtonMinimum");
  return TheLocation;
}

inline void math_NewtonMinimum::Location(math_Vector& Loc) const
{
  StdFail_NotDone_Raise_if(!Done, "NewtonMinimum");
  Loc = TheLocation;
}

inline double math_NewtonMinimum::Minimum() const
{
  StdFail_NotDone_Raise_if(!Done, "NewtonMinimum");
  return TheMinimum;
}

inline const math_Vector& math_NewtonMinimum::Gradient() const
{
  StdFail_NotDone_Raise_if(!Done, "NewtonMinimum");
  return TheGradient;
}

inline void math_NewtonMinimum::Gradient(math_Vector& Grad) const
{
  StdFail_NotDone_Raise_if(!Done, "NewtonMinimum");
  Grad = TheGradient;
}

inline int math_NewtonMinimum::NbIterations() const
{
  StdFail_NotDone_Raise_if(!Done, "NewtonMinimum");
  return nbiter;
}

inline math_Status math_NewtonMinimum::GetStatus() const
{
  return TheStatus;
}
