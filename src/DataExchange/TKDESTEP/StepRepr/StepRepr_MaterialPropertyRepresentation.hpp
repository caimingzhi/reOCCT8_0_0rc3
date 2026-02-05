#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_PropertyDefinitionRepresentation.hpp>
class StepRepr_DataEnvironment;
class StepRepr_RepresentedDefinition;
class StepRepr_Representation;

//! Representation of STEP entity MaterialPropertyRepresentation
class StepRepr_MaterialPropertyRepresentation : public StepRepr_PropertyDefinitionRepresentation
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_MaterialPropertyRepresentation();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const StepRepr_RepresentedDefinition& aPropertyDefinitionRepresentation_Definition,
    const occ::handle<StepRepr_Representation>&
      aPropertyDefinitionRepresentation_UsedRepresentation,
    const occ::handle<StepRepr_DataEnvironment>& aDependentEnvironment);

  //! Returns field DependentEnvironment
  Standard_EXPORT occ::handle<StepRepr_DataEnvironment> DependentEnvironment() const;

  //! Set field DependentEnvironment
  Standard_EXPORT void SetDependentEnvironment(
    const occ::handle<StepRepr_DataEnvironment>& DependentEnvironment);

  DEFINE_STANDARD_RTTIEXT(StepRepr_MaterialPropertyRepresentation,
                          StepRepr_PropertyDefinitionRepresentation)

private:
  occ::handle<StepRepr_DataEnvironment> theDependentEnvironment;
};
