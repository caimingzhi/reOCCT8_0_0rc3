#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepElement_SurfaceSectionField.hpp>
class StepElement_SurfaceSection;

class StepElement_SurfaceSectionFieldConstant : public StepElement_SurfaceSectionField
{

public:
  Standard_EXPORT StepElement_SurfaceSectionFieldConstant();

  Standard_EXPORT void Init(const occ::handle<StepElement_SurfaceSection>& aDefinition);

  Standard_EXPORT occ::handle<StepElement_SurfaceSection> Definition() const;

  Standard_EXPORT void SetDefinition(const occ::handle<StepElement_SurfaceSection>& Definition);

  DEFINE_STANDARD_RTTIEXT(StepElement_SurfaceSectionFieldConstant, StepElement_SurfaceSectionField)

private:
  occ::handle<StepElement_SurfaceSection> theDefinition;
};
