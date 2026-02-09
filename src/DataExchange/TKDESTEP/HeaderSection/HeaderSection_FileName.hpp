#pragma once

#include <Standard.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;

class HeaderSection_FileName : public Standard_Transient
{

public:
  Standard_EXPORT HeaderSection_FileName();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                   aName,
    const occ::handle<TCollection_HAsciiString>&                                   aTimeStamp,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aAuthor,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aOrganization,
    const occ::handle<TCollection_HAsciiString>& aPreprocessorVersion,
    const occ::handle<TCollection_HAsciiString>& aOriginatingSystem,
    const occ::handle<TCollection_HAsciiString>& aAuthorisation);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetTimeStamp(const occ::handle<TCollection_HAsciiString>& aTimeStamp);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> TimeStamp() const;

  Standard_EXPORT void SetAuthor(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aAuthor);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> Author()
    const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> AuthorValue(const int num) const;

  Standard_EXPORT int NbAuthor() const;

  Standard_EXPORT void SetOrganization(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aOrganization);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>
                  Organization() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> OrganizationValue(const int num) const;

  Standard_EXPORT int NbOrganization() const;

  Standard_EXPORT void SetPreprocessorVersion(
    const occ::handle<TCollection_HAsciiString>& aPreprocessorVersion);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PreprocessorVersion() const;

  Standard_EXPORT void SetOriginatingSystem(
    const occ::handle<TCollection_HAsciiString>& aOriginatingSystem);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> OriginatingSystem() const;

  Standard_EXPORT void SetAuthorisation(
    const occ::handle<TCollection_HAsciiString>& aAuthorisation);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Authorisation() const;

  DEFINE_STANDARD_RTTIEXT(HeaderSection_FileName, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>                                   name;
  occ::handle<TCollection_HAsciiString>                                   timeStamp;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> author;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> organization;
  occ::handle<TCollection_HAsciiString>                                   preprocessorVersion;
  occ::handle<TCollection_HAsciiString>                                   originatingSystem;
  occ::handle<TCollection_HAsciiString>                                   authorisation;
};
