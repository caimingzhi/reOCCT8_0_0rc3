#include "XmlTObjDrivers_ReferenceDriver.hpp"

#include <TDF_Tool.hpp>
#include <TDF_Attribute.hpp>

#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>
#include <XmlObjMgt_RRelocationTable.hpp>

#include <TObj_TReference.hpp>
#include <TObj_Model.hpp>
#include <TObj_Object.hpp>
#include <TObj_Assistant.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlTObjDrivers_ReferenceDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(MasterEntry, "master")
IMPLEMENT_DOMSTRING(ReferredEntry, "entry")
IMPLEMENT_DOMSTRING(ReferredModelEntry, "modelentry")

//=================================================================================================

XmlTObjDrivers_ReferenceDriver::XmlTObjDrivers_ReferenceDriver(
  const occ::handle<Message_Messenger>& theMessageDriver)
    : XmlMDF_ADriver(theMessageDriver, nullptr)
{
}

//=======================================================================
// function : NewEmpty
// purpose  : Creates a new attribute
//=======================================================================

occ::handle<TDF_Attribute> XmlTObjDrivers_ReferenceDriver::NewEmpty() const
{
  return new TObj_TReference;
}

//=======================================================================
// function : Paste
// purpose  : Translate the contents of <aSource> and put it
//           into <aTarget>, using the relocation table
//           <aRelocTable> to keep the sharings.
//=======================================================================

bool XmlTObjDrivers_ReferenceDriver::Paste(const XmlObjMgt_Persistent&       Source,
                                           const occ::handle<TDF_Attribute>& Target,
                                           XmlObjMgt_RRelocationTable& /*RelocTable*/) const
{
  const XmlObjMgt_Element& anElement = Source;

  // get entries
  TCollection_AsciiString RefEntry    = anElement.getAttribute(::ReferredEntry());
  TCollection_AsciiString MasterEntry = anElement.getAttribute(::MasterEntry());
  // entry in model holder
  TCollection_AsciiString InHolderEntry = anElement.getAttribute(::ReferredModelEntry());

  // master label
  TDF_Label aLabel, aMasterLabel;
  TDF_Tool::Label(Target->Label().Data(), MasterEntry, aMasterLabel);
  // referred label
  if (InHolderEntry.IsEmpty())
    TDF_Tool::Label(Target->Label().Data(), RefEntry, aLabel, true);
  else
  {
    occ::handle<TObj_Model> aModel = TObj_Assistant::FindModel(InHolderEntry.ToCString());
    TDF_Tool::Label(aModel->GetLabel().Data(), RefEntry, aLabel, true);
  }
  occ::handle<TObj_TReference> aTarget = occ::down_cast<TObj_TReference>(Target);
  aTarget->Set(aLabel, aMasterLabel);

  return !aLabel.IsNull() && !aMasterLabel.IsNull();
}

//=======================================================================
// function : Paste
// purpose  : Translate the contents of <aSource> and put it
//           into <aTarget>, using the relocation table
//           <aRelocTable> to keep the sharings.
//           Store master and referred labels as entry, the other model referred
//           as entry in model-container
//=======================================================================

void XmlTObjDrivers_ReferenceDriver::Paste(const occ::handle<TDF_Attribute>& Source,
                                           XmlObjMgt_Persistent&             Target,
                                           XmlObjMgt_SRelocationTable& /*RelocTable*/) const
{
  occ::handle<TObj_TReference> aSource = occ::down_cast<TObj_TReference>(Source);

  occ::handle<TObj_Object> aLObject = aSource->Get();
  if (aLObject.IsNull())
    return;

  // referred entry
  TCollection_AsciiString entry;
  TDF_Label               aLabel = aLObject->GetLabel();
  TDF_Tool::Entry(aLabel, entry);
  Target.Element().setAttribute(::ReferredEntry(), entry.ToCString());

  // master entry
  entry.Clear();
  TDF_Label aMasterLabel = aSource->GetMasterLabel();
  TDF_Tool::Entry(aMasterLabel, entry);
  Target.Element().setAttribute(::MasterEntry(), entry.ToCString());

  // is reference to other document
  if (aLabel.Root() == aMasterLabel.Root())
    return;

  occ::handle<TObj_Model> aModel = aLObject->GetModel();
  TCollection_AsciiString aModelName(aModel->GetModelName()->String());
  Target.Element().setAttribute(::ReferredModelEntry(), aModelName.ToCString());
}
