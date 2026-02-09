

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
#include <StepRepr_FunctionallyDefinedTransformation.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepRepr_Transformation.hpp>

StepRepr_Transformation::StepRepr_Transformation() = default;

int StepRepr_Transformation::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ItemDefinedTransformation)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_FunctionallyDefinedTransformation)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_GeometricRepresentationItem)))
    return 1;
  return 0;
}

occ::handle<StepRepr_ItemDefinedTransformation> StepRepr_Transformation::ItemDefinedTransformation()
  const
{
  return GetCasted(StepRepr_ItemDefinedTransformation, Value());
}

occ::handle<StepRepr_FunctionallyDefinedTransformation> StepRepr_Transformation::
  FunctionallyDefinedTransformation() const
{
  return GetCasted(StepRepr_FunctionallyDefinedTransformation, Value());
}
