#include "XmlTObjDrivers_ModelDriver.hpp"

#include <XmlObjMgt_Persistent.hpp>
#include <XmlObjMgt_RRelocationTable.hpp>
#include <XmlObjMgt.hpp>
#include <Standard_GUID.hpp>

#include <TObj_TModel.hpp>
#include <TObj_Model.hpp>
#include <TObj_Assistant.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlTObjDrivers_ModelDriver, XmlMDF_ADriver)

XmlTObjDrivers_ModelDriver::XmlTObjDrivers_ModelDriver(
  const occ::handle<Message_Messenger>& theMessageDriver)
    : XmlMDF_ADriver(theMessageDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlTObjDrivers_ModelDriver::NewEmpty() const
{
  return new TObj_TModel;
}

bool XmlTObjDrivers_ModelDriver::Paste(const XmlObjMgt_Persistent&       Source,
                                       const occ::handle<TDF_Attribute>& Target,
                                       XmlObjMgt_RRelocationTable&) const
{
  TCollection_ExtendedString aString;
  if (XmlObjMgt::GetExtendedString(Source, aString))
  {
    Standard_GUID           aGUID(aString.ToExtString());
    occ::handle<TObj_Model> aCurrentModel = TObj_Assistant::GetCurrentModel();
    if (aGUID == aCurrentModel->GetGUID())
    {
      occ::handle<TObj_TModel> aTModel = occ::down_cast<TObj_TModel>(Target);
      aCurrentModel->SetLabel(aTModel->Label());
      aTModel->Set(aCurrentModel);
      return true;
    }
    myMessageDriver->Send("TObj_TModel retrieval: wrong model GUID", Message_Fail);
    return false;
  }
  myMessageDriver->Send("error retrieving ExtendedString for type TObj_TModel", Message_Fail);
  return false;
}

void XmlTObjDrivers_ModelDriver::Paste(const occ::handle<TDF_Attribute>& Source,
                                       XmlObjMgt_Persistent&             Target,
                                       XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TObj_TModel> aTModel = occ::down_cast<TObj_TModel>(Source);
  occ::handle<TObj_Model>  aModel  = aTModel->Model();

  Standard_PCharacter aPGuidString = new char[256];
  aModel->GetGUID().ToCString(aPGuidString);
  XmlObjMgt::SetExtendedString(Target, aPGuidString);
  delete[] aPGuidString;
}
