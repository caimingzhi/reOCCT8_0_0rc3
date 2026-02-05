#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_XY.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_XYZ.hpp>
#include <AdvApp2Var_Criterion.hpp>
#include <AdvApp2Var_CriterionType.hpp>
#include <AdvApp2Var_CriterionRepartition.hpp>
class AdvApp2Var_Patch;
class AdvApp2Var_Context;

//! this class contains a specific G0 criterion for GeomPlate_MakeApprox
class GeomPlate_PlateG0Criterion : public AdvApp2Var_Criterion
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomPlate_PlateG0Criterion(
    const NCollection_Sequence<gp_XY>&    Data,
    const NCollection_Sequence<gp_XYZ>&   G0Data,
    const double                          Maximum,
    const AdvApp2Var_CriterionType        Type   = AdvApp2Var_Absolute,
    const AdvApp2Var_CriterionRepartition Repart = AdvApp2Var_Regular);

  Standard_EXPORT void Value(AdvApp2Var_Patch& P, const AdvApp2Var_Context& C) const override;

  Standard_EXPORT bool IsSatisfied(const AdvApp2Var_Patch& P) const override;

private:
  NCollection_Sequence<gp_XY>  myData;
  NCollection_Sequence<gp_XYZ> myXYZ;
};
