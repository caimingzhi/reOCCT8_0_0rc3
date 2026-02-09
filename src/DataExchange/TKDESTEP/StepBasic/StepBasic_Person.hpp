#pragma once

#include <Standard.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;

class StepBasic_Person : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_Person();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                   aId,
    const bool                                                                     hasAlastName,
    const occ::handle<TCollection_HAsciiString>&                                   aLastName,
    const bool                                                                     hasAfirstName,
    const occ::handle<TCollection_HAsciiString>&                                   aFirstName,
    const bool                                                                     hasAmiddleNames,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aMiddleNames,
    const bool                                                                     hasAprefixTitles,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aPrefixTitles,
    const bool                                                                     hasAsuffixTitles,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aSuffixTitles);

  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& aId);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  Standard_EXPORT void SetLastName(const occ::handle<TCollection_HAsciiString>& aLastName);

  Standard_EXPORT void UnSetLastName();

  Standard_EXPORT occ::handle<TCollection_HAsciiString> LastName() const;

  Standard_EXPORT bool HasLastName() const;

  Standard_EXPORT void SetFirstName(const occ::handle<TCollection_HAsciiString>& aFirstName);

  Standard_EXPORT void UnSetFirstName();

  Standard_EXPORT occ::handle<TCollection_HAsciiString> FirstName() const;

  Standard_EXPORT bool HasFirstName() const;

  Standard_EXPORT void SetMiddleNames(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aMiddleNames);

  Standard_EXPORT void UnSetMiddleNames();

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>
                  MiddleNames() const;

  Standard_EXPORT bool HasMiddleNames() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> MiddleNamesValue(const int num) const;

  Standard_EXPORT int NbMiddleNames() const;

  Standard_EXPORT void SetPrefixTitles(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aPrefixTitles);

  Standard_EXPORT void UnSetPrefixTitles();

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>
                  PrefixTitles() const;

  Standard_EXPORT bool HasPrefixTitles() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PrefixTitlesValue(const int num) const;

  Standard_EXPORT int NbPrefixTitles() const;

  Standard_EXPORT void SetSuffixTitles(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aSuffixTitles);

  Standard_EXPORT void UnSetSuffixTitles();

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>
                  SuffixTitles() const;

  Standard_EXPORT bool HasSuffixTitles() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> SuffixTitlesValue(const int num) const;

  Standard_EXPORT int NbSuffixTitles() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_Person, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>                                   id;
  occ::handle<TCollection_HAsciiString>                                   lastName;
  occ::handle<TCollection_HAsciiString>                                   firstName;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> middleNames;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> prefixTitles;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> suffixTitles;
  bool                                                                    hasLastName;
  bool                                                                    hasFirstName;
  bool                                                                    hasMiddleNames;
  bool                                                                    hasPrefixTitles;
  bool                                                                    hasSuffixTitles;
};
