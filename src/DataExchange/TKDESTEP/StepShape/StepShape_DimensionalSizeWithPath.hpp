#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_DimensionalSize.hpp>
class StepRepr_ShapeAspect;
class TCollection_HAsciiString;

class StepShape_DimensionalSizeWithPath : public StepShape_DimensionalSize
{

public:
  Standard_EXPORT StepShape_DimensionalSizeWithPath();

  Standard_EXPORT void Init(const occ::handle<StepRepr_ShapeAspect>&     aDimensionalSize_AppliesTo,
                            const occ::handle<TCollection_HAsciiString>& aDimensionalSize_Name,
                            const occ::handle<StepRepr_ShapeAspect>&     aPath);

  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> Path() const;

  Standard_EXPORT void SetPath(const occ::handle<StepRepr_ShapeAspect>& Path);

  DEFINE_STANDARD_RTTIEXT(StepShape_DimensionalSizeWithPath, StepShape_DimensionalSize)

private:
  occ::handle<StepRepr_ShapeAspect> thePath;
};
