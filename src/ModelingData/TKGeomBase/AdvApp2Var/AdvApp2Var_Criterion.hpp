#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <AdvApp2Var_CriterionType.hpp>
#include <AdvApp2Var_CriterionRepartition.hpp>
#include <Standard_Boolean.hpp>
class AdvApp2Var_Patch;
class AdvApp2Var_Context;

//! this class contains a given criterion to be satisfied
class AdvApp2Var_Criterion
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual ~AdvApp2Var_Criterion();

  Standard_EXPORT virtual void Value(AdvApp2Var_Patch& P, const AdvApp2Var_Context& C) const = 0;

  Standard_EXPORT virtual bool IsSatisfied(const AdvApp2Var_Patch& P) const = 0;

  Standard_EXPORT double MaxValue() const;

  Standard_EXPORT AdvApp2Var_CriterionType Type() const;

  Standard_EXPORT AdvApp2Var_CriterionRepartition Repartition() const;

protected:
  double                          myMaxValue;
  AdvApp2Var_CriterionType        myType;
  AdvApp2Var_CriterionRepartition myRepartition;
};
