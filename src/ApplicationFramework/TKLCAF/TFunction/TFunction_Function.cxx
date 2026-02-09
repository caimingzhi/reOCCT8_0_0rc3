#include <Standard_DomainError.hpp>
#include <Standard_Dump.hpp>
#include <Standard_Type.hpp>
#include <TDF_DataSet.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>
#include <TFunction_Function.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TFunction_Function, TDF_Attribute)

const Standard_GUID& TFunction_Function::GetID()
{
  static Standard_GUID TFunction_FunctionID("5b35ca00-5b78-11d1-8940-080009dc3333");
  return TFunction_FunctionID;
}

occ::handle<TFunction_Function> TFunction_Function::Set(const TDF_Label& L)
{
  occ::handle<TFunction_Function> F;
  if (!L.FindAttribute(TFunction_Function::GetID(), F))
  {
    F = new TFunction_Function();
    L.AddAttribute(F);
  }
  return F;
}

occ::handle<TFunction_Function> TFunction_Function::Set(const TDF_Label&     L,
                                                        const Standard_GUID& DriverID)
{
  occ::handle<TFunction_Function> F;
  if (!L.FindAttribute(TFunction_Function::GetID(), F))
  {
    F = new TFunction_Function();
    L.AddAttribute(F);
  }
  F->SetDriverGUID(DriverID);
  return F;
}

const Standard_GUID& TFunction_Function::ID() const
{
  return GetID();
}

TFunction_Function::TFunction_Function()
    : myFailure(0)
{
}

void TFunction_Function::SetDriverGUID(const Standard_GUID& guid)
{

  if (myDriverGUID == guid)
    return;

  Backup();
  myDriverGUID = guid;
}

void TFunction_Function::SetFailure(const int mode)
{

  if (myFailure == mode)
    return;

  Backup();
  myFailure = mode;
}

void TFunction_Function::Restore(const occ::handle<TDF_Attribute>& other)
{
  occ::handle<TFunction_Function> F = occ::down_cast<TFunction_Function>(other);
  myFailure                         = F->myFailure;
  myDriverGUID                      = F->myDriverGUID;
}

void TFunction_Function::Paste(const occ::handle<TDF_Attribute>& into,
                               const occ::handle<TDF_RelocationTable>&) const
{
  occ::handle<TFunction_Function> intof = occ::down_cast<TFunction_Function>(into);
  intof->SetFailure(myFailure);
  intof->SetDriverGUID(myDriverGUID);
}

occ::handle<TDF_Attribute> TFunction_Function::NewEmpty() const
{
  return new TFunction_Function();
}

void TFunction_Function::References(const occ::handle<TDF_DataSet>&) const {}

Standard_OStream& TFunction_Function::Dump(Standard_OStream& anOS) const
{
  TDF_Attribute::Dump(anOS);
  return anOS;
}

void TFunction_Function::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  OCCT_DUMP_FIELD_VALUE_GUID(theOStream, myDriverGUID)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myFailure)
}
