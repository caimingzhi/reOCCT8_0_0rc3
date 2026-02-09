#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_AsciiString.hpp>
#include <OSD_WhoAmI.hpp>

class OSD_Error
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT OSD_Error();

  Standard_EXPORT void Perror();

  Standard_EXPORT void SetValue(const int                      Errcode,
                                const int                      From,
                                const TCollection_AsciiString& Message);

  Standard_EXPORT int Error() const;

  Standard_EXPORT bool Failed() const;

  Standard_EXPORT void Reset();

private:
  TCollection_AsciiString myMessage;
  int                     myErrno;
  OSD_WhoAmI              myCode;
  int                     extCode{};
};
