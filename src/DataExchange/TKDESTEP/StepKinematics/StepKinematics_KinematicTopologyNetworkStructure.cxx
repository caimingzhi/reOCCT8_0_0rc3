

#include <StepKinematics_KinematicTopologyNetworkStructure.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_KinematicTopologyNetworkStructure,
                           StepRepr_Representation)

StepKinematics_KinematicTopologyNetworkStructure::
  StepKinematics_KinematicTopologyNetworkStructure() = default;

void StepKinematics_KinematicTopologyNetworkStructure::Init(
  const occ::handle<TCollection_HAsciiString>& theRepresentation_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                                theRepresentation_Items,
  const occ::handle<StepRepr_RepresentationContext>&            theRepresentation_ContextOfItems,
  const occ::handle<StepKinematics_KinematicTopologyStructure>& theParent)
{
  StepRepr_Representation::Init(theRepresentation_Name,
                                theRepresentation_Items,
                                theRepresentation_ContextOfItems);

  myParent = theParent;
}

occ::handle<StepKinematics_KinematicTopologyStructure>
  StepKinematics_KinematicTopologyNetworkStructure::Parent() const
{
  return myParent;
}

void StepKinematics_KinematicTopologyNetworkStructure::SetParent(
  const occ::handle<StepKinematics_KinematicTopologyStructure>& theParent)
{
  myParent = theParent;
}
