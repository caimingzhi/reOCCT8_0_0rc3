#pragma once


#include <Standard.hpp>

#include <Standard_Type.hpp>
#include <XmlMDF_ADriver.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Boolean.hpp>
#include <TCollection_AsciiString.hpp>
class XmlMDF_ADriver;

//! A driver table is an object building links between
//! object types and object drivers. In the
//! translation process, a driver table is asked to
//! give a translation driver for each current object
//! to be translated.
class XmlMDF_ADriverTable : public Standard_Transient
{

public:
  //! Creates a mutable ADriverTable from XmlMDF.
  Standard_EXPORT XmlMDF_ADriverTable();

  //! Sets a translation driver: <aDriver>.
  Standard_EXPORT void AddDriver(const occ::handle<XmlMDF_ADriver>& anHDriver);

  //! Adds a translation driver for the derived attribute. The base driver must be already added.
  //! @param theInstance is newly created attribute, detached from any label
  Standard_EXPORT void AddDerivedDriver(const occ::handle<TDF_Attribute>& theInstance);

  //! Adds a translation driver for the derived attribute. The base driver must be already added.
  //! @param theDerivedType is registered attribute type using IMPLEMENT_DERIVED_ATTRIBUTE macro
  Standard_EXPORT const occ::handle<Standard_Type>& AddDerivedDriver(const char* theDerivedType);

  //! Fills the map by all registered drivers.
  Standard_EXPORT void CreateDrvMap(
    NCollection_DataMap<TCollection_AsciiString, occ::handle<XmlMDF_ADriver>>& theDriverMap);

  //! Gets a driver <aDriver> according to <aType>
  //!
  //! Returns True if a driver is found; false otherwise.
  Standard_EXPORT bool GetDriver(const occ::handle<Standard_Type>& theType,
                                 occ::handle<XmlMDF_ADriver>&      theDriver);

  DEFINE_STANDARD_RTTIEXT(XmlMDF_ADriverTable, Standard_Transient)

private:
  NCollection_DataMap<occ::handle<Standard_Type>, occ::handle<XmlMDF_ADriver>> myMap;
};

