

#include <AppParCurves_ConstraintCouple.hpp>

AppParCurves_ConstraintCouple::AppParCurves_ConstraintCouple()
    : myIndex(-1),
      myConstraint(AppParCurves_NoConstraint)
{
}

AppParCurves_ConstraintCouple::AppParCurves_ConstraintCouple(const int                     TheIndex,
                                                             const AppParCurves_Constraint Cons)
{
  myIndex      = TheIndex;
  myConstraint = Cons;
}

int AppParCurves_ConstraintCouple::Index() const
{
  return myIndex;
}

AppParCurves_Constraint AppParCurves_ConstraintCouple::Constraint() const
{
  return myConstraint;
}

void AppParCurves_ConstraintCouple::SetIndex(const int TheIndex)
{
  myIndex = TheIndex;
}

void AppParCurves_ConstraintCouple::SetConstraint(const AppParCurves_Constraint Cons)
{
  myConstraint = Cons;
}
