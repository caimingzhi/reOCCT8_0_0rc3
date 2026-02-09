#pragma once

#include <Standard.hpp>

#include <Standard_Type.hpp>
#include <XmlMDF_ADriver.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Boolean.hpp>
#include <TCollection_AsciiString.hpp>
class XmlMDF_ADriver;

class XmlMDF_ADriverTable : public Standard_Transient
{

public:
  Standard_EXPORT XmlMDF_ADriverTable();

  Standard_EXPORT void AddDriver(const occ::handle<XmlMDF_ADriver>& anHDriver);

  Standard_EXPORT void AddDerivedDriver(const occ::handle<TDF_Attribute>& theInstance);

  Standard_EXPORT const occ::handle<Standard_Type>& AddDerivedDriver(const char* theDerivedType);

  Standard_EXPORT void CreateDrvMap(
    NCollection_DataMap<TCollection_AsciiString, occ::handle<XmlMDF_ADriver>>& theDriverMap);

  Standard_EXPORT bool GetDriver(const occ::handle<Standard_Type>& theType,
                                 occ::handle<XmlMDF_ADriver>&      theDriver);

  DEFINE_STANDARD_RTTIEXT(XmlMDF_ADriverTable, Standard_Transient)

private:
  NCollection_DataMap<occ::handle<Standard_Type>, occ::handle<XmlMDF_ADriver>> myMap;
};
