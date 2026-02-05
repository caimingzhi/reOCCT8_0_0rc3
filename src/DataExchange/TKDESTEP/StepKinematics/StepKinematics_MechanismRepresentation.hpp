#pragma once

#include <Standard.hpp>
#include <StepRepr_Representation.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepKinematics_KinematicTopologyRepresentationSelect.hpp>

//! Representation of STEP entity MechanismRepresentation
class StepKinematics_MechanismRepresentation : public StepRepr_Representation
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_MechanismRepresentation();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theRepresentation_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                                theRepresentation_Items,
    const occ::handle<StepRepr_RepresentationContext>&          theRepresentation_ContextOfItems,
    const StepKinematics_KinematicTopologyRepresentationSelect& theRepresentedTopology);

  //! Returns field RepresentedTopology
  Standard_EXPORT StepKinematics_KinematicTopologyRepresentationSelect RepresentedTopology() const;
  //! Sets field RepresentedTopology
  Standard_EXPORT void SetRepresentedTopology(
    const StepKinematics_KinematicTopologyRepresentationSelect& theRepresentedTopology);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_MechanismRepresentation, StepRepr_Representation)

private:
  StepKinematics_KinematicTopologyRepresentationSelect myRepresentedTopology;
};
