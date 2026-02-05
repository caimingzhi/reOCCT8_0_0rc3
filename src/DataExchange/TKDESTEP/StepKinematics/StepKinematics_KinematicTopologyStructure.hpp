#pragma once

#include <Standard.hpp>
#include <StepRepr_Representation.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//! Representation of STEP entity KinematicTopologyStructure
class StepKinematics_KinematicTopologyStructure : public StepRepr_Representation
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_KinematicTopologyStructure();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_KinematicTopologyStructure, StepRepr_Representation)
};
