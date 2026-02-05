// Created on : Sat May 02 12:41:15 2020

#include <StepKinematics_MechanismRepresentation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_MechanismRepresentation, StepRepr_Representation)

//=================================================================================================

StepKinematics_MechanismRepresentation::StepKinematics_MechanismRepresentation() = default;

//=================================================================================================

void StepKinematics_MechanismRepresentation::Init(
  const occ::handle<TCollection_HAsciiString>& theRepresentation_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                              theRepresentation_Items,
  const occ::handle<StepRepr_RepresentationContext>&          theRepresentation_ContextOfItems,
  const StepKinematics_KinematicTopologyRepresentationSelect& theRepresentedTopology)
{
  StepRepr_Representation::Init(theRepresentation_Name,
                                theRepresentation_Items,
                                theRepresentation_ContextOfItems);

  myRepresentedTopology = theRepresentedTopology;
}

//=================================================================================================

StepKinematics_KinematicTopologyRepresentationSelect StepKinematics_MechanismRepresentation::
  RepresentedTopology() const
{
  return myRepresentedTopology;
}

//=================================================================================================

void StepKinematics_MechanismRepresentation::SetRepresentedTopology(
  const StepKinematics_KinematicTopologyRepresentationSelect& theRepresentedTopology)
{
  myRepresentedTopology = theRepresentedTopology;
}
