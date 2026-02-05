#include <AdvApp2Var_Criterion.hpp>

AdvApp2Var_Criterion::~AdvApp2Var_Criterion() = default;

//=================================================================================================

double AdvApp2Var_Criterion::MaxValue() const
{
  return myMaxValue;
}

//=================================================================================================

AdvApp2Var_CriterionType AdvApp2Var_Criterion::Type() const
{
  return myType;
}

//=================================================================================================

AdvApp2Var_CriterionRepartition AdvApp2Var_Criterion::Repartition() const
{
  return myRepartition;
}
