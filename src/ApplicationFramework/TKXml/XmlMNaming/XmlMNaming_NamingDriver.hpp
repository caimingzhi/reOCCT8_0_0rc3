#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <XmlMDF_ADriver.hpp>
#include <XmlObjMgt_RRelocationTable.hpp>
#include <XmlObjMgt_SRelocationTable.hpp>
class Message_Messenger;
class TDF_Attribute;
class XmlObjMgt_Persistent;

class XmlMNaming_NamingDriver : public XmlMDF_ADriver
{

public:
  Standard_EXPORT XmlMNaming_NamingDriver(const occ::handle<Message_Messenger>& aMessageDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const XmlObjMgt_Persistent&       theSource,
                             const occ::handle<TDF_Attribute>& theTarget,
                             XmlObjMgt_RRelocationTable&       theRelocTable) const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>& theSource,
                             XmlObjMgt_Persistent&             theTarget,
                             XmlObjMgt_SRelocationTable&       theRelocTable) const override;

  DEFINE_STANDARD_RTTIEXT(XmlMNaming_NamingDriver, XmlMDF_ADriver)
};
