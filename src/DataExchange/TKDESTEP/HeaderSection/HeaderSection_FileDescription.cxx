

#include <HeaderSection_FileDescription.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(HeaderSection_FileDescription, Standard_Transient)

HeaderSection_FileDescription::HeaderSection_FileDescription() = default;

void HeaderSection_FileDescription::Init(
  const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aDescription,
  const occ::handle<TCollection_HAsciiString>& aImplementationLevel)
{

  description         = aDescription;
  implementationLevel = aImplementationLevel;
}

void HeaderSection_FileDescription::SetDescription(
  const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aDescription)
{
  description = aDescription;
}

occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>
  HeaderSection_FileDescription::Description() const
{
  return description;
}

occ::handle<TCollection_HAsciiString> HeaderSection_FileDescription::DescriptionValue(
  const int num) const
{
  return description->Value(num);
}

int HeaderSection_FileDescription::NbDescription() const
{
  if (description.IsNull())
    return 0;
  return description->Length();
}

void HeaderSection_FileDescription::SetImplementationLevel(
  const occ::handle<TCollection_HAsciiString>& aImplementationLevel)
{
  implementationLevel = aImplementationLevel;
}

occ::handle<TCollection_HAsciiString> HeaderSection_FileDescription::ImplementationLevel() const
{
  return implementationLevel;
}
