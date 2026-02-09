

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWPersonalAddress.hpp"
#include <StepBasic_Person.hpp>
#include <StepBasic_PersonalAddress.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWPersonalAddress::RWStepBasic_RWPersonalAddress() = default;

void RWStepBasic_RWPersonalAddress::ReadStep(
  const occ::handle<StepData_StepReaderData>&   data,
  const int                                     num,
  occ::handle<Interface_Check>&                 ach,
  const occ::handle<StepBasic_PersonalAddress>& ent) const
{

  if (!data->CheckNbParams(num, 14, ach, "personal_address"))
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

  occ::handle<NCollection_HArray1<occ::handle<StepBasic_Person>>> aPeople;
  occ::handle<StepBasic_Person>                                   anent13;
  int                                                             nsub13;
  if (data->ReadSubList(num, 13, "people", ach, nsub13))
  {
    int nb13 = data->NbParams(nsub13);
    aPeople  = new NCollection_HArray1<occ::handle<StepBasic_Person>>(1, nb13);
    for (int i13 = 1; i13 <= nb13; i13++)
    {

      if (data->ReadEntity(nsub13, i13, "person", ach, STANDARD_TYPE(StepBasic_Person), anent13))
        aPeople->SetValue(i13, anent13);
    }
  }

  occ::handle<TCollection_HAsciiString> aDescription;
  if (data->IsParamDefined(num, 14))
  {

    data->ReadString(num, 14, "description", ach, aDescription);
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
            aTelexNumber,
            aPeople,
            aDescription);
}

void RWStepBasic_RWPersonalAddress::WriteStep(
  StepData_StepWriter&                          SW,
  const occ::handle<StepBasic_PersonalAddress>& ent) const
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

  SW.OpenSub();
  for (int i13 = 1; i13 <= ent->NbPeople(); i13++)
  {
    SW.Send(ent->PeopleValue(i13));
  }
  SW.CloseSub();

  SW.Send(ent->Description());
}

void RWStepBasic_RWPersonalAddress::Share(const occ::handle<StepBasic_PersonalAddress>& ent,
                                          Interface_EntityIterator&                     iter) const
{

  int nbElem1 = ent->NbPeople();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->PeopleValue(is1));
  }
}
