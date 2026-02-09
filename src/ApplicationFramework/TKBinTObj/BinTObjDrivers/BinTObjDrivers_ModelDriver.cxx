#include <BinTObjDrivers_ModelDriver.hpp>

#include <BinObjMgt_Persistent.hpp>
#include <Standard_GUID.hpp>
#include <TDF_Attribute.hpp>

#include <TObj_TModel.hpp>
#include <TObj_Model.hpp>
#include <TObj_Assistant.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinTObjDrivers_ModelDriver, BinMDF_ADriver)

BinTObjDrivers_ModelDriver::BinTObjDrivers_ModelDriver(
  const occ::handle<Message_Messenger>& theMessageDriver)
    : BinMDF_ADriver(theMessageDriver, nullptr)
{
}

occ::handle<TDF_Attribute> BinTObjDrivers_ModelDriver::NewEmpty() const
{
  return new TObj_TModel;
}

bool BinTObjDrivers_ModelDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                       const occ::handle<TDF_Attribute>& theTarget,
                                       BinObjMgt_RRelocationTable&) const
{
  Standard_GUID aGUID;
  if (!(theSource >> aGUID))
    return false;

  occ::handle<TObj_Model> aCurrentModel = TObj_Assistant::GetCurrentModel();
  if (aCurrentModel.IsNull())
    return false;

  if (aGUID != aCurrentModel->GetGUID())
  {
    myMessageDriver->Send("TObj_TModel retrieval: wrong model GUID", Message_Fail);
    return false;
  }

  occ::handle<TObj_TModel> aTModel = occ::down_cast<TObj_TModel>(theTarget);
  aCurrentModel->SetLabel(aTModel->Label());
  aTModel->Set(aCurrentModel);
  return true;
}

void BinTObjDrivers_ModelDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TObj_TModel> aTModel = occ::down_cast<TObj_TModel>(theSource);
  occ::handle<TObj_Model>  aModel  = aTModel->Model();
  if (!aModel.IsNull())
  {

    Standard_GUID aGUID = aModel->GetGUID();
    theTarget << aGUID;
  }
}
