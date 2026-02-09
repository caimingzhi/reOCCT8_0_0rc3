#pragma once

#include <Standard.hpp>

#include <StepRepr_RepresentationContext.hpp>
#include <StepKinematics_KinematicTopologyStructure.hpp>

class StepKinematics_KinematicTopologyDirectedStructure : public StepRepr_Representation
{
public:
  Standard_EXPORT StepKinematics_KinematicTopologyDirectedStructure();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theRepresentation_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                                  theRepresentation_Items,
    const occ::handle<StepRepr_RepresentationContext>&            theRepresentation_ContextOfItems,
    const occ::handle<StepKinematics_KinematicTopologyStructure>& theParent);

  Standard_EXPORT occ::handle<StepKinematics_KinematicTopologyStructure> Parent() const;

  Standard_EXPORT void SetParent(
    const occ::handle<StepKinematics_KinematicTopologyStructure>& theParent);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_KinematicTopologyDirectedStructure,
                          StepRepr_Representation)

private:
  occ::handle<StepKinematics_KinematicTopologyStructure> myParent;
};
