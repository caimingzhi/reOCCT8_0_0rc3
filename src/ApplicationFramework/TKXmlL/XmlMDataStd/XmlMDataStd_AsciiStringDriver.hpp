#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <XmlMDF_ADriver.hpp>
#include <XmlObjMgt_RRelocationTable.hpp>
#include <XmlObjMgt_SRelocationTable.hpp>
class Message_Messenger;
class TDF_Attribute;
class XmlObjMgt_Persistent;

//! TDataStd_AsciiString attribute Driver.
class XmlMDataStd_AsciiStringDriver : public XmlMDF_ADriver
{

public:
  Standard_EXPORT XmlMDataStd_AsciiStringDriver(
    const occ::handle<Message_Messenger>& theMessageDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  //! persistent -> transient (retrieve)
  Standard_EXPORT bool Paste(const XmlObjMgt_Persistent&       Source,
                             const occ::handle<TDF_Attribute>& Target,
                             XmlObjMgt_RRelocationTable&       RelocTable) const override;

  //! transient -> persistent (store)
  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>& Source,
                             XmlObjMgt_Persistent&             Target,
                             XmlObjMgt_SRelocationTable&       RelocTable) const override;

  DEFINE_STANDARD_RTTIEXT(XmlMDataStd_AsciiStringDriver, XmlMDF_ADriver)
};

