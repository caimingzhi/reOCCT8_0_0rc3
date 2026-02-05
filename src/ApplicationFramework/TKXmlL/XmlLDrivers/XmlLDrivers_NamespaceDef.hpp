#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_AsciiString.hpp>

class XmlLDrivers_NamespaceDef
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT XmlLDrivers_NamespaceDef();

  Standard_EXPORT XmlLDrivers_NamespaceDef(const TCollection_AsciiString& thePrefix,
                                           const TCollection_AsciiString& theURI);

  Standard_EXPORT const TCollection_AsciiString& Prefix() const;

  Standard_EXPORT const TCollection_AsciiString& URI() const;

private:
  TCollection_AsciiString myPrefix;
  TCollection_AsciiString myURI;
};
