#pragma once

#include <Standard_Transient.hpp>
#include <NCollection_Map.hpp>

class XSControl_WorkSession;

class StepTidy_DuplicateCleaner
{
public:
  Standard_EXPORT StepTidy_DuplicateCleaner(occ::handle<XSControl_WorkSession> theWS);

  Standard_EXPORT void Perform();

private:
  void removeEntities(const NCollection_Map<occ::handle<Standard_Transient>>& theToRemove);

private:
  occ::handle<XSControl_WorkSession> myWS;
};
