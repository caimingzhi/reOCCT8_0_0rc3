#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <math_Vector.hpp>
#include <math_IntegerVector.hpp>
#include <math_Matrix.hpp>
#include <Standard_OStream.hpp>
class math_FunctionSetWithDerivatives;

class math_NewtonFunctionSetRoot
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_NewtonFunctionSetRoot(math_FunctionSetWithDerivatives& theFunction,
                                             const math_Vector&               theXTolerance,
                                             const double                     theFTolerance,
                                             const int theNbIterations = 100);

  Standard_EXPORT math_NewtonFunctionSetRoot(math_FunctionSetWithDerivatives& theFunction,
                                             const double                     theFTolerance,
                                             const int theNbIterations = 100);

  Standard_EXPORT virtual ~math_NewtonFunctionSetRoot();

  Standard_EXPORT void SetTolerance(const math_Vector& XTol);

  Standard_EXPORT void Perform(math_FunctionSetWithDerivatives& theFunction,
                               const math_Vector&               theStartingPoint);

  Standard_EXPORT void Perform(math_FunctionSetWithDerivatives& theFunction,
                               const math_Vector&               theStartingPoint,
                               const math_Vector&               theInfBound,
                               const math_Vector&               theSupBound);

  virtual bool IsSolutionReached(math_FunctionSetWithDerivatives& F);

  bool IsDone() const;

  const math_Vector& Root() const;

  void Root(math_Vector& Root) const;

  int StateNumber() const;

  const math_Matrix& Derivative() const;

  void Derivative(math_Matrix& Der) const;

  const math_Vector& FunctionSetErrors() const;

  void FunctionSetErrors(math_Vector& Err) const;

  int NbIterations() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

protected:
  math_Vector        TolX;
  double             TolF;
  math_IntegerVector Indx;
  math_Vector        Scratch;
  math_Vector        Sol;
  math_Vector        DeltaX;
  math_Vector        FValues;
  math_Matrix        Jacobian;

private:
  bool Done;
  int  State;
  int  Iter;
  int  Itermax;
};

#include <StdFail_NotDone.hpp>

inline bool math_NewtonFunctionSetRoot::IsSolutionReached(math_FunctionSetWithDerivatives&)
{
  for (int i = DeltaX.Lower(); i <= DeltaX.Upper(); ++i)
    if (std::abs(DeltaX(i)) > TolX(i) || std::abs(FValues(i)) > TolF)
      return false;

  return true;
}

inline bool math_NewtonFunctionSetRoot::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_NewtonFunctionSetRoot& N)
{
  N.Dump(o);
  return o;
}

inline const math_Vector& math_NewtonFunctionSetRoot::Root() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return Sol;
}

inline void math_NewtonFunctionSetRoot::Root(math_Vector& Root) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  Root = Sol;
}

inline const math_Matrix& math_NewtonFunctionSetRoot::Derivative() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return Jacobian;
}

inline void math_NewtonFunctionSetRoot::Derivative(math_Matrix& Der) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  Der = Jacobian;
}

inline const math_Vector& math_NewtonFunctionSetRoot::FunctionSetErrors() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return DeltaX;
}

inline void math_NewtonFunctionSetRoot::FunctionSetErrors(math_Vector& Err) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  Err = DeltaX;
}

inline int math_NewtonFunctionSetRoot::NbIterations() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return Iter;
}
