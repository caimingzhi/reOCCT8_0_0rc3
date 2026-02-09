#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <XmlObjMgt_Element.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <XmlMDF_ADriver.hpp>
#include <NCollection_DataMap.hpp>

#include <Message_ProgressRange.hpp>

class TDF_Data;
class XmlMDF_ADriverTable;
class TDF_Label;
class Message_Messenger;

class XmlMDF
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void FromTo(
    const occ::handle<TDF_Data>&            aSource,
    XmlObjMgt_Element&                      aTarget,
    XmlObjMgt_SRelocationTable&             aReloc,
    const occ::handle<XmlMDF_ADriverTable>& aDrivers,
    const Message_ProgressRange&            theRange = Message_ProgressRange());

  Standard_EXPORT static bool FromTo(
    const XmlObjMgt_Element&                aSource,
    occ::handle<TDF_Data>&                  aTarget,
    XmlObjMgt_RRelocationTable&             aReloc,
    const occ::handle<XmlMDF_ADriverTable>& aDrivers,
    const Message_ProgressRange&            theRange = Message_ProgressRange());

  Standard_EXPORT static void AddDrivers(const occ::handle<XmlMDF_ADriverTable>& aDriverTable,
                                         const occ::handle<Message_Messenger>&   theMessageDriver);

private:
  Standard_EXPORT static int WriteSubTree(
    const TDF_Label&                        theLabel,
    XmlObjMgt_Element&                      theElement,
    XmlObjMgt_SRelocationTable&             aReloc,
    const occ::handle<XmlMDF_ADriverTable>& aDrivers,
    const Message_ProgressRange&            theRange = Message_ProgressRange());

  Standard_EXPORT static int ReadSubTree(
    const XmlObjMgt_Element&                                                         theElement,
    const TDF_Label&                                                                 theLabel,
    XmlObjMgt_RRelocationTable&                                                      aReloc,
    const NCollection_DataMap<TCollection_AsciiString, occ::handle<XmlMDF_ADriver>>& aDrivers,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT static void CreateDrvMap(
    const occ::handle<XmlMDF_ADriverTable>&                                    aDriverTable,
    NCollection_DataMap<TCollection_AsciiString, occ::handle<XmlMDF_ADriver>>& anAsciiDriverMap);

  friend class XmlMDF_ADriver;
  friend class XmlMDF_TagSourceDriver;
  friend class XmlMDF_ReferenceDriver;
  friend class XmlMDF_ADriverTable;
};
