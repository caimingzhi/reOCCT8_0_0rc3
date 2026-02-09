

#include <StdLPersistent_Value.hpp>

#include <TCollection_HExtendedString.hpp>
#include <Standard_GUID.hpp>

template <class AttribClass>
void StdLPersistent_Value::integer<AttribClass>::ImportAttribute()
{
  this->myTransient->Set(this->myData);
}

template <class AttribClass, class HStringClass>
void StdLPersistent_Value::string<AttribClass, HStringClass>::ImportAttribute()
{
  occ::handle<HStringClass> anHString = occ::down_cast<HStringClass>(this->myData);
  if (anHString)
  {
    this->myTransient->Set(anHString->Value()->String());
    this->myData.Nullify();
  }
}

template <>
void StdLPersistent_Value::string<TDF_Reference>::ImportAttribute()
{
  if (this->myData)
  {
    TDF_Label aLabel = myData->Label(this->myTransient->Label().Data());
    if (!aLabel.IsNull())
      this->myTransient->Set(aLabel);
    this->myData.Nullify();
  }
}

template <>
void StdLPersistent_Value::string<TDataStd_UAttribute>::ImportAttribute()
{
}

occ::handle<TDF_Attribute> StdLPersistent_Value::UAttribute::CreateAttribute()
{
  string<TDataStd_UAttribute, StdLPersistent_HString::Extended>::CreateAttribute();

  if (this->myData)
  {
    occ::handle<TCollection_HExtendedString> aString = this->myData->ExtString();
    if (aString)
      this->myTransient->SetID(Standard_GUID(aString->String().ToExtString()));
    this->myData.Nullify();
  }

  return this->myTransient;
}

occ::handle<TDF_Attribute> StdLPersistent_Value::Integer::CreateAttribute()
{
  integer<TDataStd_Integer>::CreateAttribute();

  if (this->myData)
  {
    this->myTransient->SetID(TDataStd_Integer::GetID());
  }

  return this->myTransient;
}

occ::handle<TDF_Attribute> StdLPersistent_Value::Name::CreateAttribute()
{
  string<TDataStd_Name>::CreateAttribute();

  if (this->myData)
  {
    this->myTransient->SetID(TDataStd_Name::GetID());
  }

  return this->myTransient;
}

occ::handle<TDF_Attribute> StdLPersistent_Value::AsciiString::CreateAttribute()
{
  string<TDataStd_AsciiString, StdLPersistent_HString::Ascii>::CreateAttribute();

  if (this->myData)
  {
    this->myTransient->SetID(TDataStd_AsciiString::GetID());
  }

  return this->myTransient;
}

template class StdLPersistent_Value::integer<TDataStd_Integer>;
template class StdLPersistent_Value::integer<TDF_TagSource>;

template class StdLPersistent_Value::string<TDF_Reference>;
template class StdLPersistent_Value::string<TDataStd_UAttribute>;
template class StdLPersistent_Value::string<TDataStd_Name>;
template class StdLPersistent_Value::string<TDataStd_Comment>;
template class StdLPersistent_Value::string<TDataStd_AsciiString, StdLPersistent_HString::Ascii>;
