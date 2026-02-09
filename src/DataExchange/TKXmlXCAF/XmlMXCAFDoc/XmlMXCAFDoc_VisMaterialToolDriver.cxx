

#include <XmlMXCAFDoc_VisMaterialToolDriver.hpp>

#include <Message_Messenger.hpp>
#include <XCAFDoc_VisMaterialTool.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMXCAFDoc_VisMaterialToolDriver, XmlMDF_ADriver)

XmlMXCAFDoc_VisMaterialToolDriver::XmlMXCAFDoc_VisMaterialToolDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, "xcaf", "VisMaterialTool")
{
}

occ::handle<TDF_Attribute> XmlMXCAFDoc_VisMaterialToolDriver::NewEmpty() const
{
  return new XCAFDoc_VisMaterialTool();
}

bool XmlMXCAFDoc_VisMaterialToolDriver::Paste(const XmlObjMgt_Persistent&,
                                              const occ::handle<TDF_Attribute>&,
                                              XmlObjMgt_RRelocationTable&) const
{
  return true;
}

void XmlMXCAFDoc_VisMaterialToolDriver::Paste(const occ::handle<TDF_Attribute>&,
                                              XmlObjMgt_Persistent&,
                                              XmlObjMgt_SRelocationTable&) const
{
}
