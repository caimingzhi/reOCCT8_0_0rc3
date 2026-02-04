#pragma once


#include <Standard.hpp>
#include <StepKinematics_KinematicPropertyDefinitionRepresentation.hpp>

#include <StepRepr_RepresentedDefinition.hpp>
#include <StepRepr_Representation.hpp>
#include <StepKinematics_KinematicLinkRepresentation.hpp>

//! Representation of STEP entity KinematicPropertyMechanismRepresentation
class StepKinematics_KinematicPropertyMechanismRepresentation
    : public StepKinematics_KinematicPropertyDefinitionRepresentation
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_KinematicPropertyMechanismRepresentation();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const StepRepr_RepresentedDefinition& thePropertyDefinitionRepresentation_Definition,
    const occ::handle<StepRepr_Representation>&
      thePropertyDefinitionRepresentation_UsedRepresentation,
    const occ::handle<StepKinematics_KinematicLinkRepresentation>& theBase);

  //! Returns field Base
  Standard_EXPORT occ::handle<StepKinematics_KinematicLinkRepresentation> Base() const;
  //! Sets field Base
  Standard_EXPORT void SetBase(
    const occ::handle<StepKinematics_KinematicLinkRepresentation>& theBase);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_KinematicPropertyMechanismRepresentation,
                          StepKinematics_KinematicPropertyDefinitionRepresentation)

private:
  occ::handle<StepKinematics_KinematicLinkRepresentation> myBase;
};
