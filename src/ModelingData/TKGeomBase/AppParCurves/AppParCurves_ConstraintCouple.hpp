#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AppParCurves_Constraint.hpp>

class AppParCurves_ConstraintCouple
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AppParCurves_ConstraintCouple();

  Standard_EXPORT AppParCurves_ConstraintCouple(const int                     TheIndex,
                                                const AppParCurves_Constraint Cons);

  Standard_EXPORT int Index() const;

  Standard_EXPORT AppParCurves_Constraint Constraint() const;

  Standard_EXPORT void SetIndex(const int TheIndex);

  Standard_EXPORT void SetConstraint(const AppParCurves_Constraint Cons);

private:
  int                     myIndex;
  AppParCurves_Constraint myConstraint;
};
