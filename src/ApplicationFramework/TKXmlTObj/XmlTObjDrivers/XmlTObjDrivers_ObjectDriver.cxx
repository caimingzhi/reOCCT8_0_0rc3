#include <Message_Messenger.hpp>
#include "XmlTObjDrivers_ObjectDriver.hpp"
#include <TObj_TObject.hpp>
#include <TObj_Persistence.hpp>
#include <XmlObjMgt_Persistent.hpp>
#include <XmlObjMgt_RRelocationTable.hpp>
#include <XmlObjMgt.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlTObjDrivers_ObjectDriver, XmlMDF_ADriver)

//=================================================================================================

XmlTObjDrivers_ObjectDriver::XmlTObjDrivers_ObjectDriver(
  const occ::handle<Message_Messenger>& theMessageDriver)
    : XmlMDF_ADriver(theMessageDriver, nullptr)
{
}

//=======================================================================
// function : NewEmpty
// purpose  : Creates a new attribute
//=======================================================================

occ::handle<TDF_Attribute> XmlTObjDrivers_ObjectDriver::NewEmpty() const
{
  return new TObj_TObject;
}

//=======================================================================
// function : Paste
// purpose  : Translate the contents of <aSource> and put it
//           into <aTarget>, using the relocation table
//           <aRelocTable> to keep the sharings.
//=======================================================================

bool XmlTObjDrivers_ObjectDriver::Paste(const XmlObjMgt_Persistent&       Source,
                                        const occ::handle<TDF_Attribute>& Target,
                                        XmlObjMgt_RRelocationTable& /*RelocTable*/) const
{
  TCollection_ExtendedString aString;
  if (XmlObjMgt::GetExtendedString(Source, aString))
  {
    TCollection_AsciiString  anAscii(aString);
    occ::handle<TObj_Object> anObject =
      TObj_Persistence::CreateNewObject(anAscii.ToCString(), Target->Label());
    occ::down_cast<TObj_TObject>(Target)->Set(anObject);
    return true;
  }
  myMessageDriver->Send("error retrieving ExtendedString for type TObj_TModel", Message_Fail);
  return false;
}

//=======================================================================
// function : Paste
// purpose  : Translate the contents of <aSource> and put it
//           into <aTarget>, using the relocation table
//           <aRelocTable> to keep the sharings.
//           anObject is stored as a Name of class derived from TObj_Object
//=======================================================================

void XmlTObjDrivers_ObjectDriver::Paste(const occ::handle<TDF_Attribute>& Source,
                                        XmlObjMgt_Persistent&             Target,
                                        XmlObjMgt_SRelocationTable& /*RelocTable*/) const
{
  occ::handle<TObj_TObject> aTObj     = occ::down_cast<TObj_TObject>(Source);
  occ::handle<TObj_Object>  anIObject = aTObj->Get();

  XmlObjMgt::SetExtendedString(Target, anIObject->DynamicType()->Name());
}
