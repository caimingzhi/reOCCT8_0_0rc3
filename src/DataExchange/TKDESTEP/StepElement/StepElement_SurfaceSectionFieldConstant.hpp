#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepElement_SurfaceSectionField.hpp>
class StepElement_SurfaceSection;

//! Representation of STEP entity SurfaceSectionFieldConstant
class StepElement_SurfaceSectionFieldConstant : public StepElement_SurfaceSectionField
{

public:
  //! Empty constructor
  Standard_EXPORT StepElement_SurfaceSectionFieldConstant();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<StepElement_SurfaceSection>& aDefinition);

  //! Returns field Definition
  Standard_EXPORT occ::handle<StepElement_SurfaceSection> Definition() const;

  //! Set field Definition
  Standard_EXPORT void SetDefinition(const occ::handle<StepElement_SurfaceSection>& Definition);

  DEFINE_STANDARD_RTTIEXT(StepElement_SurfaceSectionFieldConstant, StepElement_SurfaceSectionField)

private:
  occ::handle<StepElement_SurfaceSection> theDefinition;
};
