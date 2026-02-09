#pragma once

#include <StepTidy_EntityReducer.hpp>
#include <StepTidy_DirectionHasher.hpp>

#include <StepGeom_Direction.hpp>

class StepTidy_DirectionReducer
    : public StepTidy_EntityReducer<StepGeom_Direction, StepTidy_DirectionHasher>
{
public:
  Standard_EXPORT StepTidy_DirectionReducer(const occ::handle<XSControl_WorkSession>& theWS);

private:
  static bool replaceAxis1Placement(const occ::handle<StepGeom_Direction>& theOldEntity,
                                    const occ::handle<StepGeom_Direction>& theNewEntity,
                                    const occ::handle<Standard_Transient>& theSharing);

  static bool replaceAxis2Placement3d(const occ::handle<StepGeom_Direction>& theOldEntity,
                                      const occ::handle<StepGeom_Direction>& theNewEntity,
                                      const occ::handle<Standard_Transient>& theSharing);

  static bool replaceVector(const occ::handle<StepGeom_Direction>& theOldEntity,
                            const occ::handle<StepGeom_Direction>& theNewEntity,
                            const occ::handle<Standard_Transient>& theSharing);
};
