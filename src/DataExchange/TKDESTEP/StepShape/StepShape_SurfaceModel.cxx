

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepShape_FaceBasedSurfaceModel.hpp>
#include <StepShape_ShellBasedSurfaceModel.hpp>
#include <StepShape_SurfaceModel.hpp>

StepShape_SurfaceModel::StepShape_SurfaceModel() = default;

int StepShape_SurfaceModel::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepShape_ShellBasedSurfaceModel)))
    return 1;

  return 0;
}

occ::handle<StepShape_ShellBasedSurfaceModel> StepShape_SurfaceModel::ShellBasedSurfaceModel() const
{
  return GetCasted(StepShape_ShellBasedSurfaceModel, Value());
}
