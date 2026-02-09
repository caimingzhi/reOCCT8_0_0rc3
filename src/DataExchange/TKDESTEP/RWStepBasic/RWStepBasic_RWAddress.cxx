

#include "RWStepBasic_RWAddress.hpp"
#include <StepBasic_Address.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWAddress::RWStepBasic_RWAddress() = default;

void RWStepBasic_RWAddress::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                     const int                                   num,
                                     occ::handle<Interface_Check>&               ach,
                                     const occ::handle<StepBasic_Address>&       ent) const
{

  if (!data->CheckNbParams(num, 12, ach, "address"))
    return;

  occ::handle<TCollection_HAsciiString> aInternalLocation;
  bool                                  hasAinternalLocation = true;
  if (data->IsParamDefined(num, 1))
  {

    data->ReadString(num, 1, "internal_location", ach, aInternalLocation);
  }
  else
  {
    hasAinternalLocation = false;
    aInternalLocation.Nullify();
  }

  occ::handle<TCollection_HAsciiString> aStreetNumber;
  bool                                  hasAstreetNumber = true;
  if (data->IsParamDefined(num, 2))
  {

    data->ReadString(num, 2, "street_number", ach, aStreetNumber);
  }
  else
  {
    hasAstreetNumber = false;
    aStreetNumber.Nullify();
  }

  occ::handle<TCollection_HAsciiString> aStreet;
  bool                                  hasAstreet = true;
  if (data->IsParamDefined(num, 3))
  {

    data->ReadString(num, 3, "street", ach, aStreet);
  }
  else
  {
    hasAstreet = false;
    aStreet.Nullify();
  }

  occ::handle<TCollection_HAsciiString> aPostalBox;
  bool                                  hasApostalBox = true;
  if (data->IsParamDefined(num, 4))
  {

    data->ReadString(num, 4, "postal_box", ach, aPostalBox);
  }
  else
  {
    hasApostalBox = false;
    aPostalBox.Nullify();
  }

  occ::handle<TCollection_HAsciiString> aTown;
  bool                                  hasAtown = true;
  if (data->IsParamDefined(num, 5))
  {

    data->ReadString(num, 5, "town", ach, aTown);
  }
  else
  {
    hasAtown = false;
    aTown.Nullify();
  }

  occ::handle<TCollection_HAsciiString> aRegion;
  bool                                  hasAregion = true;
  if (data->IsParamDefined(num, 6))
  {

    data->ReadString(num, 6, "region", ach, aRegion);
  }
  else
  {
    hasAregion = false;
    aRegion.Nullify();
  }

  occ::handle<TCollection_HAsciiString> aPostalCode;
  bool                                  hasApostalCode = true;
  if (data->IsParamDefined(num, 7))
  {

    data->ReadString(num, 7, "postal_code", ach, aPostalCode);
  }
  else
  {
    hasApostalCode = false;
    aPostalCode.Nullify();
  }

  occ::handle<TCollection_HAsciiString> aCountry;
  bool                                  hasAcountry = true;
  if (data->IsParamDefined(num, 8))
  {

    data->ReadString(num, 8, "country", ach, aCountry);
  }
  else
  {
    hasAcountry = false;
    aCountry.Nullify();
  }

  occ::handle<TCollection_HAsciiString> aFacsimileNumber;
  bool                                  hasAfacsimileNumber = true;
  if (data->IsParamDefined(num, 9))
  {

    data->ReadString(num, 9, "facsimile_number", ach, aFacsimileNumber);
  }
  else
  {
    hasAfacsimileNumber = false;
    aFacsimileNumber.Nullify();
  }

  occ::handle<TCollection_HAsciiString> aTelephoneNumber;
  bool                                  hasAtelephoneNumber = true;
  if (data->IsParamDefined(num, 10))
  {

    data->ReadString(num, 10, "telephone_number", ach, aTelephoneNumber);
  }
  else
  {
    hasAtelephoneNumber = false;
    aTelephoneNumber.Nullify();
  }

  occ::handle<TCollection_HAsciiString> aElectronicMailAddress;
  bool                                  hasAelectronicMailAddress = true;
  if (data->IsParamDefined(num, 11))
  {

    data->ReadString(num, 11, "electronic_mail_address", ach, aElectronicMailAddress);
  }
  else
  {
    hasAelectronicMailAddress = false;
    aElectronicMailAddress.Nullify();
  }

  occ::handle<TCollection_HAsciiString> aTelexNumber;
  bool                                  hasAtelexNumber = true;
  if (data->IsParamDefined(num, 12))
  {

    data->ReadString(num, 12, "telex_number", ach, aTelexNumber);
  }
  else
  {
    hasAtelexNumber = false;
    aTelexNumber.Nullify();
  }

  ent->Init(hasAinternalLocation,
            aInternalLocation,
            hasAstreetNumber,
            aStreetNumber,
            hasAstreet,
            aStreet,
            hasApostalBox,
            aPostalBox,
            hasAtown,
            aTown,
            hasAregion,
            aRegion,
            hasApostalCode,
            aPostalCode,
            hasAcountry,
            aCountry,
            hasAfacsimileNumber,
            aFacsimileNumber,
            hasAtelephoneNumber,
            aTelephoneNumber,
            hasAelectronicMailAddress,
            aElectronicMailAddress,
            hasAtelexNumber,
            aTelexNumber);
}

void RWStepBasic_RWAddress::WriteStep(StepData_StepWriter&                  SW,
                                      const occ::handle<StepBasic_Address>& ent) const
{

  bool hasAinternalLocation = ent->HasInternalLocation();
  if (hasAinternalLocation)
  {
    SW.Send(ent->InternalLocation());
  }
  else
  {
    SW.SendUndef();
  }

  bool hasAstreetNumber = ent->HasStreetNumber();
  if (hasAstreetNumber)
  {
    SW.Send(ent->StreetNumber());
  }
  else
  {
    SW.SendUndef();
  }

  bool hasAstreet = ent->HasStreet();
  if (hasAstreet)
  {
    SW.Send(ent->Street());
  }
  else
  {
    SW.SendUndef();
  }

  bool hasApostalBox = ent->HasPostalBox();
  if (hasApostalBox)
  {
    SW.Send(ent->PostalBox());
  }
  else
  {
    SW.SendUndef();
  }

  bool hasAtown = ent->HasTown();
  if (hasAtown)
  {
    SW.Send(ent->Town());
  }
  else
  {
    SW.SendUndef();
  }

  bool hasAregion = ent->HasRegion();
  if (hasAregion)
  {
    SW.Send(ent->Region());
  }
  else
  {
    SW.SendUndef();
  }

  bool hasApostalCode = ent->HasPostalCode();
  if (hasApostalCode)
  {
    SW.Send(ent->PostalCode());
  }
  else
  {
    SW.SendUndef();
  }

  bool hasAcountry = ent->HasCountry();
  if (hasAcountry)
  {
    SW.Send(ent->Country());
  }
  else
  {
    SW.SendUndef();
  }

  bool hasAfacsimileNumber = ent->HasFacsimileNumber();
  if (hasAfacsimileNumber)
  {
    SW.Send(ent->FacsimileNumber());
  }
  else
  {
    SW.SendUndef();
  }

  bool hasAtelephoneNumber = ent->HasTelephoneNumber();
  if (hasAtelephoneNumber)
  {
    SW.Send(ent->TelephoneNumber());
  }
  else
  {
    SW.SendUndef();
  }

  bool hasAelectronicMailAddress = ent->HasElectronicMailAddress();
  if (hasAelectronicMailAddress)
  {
    SW.Send(ent->ElectronicMailAddress());
  }
  else
  {
    SW.SendUndef();
  }

  bool hasAtelexNumber = ent->HasTelexNumber();
  if (hasAtelexNumber)
  {
    SW.Send(ent->TelexNumber());
  }
  else
  {
    SW.SendUndef();
  }
}
