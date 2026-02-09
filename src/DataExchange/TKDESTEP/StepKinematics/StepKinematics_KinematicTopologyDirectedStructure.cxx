

#include <StepKinematics_KinematicTopologyDirectedStructure.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_KinematicTopologyDirectedStructure,
                           StepRepr_Representation)

StepKinematics_KinematicTopologyDirectedStructure::
  StepKinematics_KinematicTopologyDirectedStructure() = default;

void StepKinematics_KinematicTopologyDirectedStructure::Init(
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
  StepKinematics_KinematicTopologyDirectedStructure::Parent() const
{
  return myParent;
}

void StepKinematics_KinematicTopologyDirectedStructure::SetParent(
  const occ::handle<StepKinematics_KinematicTopologyStructure>& theParent)
{
  myParent = theParent;
}
