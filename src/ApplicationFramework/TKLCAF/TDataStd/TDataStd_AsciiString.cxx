#include <TDataStd_AsciiString.hpp>

#include <Standard_Dump.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_AsciiString, TDF_Attribute)

//=================================================================================================

TDataStd_AsciiString::TDataStd_AsciiString()
    : myID(GetID())
{
  myString.Clear();
}

//=================================================================================================

const Standard_GUID& TDataStd_AsciiString::GetID()
{
  static Standard_GUID theGUID("3bbefc60-e618-11d4-ba38-0060b0ee18ea");
  return theGUID;
}

//=================================================================================================

const Standard_GUID& TDataStd_AsciiString::ID() const
{
  return myID;
}

//=======================================================================
// function : SetAttr
// purpose  : Implements Set functionality
//=======================================================================
static occ::handle<TDataStd_AsciiString> SetAttr(const TDF_Label&               label,
                                                 const TCollection_AsciiString& theString,
                                                 const Standard_GUID&           theGuid)
{
  occ::handle<TDataStd_AsciiString> A;
  if (!label.FindAttribute(theGuid, A))
  {
    A = new TDataStd_AsciiString();
    A->SetID(theGuid);
    label.AddAttribute(A);
  }
  A->Set(theString);
  return A;
}

//=================================================================================================

occ::handle<TDataStd_AsciiString> TDataStd_AsciiString::Set(
  const TDF_Label&               theLabel,
  const TCollection_AsciiString& theAsciiString)
{
  return SetAttr(theLabel, theAsciiString, GetID());
}

//=======================================================================
// function : Set
// purpose  : Set user defined attribute
//=======================================================================

occ::handle<TDataStd_AsciiString> TDataStd_AsciiString::Set(
  const TDF_Label&               theLabel,
  const Standard_GUID&           theGuid,
  const TCollection_AsciiString& theAsciiString)
{
  return SetAttr(theLabel, theAsciiString, theGuid);
}

//=================================================================================================

void TDataStd_AsciiString::Set(const TCollection_AsciiString& theAsciiString)
{
  if (myString == theAsciiString)
    return;
  Backup();
  myString = theAsciiString;
}

//=================================================================================================

const TCollection_AsciiString& TDataStd_AsciiString::Get() const
{
  return myString;
}

//=================================================================================================

void TDataStd_AsciiString::SetID(const Standard_GUID& theGuid)
{
  if (myID == theGuid)
    return;

  Backup();
  myID = theGuid;
}

//=================================================================================================

void TDataStd_AsciiString::SetID()
{
  Backup();
  myID = GetID();
}

//=================================================================================================

occ::handle<TDF_Attribute> TDataStd_AsciiString::NewEmpty() const
{
  return new TDataStd_AsciiString();
}

//=================================================================================================

void TDataStd_AsciiString::Restore(const occ::handle<TDF_Attribute>& theWith)
{
  occ::handle<TDataStd_AsciiString> R = occ::down_cast<TDataStd_AsciiString>(theWith);
  myString                            = R->Get();
  myID                                = R->ID();
}

//=================================================================================================

void TDataStd_AsciiString::Paste(const occ::handle<TDF_Attribute>& theInto,
                                 const occ::handle<TDF_RelocationTable>& /* RT */) const
{
  occ::handle<TDataStd_AsciiString> R = occ::down_cast<TDataStd_AsciiString>(theInto);
  R->Set(myString);
  R->SetID(myID);
}

//=================================================================================================

bool TDataStd_AsciiString::IsEmpty() const
{
  return myString.IsEmpty();
}

//=================================================================================================

Standard_OStream& TDataStd_AsciiString::Dump(Standard_OStream& theOS) const
{
  Standard_OStream& anOS = TDF_Attribute::Dump(theOS);
  anOS << myString;
  anOS << " Name=|" << myString << "|";
  char sguid[Standard_GUID_SIZE_ALLOC];
  myID.ToCString(sguid);
  anOS << sguid << "|" << std::endl;
  return anOS;
}

//=================================================================================================

void TDataStd_AsciiString::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, myString)
}
