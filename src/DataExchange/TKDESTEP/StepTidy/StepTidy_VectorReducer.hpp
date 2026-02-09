#pragma once

#include <StepTidy_EntityReducer.hpp>
#include <StepTidy_VectorHasher.hpp>

#include <StepGeom_Vector.hpp>

class StepTidy_VectorReducer : public StepTidy_EntityReducer<StepGeom_Vector, StepTidy_VectorHasher>
{
public:
  Standard_EXPORT StepTidy_VectorReducer(const occ::handle<XSControl_WorkSession>& theWS);

private:
  static bool replaceLine(const occ::handle<StepGeom_Vector>&    theOldEntity,
                          const occ::handle<StepGeom_Vector>&    theNewEntity,
                          const occ::handle<Standard_Transient>& theSharing);
};
