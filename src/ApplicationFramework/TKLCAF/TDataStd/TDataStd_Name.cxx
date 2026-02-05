#include <TDataStd_Name.hpp>
#include <TDF_Label.hpp>

IMPLEMENT_DERIVED_ATTRIBUTE(TDataStd_Name, TDataStd_GenericExtString)

//=================================================================================================

const Standard_GUID& TDataStd_Name::GetID()
{
  static Standard_GUID TDataStd_NameID("2a96b608-ec8b-11d0-bee7-080009dc3333");
  return TDataStd_NameID;
}

//=======================================================================
// function : SetAttr
// purpose  : Implements Set functionality
//=======================================================================
static occ::handle<TDataStd_Name> SetAttr(const TDF_Label&                  label,
                                          const TCollection_ExtendedString& theString,
                                          const Standard_GUID&              theGuid)
{
  occ::handle<TDataStd_Name> N;
  if (!label.FindAttribute(theGuid, N))
  {
    N = new TDataStd_Name();
    N->SetID(theGuid);
    label.AddAttribute(N);
  }
  N->Set(theString);
  return N;
}

//=================================================================================================

occ::handle<TDataStd_Name> TDataStd_Name::Set(const TDF_Label&                  label,
                                              const TCollection_ExtendedString& theString)
{
  return SetAttr(label, theString, GetID());
}

//=======================================================================
// function : Set
// purpose  : Set user defined attribute
//=======================================================================

occ::handle<TDataStd_Name> TDataStd_Name::Set(const TDF_Label&                  label,
                                              const Standard_GUID&              theGuid,
                                              const TCollection_ExtendedString& theString)
{
  return SetAttr(label, theString, theGuid);
}

//=================================================================================================

TDataStd_Name::TDataStd_Name()
{
  myID = GetID();
}

//=================================================================================================

void TDataStd_Name::Set(const TCollection_ExtendedString& S)
{
  if (myString == S)
    return;

  Backup();
  myString = S;
}

//=================================================================================================

void TDataStd_Name::SetID(const Standard_GUID& theGuid)
{
  if (myID == theGuid)
    return;

  Backup();
  myID = theGuid;
}

//=================================================================================================

void TDataStd_Name::SetID()
{
  Backup();
  myID = GetID();
}

// TDF_Attribute methods
//=================================================================================================

Standard_OStream& TDataStd_Name::Dump(Standard_OStream& anOS) const
{
  TDF_Attribute::Dump(anOS);
  anOS << " Name=|" << myString << "|";
  char sguid[Standard_GUID_SIZE_ALLOC];
  myID.ToCString(sguid);
  anOS << sguid << std::endl;
  return anOS;
}
