#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_AsciiString.hpp>
#include <OSD_Error.hpp>

class OSD_Environment
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT OSD_Environment();

  Standard_EXPORT OSD_Environment(const TCollection_AsciiString& Name);

  Standard_EXPORT OSD_Environment(const TCollection_AsciiString& Name,
                                  const TCollection_AsciiString& Value);

  Standard_EXPORT void SetValue(const TCollection_AsciiString& Value);

  Standard_EXPORT TCollection_AsciiString Value();

  Standard_EXPORT void SetName(const TCollection_AsciiString& name);

  Standard_EXPORT TCollection_AsciiString Name() const;

  Standard_EXPORT void Build();

  Standard_EXPORT void Remove();

  Standard_EXPORT bool Failed() const;

  Standard_EXPORT void Reset();

  Standard_EXPORT void Perror();

  Standard_EXPORT int Error() const;

private:
  TCollection_AsciiString myName;
  TCollection_AsciiString myValue;
  OSD_Error               myError;
};
