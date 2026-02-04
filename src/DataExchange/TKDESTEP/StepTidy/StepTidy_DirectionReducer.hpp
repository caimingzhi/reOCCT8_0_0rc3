#pragma once


#include <StepTidy_EntityReducer.hpp>
#include <StepTidy_DirectionHasher.hpp>

#include <StepGeom_Direction.hpp>

//! Processor for merging StepGeom_Direction entities.
//! This processor merges directions with the same direction ratios and names.
//! The processor replaces all occurrences of the old directions with the new ones.
//! The processor does not remove old directions from the model.
//! See StepTidy_EntityReducer for the description of the Reducer workflow.
class StepTidy_DirectionReducer
    : public StepTidy_EntityReducer<StepGeom_Direction, StepTidy_DirectionHasher>
{
public:
  //! Constructor. Stores the work session and registers replacer functions.
  //! @param theWS the work session.
  Standard_EXPORT StepTidy_DirectionReducer(const occ::handle<XSControl_WorkSession>& theWS);

private:
  //! Replaces the old direction with the new one in the StepGeom_Axis1Placement entity.
  //! @param theOldEntity the old direction.
  //! @param theNewEntity the new direction.
  //! @param theSharing the StepGeom_Axis1Placement entity to update.
  //! @return true if the direction was replaced, false otherwise.
  static bool replaceAxis1Placement(const occ::handle<StepGeom_Direction>& theOldEntity,
                                    const occ::handle<StepGeom_Direction>& theNewEntity,
                                    const occ::handle<Standard_Transient>& theSharing);

  //! Replaces the old direction with the new one in the StepGeom_Axis2Placement3d entity.
  //! @param theOldEntity the old direction.
  //! @param theNewEntity the new direction.
  //! @param theSharing the StepGeom_Axis2Placement3d entity to update.
  //! @return true if the direction was replaced, false otherwise.
  static bool replaceAxis2Placement3d(const occ::handle<StepGeom_Direction>& theOldEntity,
                                      const occ::handle<StepGeom_Direction>& theNewEntity,
                                      const occ::handle<Standard_Transient>& theSharing);

  //! Replaces the old direction with the new one in the StepGeom_Vector entity.
  //! @param theOldEntity the old direction.
  //! @param theNewEntity the new direction.
  //! @param theSharing the StepGeom_Vector entity to update.
  //! @return true if the direction was replaced, false otherwise.
  static bool replaceVector(const occ::handle<StepGeom_Direction>& theOldEntity,
                            const occ::handle<StepGeom_Direction>& theNewEntity,
                            const occ::handle<Standard_Transient>& theSharing);
};

