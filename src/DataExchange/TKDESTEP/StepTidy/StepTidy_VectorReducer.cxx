

#include <StepTidy_VectorReducer.hpp>

#include <Interface_Graph.hpp>
#include <StepGeom_Line.hpp>
#include <StepGeom_Vector.hpp>

StepTidy_VectorReducer::StepTidy_VectorReducer(const occ::handle<XSControl_WorkSession>& theWS)
    : StepTidy_EntityReducer<StepGeom_Vector, StepTidy_VectorHasher>(theWS)
{
  registerReplacer(STANDARD_TYPE(StepGeom_Line), replaceLine);
}

bool StepTidy_VectorReducer::replaceLine(const occ::handle<StepGeom_Vector>&    theOldEntity,
                                         const occ::handle<StepGeom_Vector>&    theNewEntity,
                                         const occ::handle<Standard_Transient>& theSharing)
{
  occ::handle<StepGeom_Line> aLine = occ::down_cast<StepGeom_Line>(theSharing);
  if (aLine->Dir() == theOldEntity)
  {
    aLine->SetDir(theNewEntity);
    return true;
  }
  return false;
}
