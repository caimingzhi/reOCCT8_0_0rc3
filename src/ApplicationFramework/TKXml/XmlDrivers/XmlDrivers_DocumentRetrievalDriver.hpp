#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <XmlLDrivers_DocumentRetrievalDriver.hpp>
#include <XmlObjMgt_Element.hpp>
#include <Standard_Integer.hpp>
class XmlMDF_ADriverTable;
class Message_Messenger;
class XmlMDF_ADriver;

class XmlDrivers_DocumentRetrievalDriver : public XmlLDrivers_DocumentRetrievalDriver
{
public:
  Standard_EXPORT XmlDrivers_DocumentRetrievalDriver();

  Standard_EXPORT occ::handle<XmlMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

  Standard_EXPORT occ::handle<XmlMDF_ADriver> ReadShapeSection(
    const XmlObjMgt_Element&              thePDoc,
    const occ::handle<Message_Messenger>& theMsgDriver,
    const Message_ProgressRange&          theRange = Message_ProgressRange()) override;

  Standard_EXPORT void ShapeSetCleaning(const occ::handle<XmlMDF_ADriver>& theDriver) override;

  DEFINE_STANDARD_RTTIEXT(XmlDrivers_DocumentRetrievalDriver, XmlLDrivers_DocumentRetrievalDriver)
};

