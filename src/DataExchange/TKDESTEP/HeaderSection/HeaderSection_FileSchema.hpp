#pragma once


#include <Standard.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;

class HeaderSection_FileSchema : public Standard_Transient
{

public:
  //! Returns a FileSchema
  Standard_EXPORT HeaderSection_FileSchema();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>&
      aSchemaIdentifiers);

  Standard_EXPORT void SetSchemaIdentifiers(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>&
      aSchemaIdentifiers);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>
                  SchemaIdentifiers() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> SchemaIdentifiersValue(const int num) const;

  Standard_EXPORT int NbSchemaIdentifiers() const;

  DEFINE_STANDARD_RTTIEXT(HeaderSection_FileSchema, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> schemaIdentifiers;
};

