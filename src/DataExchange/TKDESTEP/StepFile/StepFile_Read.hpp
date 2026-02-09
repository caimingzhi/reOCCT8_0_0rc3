#pragma once

#include <Standard_CString.hpp>
#include <Standard_Type.hpp>

#include <iostream>

class StepData_StepModel;
class StepData_Protocol;

void StepFile_Interrupt(const char* theErrorMessage, const bool theIsFail = true);

Standard_EXPORT int StepFile_Read(const char*                            theName,
                                  std::istream*                          theIStream,
                                  const occ::handle<StepData_StepModel>& theModel,
                                  const occ::handle<StepData_Protocol>&  theProtocol);
