#pragma once

#include <StepTidy_EntityReducer.hpp>
#include <StepTidy_VectorHasher.hpp>

#include <StepGeom_Vector.hpp>

//! Processor for merging StepGeom_Vector entities.
//! This processor merges vectors with the same orientation and magnitude and names.
class StepTidy_VectorReducer : public StepTidy_EntityReducer<StepGeom_Vector, StepTidy_VectorHasher>
{
public:
  //! Constructor. Stores the work session and registers replacer functions.
  //! @param theWS the work session.
  Standard_EXPORT StepTidy_VectorReducer(const occ::handle<XSControl_WorkSession>& theWS);

private:
  //! Replaces the old vector with the new one in the StepGeom_Line entity.
  //! @param theOldEntity the old vector.
  //! @param theNewEntity the new vector to replace the old one.
  //! @param theSharing the StepGeom_Line entity to update.
  //! @return true if the vector was replaced, false otherwise.
  static bool replaceLine(const occ::handle<StepGeom_Vector>&    theOldEntity,
                          const occ::handle<StepGeom_Vector>&    theNewEntity,
                          const occ::handle<Standard_Transient>& theSharing);
};
