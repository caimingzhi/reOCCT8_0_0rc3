#include <TObj_TModel.hpp>

#include <Standard_GUID.hpp>
#include <TDF_RelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TObj_TModel, TDF_Attribute)

//=================================================================================================

const Standard_GUID& TObj_TModel::GetID()
{
  static Standard_GUID GModelID("bbdab6a6-dca9-11d4-ba37-0060b0ee18ea");
  return GModelID;
}

//=================================================================================================

TObj_TModel::TObj_TModel() = default;

//=================================================================================================

const Standard_GUID& TObj_TModel::ID() const
{
  return GetID();
}

//=================================================================================================

occ::handle<TDF_Attribute> TObj_TModel::NewEmpty() const
{
  return new TObj_TModel;
}

//=================================================================================================

occ::handle<TObj_Model> TObj_TModel::Model() const
{
  return myModel;
}

//=================================================================================================

void TObj_TModel::Set(const occ::handle<TObj_Model>& theModel)
{
  Backup();
  myModel = theModel;
}

//=================================================================================================

void TObj_TModel::Restore(const occ::handle<TDF_Attribute>& theWith)
{
  occ::handle<TObj_TModel> R = occ::down_cast<TObj_TModel>(theWith);
  myModel                    = R->Model();
}

//=================================================================================================

void TObj_TModel::Paste(const occ::handle<TDF_Attribute>& theInto,
                        const occ::handle<TDF_RelocationTable>& /* RT */) const
{
  occ::handle<TObj_TModel> R = occ::down_cast<TObj_TModel>(theInto);
  R->Set(myModel);
}
