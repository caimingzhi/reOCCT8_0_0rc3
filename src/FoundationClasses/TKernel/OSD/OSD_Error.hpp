#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_AsciiString.hpp>
#include <OSD_WhoAmI.hpp>

//! Accurate management of OSD specific errors.
class OSD_Error
{
public:
  DEFINE_STANDARD_ALLOC

  //! Initializes Error to be without any Error.
  //! This is only used by OSD, not by programmer.
  Standard_EXPORT OSD_Error();

  //! Raises OSD_Error with accurate error message.
  Standard_EXPORT void Perror();

  //! Instantiates error
  //! This is only used by OSD methods to instantiates an error code.
  //! No description is done for the programmer.
  Standard_EXPORT void SetValue(const int                      Errcode,
                                const int                      From,
                                const TCollection_AsciiString& Message);

  //! Returns an accurate error code.
  //! To test these values, you must include "OSD_ErrorList.hpp"
  Standard_EXPORT int Error() const;

  //! Returns TRUE if an error occurs
  //! This is a way to test if a system call succeeded or not.
  Standard_EXPORT bool Failed() const;

  //! Resets error counter to zero
  //! This allows the user to ignore an error (WARNING).
  Standard_EXPORT void Reset();

private:
  TCollection_AsciiString myMessage;
  int                     myErrno;
  OSD_WhoAmI              myCode;
  int                     extCode{};
};

