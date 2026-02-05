#pragma once

#include <Standard_CString.hpp>
#include <Standard_Type.hpp>

#include <iostream>

class StepData_StepModel;
class StepData_Protocol;

//! Prints the error message
//! @param theErrorMessage - error message for output
//! @param theFail - if true output as a fail info, else output as a trace info ( log )
void StepFile_Interrupt(const char* theErrorMessage, const bool theIsFail = true);

//! Working function reading STEP file or stream.
//! @param theName - name of the file or stream
//! @param theIStream - pointer to stream to read; if null, file theName will be opened
//! @param theModel - STEP model
//! @param theProtocol - STEP protocol object
//! @return 0 on success, -1 if stream fails, 1 in case of parsing error
Standard_EXPORT int StepFile_Read(const char*                            theName,
                                  std::istream*                          theIStream,
                                  const occ::handle<StepData_StepModel>& theModel,
                                  const occ::handle<StepData_Protocol>&  theProtocol);
