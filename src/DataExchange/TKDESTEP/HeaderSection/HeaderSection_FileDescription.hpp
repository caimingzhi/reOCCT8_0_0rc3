#pragma once


#include <Standard.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;

class HeaderSection_FileDescription : public Standard_Transient
{

public:
  //! Returns a FileDescription
  Standard_EXPORT HeaderSection_FileDescription();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aDescription,
    const occ::handle<TCollection_HAsciiString>& aImplementationLevel);

  Standard_EXPORT void SetDescription(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aDescription);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>
                  Description() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> DescriptionValue(const int num) const;

  Standard_EXPORT int NbDescription() const;

  Standard_EXPORT void SetImplementationLevel(
    const occ::handle<TCollection_HAsciiString>& aImplementationLevel);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ImplementationLevel() const;

  DEFINE_STANDARD_RTTIEXT(HeaderSection_FileDescription, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> description;
  occ::handle<TCollection_HAsciiString>                                   implementationLevel;
};

