#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <XmlLDrivers_DocumentStorageDriver.hpp>
#include <XmlObjMgt_Element.hpp>
class TCollection_ExtendedString;
class XmlMDF_ADriverTable;
class Message_Messenger;

class XmlDrivers_DocumentStorageDriver : public XmlLDrivers_DocumentStorageDriver
{
public:
  Standard_EXPORT XmlDrivers_DocumentStorageDriver(const TCollection_ExtendedString& theCopyright);

  Standard_EXPORT occ::handle<XmlMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

  Standard_EXPORT bool WriteShapeSection(
    XmlObjMgt_Element&           thePDoc,
    const TDocStd_FormatVersion  theStorageFormatVersion,
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  DEFINE_STANDARD_RTTIEXT(XmlDrivers_DocumentStorageDriver, XmlLDrivers_DocumentStorageDriver)
};
