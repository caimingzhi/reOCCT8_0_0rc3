#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AppParCurves_Constraint.hpp>

//! associates an index and a constraint for an object.
//! This couple is used by AppDef_TheVariational when performing approximations.
class AppParCurves_ConstraintCouple
{
public:
  DEFINE_STANDARD_ALLOC

  //! returns an indefinite ConstraintCouple.
  Standard_EXPORT AppParCurves_ConstraintCouple();

  //! Create a couple the object <Index> will have the
  //! constraint <Cons>.
  Standard_EXPORT AppParCurves_ConstraintCouple(const int                     TheIndex,
                                                const AppParCurves_Constraint Cons);

  //! returns the index of the constraint object.
  Standard_EXPORT int Index() const;

  //! returns the constraint of the object.
  Standard_EXPORT AppParCurves_Constraint Constraint() const;

  //! Changes the index of the constraint object.
  Standard_EXPORT void SetIndex(const int TheIndex);

  //! Changes the constraint of the object.
  Standard_EXPORT void SetConstraint(const AppParCurves_Constraint Cons);

private:
  int                     myIndex;
  AppParCurves_Constraint myConstraint;
};
