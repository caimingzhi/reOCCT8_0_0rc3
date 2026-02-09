

#include <XCAFDoc_Material.hpp>

#include <Standard_Dump.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XCAFDoc_Material, TDF_Attribute)

XCAFDoc_Material::XCAFDoc_Material() = default;

const Standard_GUID& XCAFDoc_Material::GetID()
{
  static Standard_GUID MatID("efd212f8-6dfd-11d4-b9c8-0060b0ee281b");
  return MatID;
}

occ::handle<XCAFDoc_Material> XCAFDoc_Material::Set(
  const TDF_Label&                             label,
  const occ::handle<TCollection_HAsciiString>& aName,
  const occ::handle<TCollection_HAsciiString>& aDescription,
  const double                                 aDensity,
  const occ::handle<TCollection_HAsciiString>& aDensName,
  const occ::handle<TCollection_HAsciiString>& aDensValType)
{
  occ::handle<XCAFDoc_Material> A;
  if (!label.FindAttribute(XCAFDoc_Material::GetID(), A))
  {
    A = new XCAFDoc_Material();
    label.AddAttribute(A);
  }
  A->Set(aName, aDescription, aDensity, aDensName, aDensValType);
  return A;
}

void XCAFDoc_Material::Set(const occ::handle<TCollection_HAsciiString>& aName,
                           const occ::handle<TCollection_HAsciiString>& aDescription,
                           const double                                 aDensity,
                           const occ::handle<TCollection_HAsciiString>& aDensName,
                           const occ::handle<TCollection_HAsciiString>& aDensValType)
{
  myName        = aName;
  myDescription = aDescription;
  myDensity     = aDensity;
  myDensName    = aDensName;
  myDensValType = aDensValType;
}

occ::handle<TCollection_HAsciiString> XCAFDoc_Material::GetName() const
{
  return myName;
}

occ::handle<TCollection_HAsciiString> XCAFDoc_Material::GetDescription() const
{
  return myDescription;
}

double XCAFDoc_Material::GetDensity() const
{
  return myDensity;
}

occ::handle<TCollection_HAsciiString> XCAFDoc_Material::GetDensName() const
{
  return myDensName;
}

occ::handle<TCollection_HAsciiString> XCAFDoc_Material::GetDensValType() const
{
  return myDensValType;
}

const Standard_GUID& XCAFDoc_Material::ID() const
{
  return GetID();
}

void XCAFDoc_Material::Restore(const occ::handle<TDF_Attribute>& With)
{
  myName        = occ::down_cast<XCAFDoc_Material>(With)->GetName();
  myDensity     = occ::down_cast<XCAFDoc_Material>(With)->GetDensity();
  myDescription = occ::down_cast<XCAFDoc_Material>(With)->GetDescription();
  myDensName    = occ::down_cast<XCAFDoc_Material>(With)->GetDensName();
  myDensValType = occ::down_cast<XCAFDoc_Material>(With)->GetDensValType();
}

occ::handle<TDF_Attribute> XCAFDoc_Material::NewEmpty() const
{
  return new XCAFDoc_Material();
}

void XCAFDoc_Material::Paste(const occ::handle<TDF_Attribute>& Into,
                             const occ::handle<TDF_RelocationTable>&) const
{
  occ::down_cast<XCAFDoc_Material>(Into)->Set(myName,
                                              myDescription,
                                              myDensity,
                                              myDensName,
                                              myDensValType);
}

void XCAFDoc_Material::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  if (!myName.IsNull())
  {
    const char* aMaterialName = myName->ToCString();
    OCCT_DUMP_FIELD_VALUE_STRING(theOStream, aMaterialName)
  }
  if (!myDescription.IsNull())
  {
    const char* aDescriptionName = myDescription->ToCString();
    OCCT_DUMP_FIELD_VALUE_STRING(theOStream, aDescriptionName)
  }

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myDensity)

  if (!myDensName.IsNull())
  {
    const char* aDensName = myDensName->ToCString();
    OCCT_DUMP_FIELD_VALUE_STRING(theOStream, aDensName)
  }
  if (!myDensValType.IsNull())
  {
    const char* aDensValType = myDensValType->ToCString();
    OCCT_DUMP_FIELD_VALUE_STRING(theOStream, aDensValType)
  }
}
