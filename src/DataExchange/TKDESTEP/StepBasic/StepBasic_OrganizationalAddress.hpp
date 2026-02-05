#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_Organization.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_Address.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepBasic_Organization;

class StepBasic_OrganizationalAddress : public StepBasic_Address
{

public:
  //! Returns a OrganizationalAddress
  Standard_EXPORT StepBasic_OrganizationalAddress();

  Standard_EXPORT void Init(
    const bool                                   hasAinternalLocation,
    const occ::handle<TCollection_HAsciiString>& aInternalLocation,
    const bool                                   hasAstreetNumber,
    const occ::handle<TCollection_HAsciiString>& aStreetNumber,
    const bool                                   hasAstreet,
    const occ::handle<TCollection_HAsciiString>& aStreet,
    const bool                                   hasApostalBox,
    const occ::handle<TCollection_HAsciiString>& aPostalBox,
    const bool                                   hasAtown,
    const occ::handle<TCollection_HAsciiString>& aTown,
    const bool                                   hasAregion,
    const occ::handle<TCollection_HAsciiString>& aRegion,
    const bool                                   hasApostalCode,
    const occ::handle<TCollection_HAsciiString>& aPostalCode,
    const bool                                   hasAcountry,
    const occ::handle<TCollection_HAsciiString>& aCountry,
    const bool                                   hasAfacsimileNumber,
    const occ::handle<TCollection_HAsciiString>& aFacsimileNumber,
    const bool                                   hasAtelephoneNumber,
    const occ::handle<TCollection_HAsciiString>& aTelephoneNumber,
    const bool                                   hasAelectronicMailAddress,
    const occ::handle<TCollection_HAsciiString>& aElectronicMailAddress,
    const bool                                   hasAtelexNumber,
    const occ::handle<TCollection_HAsciiString>& aTelexNumber,
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_Organization>>>& aOrganizations,
    const occ::handle<TCollection_HAsciiString>&                                 aDescription);

  Standard_EXPORT void SetOrganizations(
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_Organization>>>& aOrganizations);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepBasic_Organization>>>
                  Organizations() const;

  Standard_EXPORT occ::handle<StepBasic_Organization> OrganizationsValue(const int num) const;

  Standard_EXPORT int NbOrganizations() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_OrganizationalAddress, StepBasic_Address)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepBasic_Organization>>> organizations;
  occ::handle<TCollection_HAsciiString>                                 description;
};
