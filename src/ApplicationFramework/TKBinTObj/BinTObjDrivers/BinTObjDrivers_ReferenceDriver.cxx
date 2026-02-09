#include <BinTObjDrivers_ReferenceDriver.hpp>
#include <TDF_Attribute.hpp>
#include <TObj_TReference.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <TObj_Model.hpp>
#include <TObj_Assistant.hpp>
#include <TDF_Tool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinTObjDrivers_ReferenceDriver, BinMDF_ADriver)

BinTObjDrivers_ReferenceDriver::BinTObjDrivers_ReferenceDriver(
  const occ::handle<Message_Messenger>& theMessageDriver)
    : BinMDF_ADriver(theMessageDriver, nullptr)
{
}

occ::handle<TDF_Attribute> BinTObjDrivers_ReferenceDriver::NewEmpty() const
{
  return new TObj_TReference;
}

bool BinTObjDrivers_ReferenceDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                           const occ::handle<TDF_Attribute>& theTarget,
                                           BinObjMgt_RRelocationTable&) const
{

  TDF_Label             aMasterLabel;
  occ::handle<TDF_Data> aDS = theTarget->Label().Data();
  if (!theSource.GetLabel(aDS, aMasterLabel))
    return false;

  bool isSameDoc = false;
  if (!(theSource >> isSameDoc))
    return false;

  if (!isSameDoc)
  {
    TCollection_AsciiString aName;
    if (!(theSource >> aName))
      return false;
    occ::handle<TObj_Model> aModel = TObj_Assistant::FindModel(aName.ToCString());
    if (aModel.IsNull())
    {
      TCollection_AsciiString anEntry;
      TDF_Tool::Entry(theTarget->Label(), anEntry);
      myMessageDriver->Send(TCollection_ExtendedString("TObj_TReference retrieval: ")
                              + "wrong model ID " + aName + ", entry " + anEntry,
                            Message_Fail);
      return false;
    }
    aDS = aModel->GetLabel().Data();
  }

  TDF_Label aLabel;
  if (!theSource.GetLabel(aDS, aLabel))
    return false;

  occ::handle<TObj_TReference> aTarget = occ::down_cast<TObj_TReference>(theTarget);
  aTarget->Set(aLabel, aMasterLabel);

  return !aLabel.IsNull() && !aMasterLabel.IsNull();
}

void BinTObjDrivers_ReferenceDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TObj_TReference> aSource = occ::down_cast<TObj_TReference>(theSource);

  occ::handle<TObj_Object> aLObject = aSource->Get();
  if (aLObject.IsNull())
    return;

  TDF_Label aLabel       = aLObject->GetLabel();
  TDF_Label aMasterLabel = aSource->GetMasterLabel();
  bool      isSameDoc    = (aLabel.Root() == aMasterLabel.Root());

  theTarget << aMasterLabel;

  theTarget << isSameDoc;
  if (!isSameDoc)
  {
    TCollection_AsciiString aName;
    occ::handle<TObj_Model> aModel = aLObject->GetModel();
    aName                          = TCollection_AsciiString(aModel->GetModelName()->String());
    theTarget << aName;
  }

  theTarget << aLabel;
}
