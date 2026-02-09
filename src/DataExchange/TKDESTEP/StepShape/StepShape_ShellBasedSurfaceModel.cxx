

#include <StepShape_ShellBasedSurfaceModel.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_ShellBasedSurfaceModel, StepGeom_GeometricRepresentationItem)

StepShape_ShellBasedSurfaceModel::StepShape_ShellBasedSurfaceModel() = default;

void StepShape_ShellBasedSurfaceModel::Init(
  const occ::handle<TCollection_HAsciiString>&             aName,
  const occ::handle<NCollection_HArray1<StepShape_Shell>>& aSbsmBoundary)
{

  sbsmBoundary = aSbsmBoundary;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_ShellBasedSurfaceModel::SetSbsmBoundary(
  const occ::handle<NCollection_HArray1<StepShape_Shell>>& aSbsmBoundary)
{
  sbsmBoundary = aSbsmBoundary;
}

occ::handle<NCollection_HArray1<StepShape_Shell>> StepShape_ShellBasedSurfaceModel::SbsmBoundary()
  const
{
  return sbsmBoundary;
}

StepShape_Shell StepShape_ShellBasedSurfaceModel::SbsmBoundaryValue(const int num) const
{
  return sbsmBoundary->Value(num);
}

int StepShape_ShellBasedSurfaceModel::NbSbsmBoundary() const
{
  return sbsmBoundary->Length();
}
