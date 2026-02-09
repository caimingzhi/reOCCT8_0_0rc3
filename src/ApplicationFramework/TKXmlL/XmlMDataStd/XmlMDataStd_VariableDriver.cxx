#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_Variable.hpp>
#include <TDF_Attribute.hpp>
#include <XmlMDataStd_VariableDriver.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDataStd_VariableDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(IsConstString, "isconst")
IMPLEMENT_DOMSTRING(UnitString, "unit")
IMPLEMENT_DOMSTRING(ConstString, "true")

XmlMDataStd_VariableDriver::XmlMDataStd_VariableDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDataStd_VariableDriver::NewEmpty() const
{
  return (new TDataStd_Variable());
}

bool XmlMDataStd_VariableDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                       const occ::handle<TDF_Attribute>& theTarget,
                                       XmlObjMgt_RRelocationTable&) const
{
  occ::handle<TDataStd_Variable> aV = occ::down_cast<TDataStd_Variable>(theTarget);

  XmlObjMgt_DOMString aStr = theSource.Element().getAttribute(::IsConstString());
  aV->Constant(aStr != nullptr);

  aStr = theSource.Element().getAttribute(::UnitString());
  aV->Unit(aStr);
  return true;
}

void XmlMDataStd_VariableDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                       XmlObjMgt_Persistent&             theTarget,
                                       XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TDataStd_Variable> aV = occ::down_cast<TDataStd_Variable>(theSource);
  if (aV->IsConstant())
    theTarget.Element().setAttribute(::IsConstString(), ::ConstString());
  theTarget.Element().setAttribute(::UnitString(), aV->Unit().ToCString());
}
