

#include <HeaderSection_FileSchema.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(HeaderSection_FileSchema, Standard_Transient)

HeaderSection_FileSchema::HeaderSection_FileSchema() = default;

void HeaderSection_FileSchema::Init(
  const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aSchemaIdentifiers)
{

  schemaIdentifiers = aSchemaIdentifiers;
}

void HeaderSection_FileSchema::SetSchemaIdentifiers(
  const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aSchemaIdentifiers)
{
  schemaIdentifiers = aSchemaIdentifiers;
}

occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> HeaderSection_FileSchema::
  SchemaIdentifiers() const
{
  return schemaIdentifiers;
}

occ::handle<TCollection_HAsciiString> HeaderSection_FileSchema::SchemaIdentifiersValue(
  const int num) const
{
  return schemaIdentifiers->Value(num);
}

int HeaderSection_FileSchema::NbSchemaIdentifiers() const
{
  if (schemaIdentifiers.IsNull())
    return 0;
  return schemaIdentifiers->Length();
}
