

#include <StepTidy_DirectionReducer.hpp>

#include <Interface_Graph.hpp>
#include <StepGeom_Axis1Placement.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_Vector.hpp>

StepTidy_DirectionReducer::StepTidy_DirectionReducer(
  const occ::handle<XSControl_WorkSession>& theWS)
    : StepTidy_EntityReducer<StepGeom_Direction, StepTidy_DirectionHasher>(theWS)
{
  registerReplacer(STANDARD_TYPE(StepGeom_Axis1Placement), replaceAxis1Placement);
  registerReplacer(STANDARD_TYPE(StepGeom_Axis2Placement3d), replaceAxis2Placement3d);
  registerReplacer(STANDARD_TYPE(StepGeom_Vector), replaceVector);
}

bool StepTidy_DirectionReducer::replaceAxis1Placement(
  const occ::handle<StepGeom_Direction>& theOldEntity,
  const occ::handle<StepGeom_Direction>& theNewEntity,
  const occ::handle<Standard_Transient>& theSharing)
{
  occ::handle<StepGeom_Axis1Placement> aSharing =
    occ::down_cast<StepGeom_Axis1Placement>(theSharing);
  if (aSharing->Axis() == theOldEntity)
  {
    aSharing->SetAxis(theNewEntity);
    return true;
  }
  return false;
}

bool StepTidy_DirectionReducer::replaceAxis2Placement3d(
  const occ::handle<StepGeom_Direction>& theOldEntity,
  const occ::handle<StepGeom_Direction>& theNewEntity,
  const occ::handle<Standard_Transient>& theSharing)
{
  occ::handle<StepGeom_Axis2Placement3d> aSharing =
    occ::down_cast<StepGeom_Axis2Placement3d>(theSharing);
  if (aSharing->Axis() == theOldEntity)
  {
    aSharing->SetAxis(theNewEntity);
    return true;
  }
  else if (aSharing->RefDirection() == theOldEntity)
  {
    aSharing->SetRefDirection(theNewEntity);
    return true;
  }
  return false;
}

bool StepTidy_DirectionReducer::replaceVector(const occ::handle<StepGeom_Direction>& theOldEntity,
                                              const occ::handle<StepGeom_Direction>& theNewEntity,
                                              const occ::handle<Standard_Transient>& theSharing)
{
  occ::handle<StepGeom_Vector> aSharing = occ::down_cast<StepGeom_Vector>(theSharing);
  if (aSharing->Orientation() == theOldEntity)
  {
    aSharing->SetOrientation(theNewEntity);
    return true;
  }
  return false;
}
