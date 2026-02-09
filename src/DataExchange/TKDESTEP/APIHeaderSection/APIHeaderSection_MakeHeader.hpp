#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class HeaderSection_FileName;
class HeaderSection_FileSchema;
class HeaderSection_FileDescription;
class StepData_StepModel;
class Interface_Protocol;
class TCollection_HAsciiString;

class APIHeaderSection_MakeHeader
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT APIHeaderSection_MakeHeader(const int shapetype = 0);

  Standard_EXPORT APIHeaderSection_MakeHeader(const occ::handle<StepData_StepModel>& model);

  Standard_EXPORT void Init(const char* nameval);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT void Apply(const occ::handle<StepData_StepModel>& model) const;

  Standard_EXPORT occ::handle<StepData_StepModel> NewModel(
    const occ::handle<Interface_Protocol>& protocol) const;

  Standard_EXPORT bool HasFn() const;

  Standard_EXPORT occ::handle<HeaderSection_FileName> FnValue() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetTimeStamp(const occ::handle<TCollection_HAsciiString>& aTimeStamp);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> TimeStamp() const;

  Standard_EXPORT void SetAuthor(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aAuthor);

  Standard_EXPORT void SetAuthorValue(const int                                    num,
                                      const occ::handle<TCollection_HAsciiString>& aAuthor);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> Author()
    const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> AuthorValue(const int num) const;

  Standard_EXPORT int NbAuthor() const;

  Standard_EXPORT void SetOrganization(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aOrganization);

  Standard_EXPORT void SetOrganizationValue(
    const int                                    num,
    const occ::handle<TCollection_HAsciiString>& aOrganization);

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

  Standard_EXPORT bool HasFs() const;

  Standard_EXPORT occ::handle<HeaderSection_FileSchema> FsValue() const;

  Standard_EXPORT void SetSchemaIdentifiers(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>&
      aSchemaIdentifiers);

  Standard_EXPORT void SetSchemaIdentifiersValue(
    const int                                    num,
    const occ::handle<TCollection_HAsciiString>& aSchemaIdentifier);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>
                  SchemaIdentifiers() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> SchemaIdentifiersValue(const int num) const;

  Standard_EXPORT int NbSchemaIdentifiers() const;

  Standard_EXPORT void AddSchemaIdentifier(
    const occ::handle<TCollection_HAsciiString>& aSchemaIdentifier);

  Standard_EXPORT bool HasFd() const;

  Standard_EXPORT occ::handle<HeaderSection_FileDescription> FdValue() const;

  Standard_EXPORT void SetDescription(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aDescription);

  Standard_EXPORT void SetDescriptionValue(
    const int                                    num,
    const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>
                  Description() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> DescriptionValue(const int num) const;

  Standard_EXPORT int NbDescription() const;

  Standard_EXPORT void SetImplementationLevel(
    const occ::handle<TCollection_HAsciiString>& aImplementationLevel);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ImplementationLevel() const;

private:
  bool                                       done;
  occ::handle<HeaderSection_FileName>        fn;
  occ::handle<HeaderSection_FileSchema>      fs;
  occ::handle<HeaderSection_FileDescription> fd;
};
