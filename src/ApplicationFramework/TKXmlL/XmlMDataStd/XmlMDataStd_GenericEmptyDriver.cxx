

#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_GenericEmpty.hpp>
#include <TDF_Attribute.hpp>
#include <XmlMDataStd_GenericEmptyDriver.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDataStd_GenericEmptyDriver, XmlMDF_ADriver)

XmlMDataStd_GenericEmptyDriver::XmlMDataStd_GenericEmptyDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDataStd_GenericEmptyDriver::NewEmpty() const
{
  return occ::handle<TDF_Attribute>();
}

occ::handle<Standard_Type> XmlMDataStd_GenericEmptyDriver::SourceType() const
{
  return Standard_Type::Instance<TDataStd_GenericEmpty>();
}

bool XmlMDataStd_GenericEmptyDriver::Paste(const XmlObjMgt_Persistent&,
                                           const occ::handle<TDF_Attribute>&,
                                           XmlObjMgt_RRelocationTable&) const
{
  return true;
}

void XmlMDataStd_GenericEmptyDriver::Paste(const occ::handle<TDF_Attribute>&,
                                           XmlObjMgt_Persistent&,
                                           XmlObjMgt_SRelocationTable&) const
{
}
