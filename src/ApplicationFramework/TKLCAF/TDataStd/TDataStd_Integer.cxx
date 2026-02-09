#include <TDataStd_Integer.hpp>

#include <Standard_Dump.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_Reference.hpp>
#include <TDF_RelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_Integer, TDF_Attribute)

const Standard_GUID& TDataStd_Integer::GetID()
{
  static Standard_GUID TDataStd_IntegerID("2a96b606-ec8b-11d0-bee7-080009dc3333");
  return TDataStd_IntegerID;
}

static occ::handle<TDataStd_Integer> SetAttr(const TDF_Label&     label,
                                             const int            V,
                                             const Standard_GUID& theGuid)
{
  occ::handle<TDataStd_Integer> A;
  if (!label.FindAttribute(theGuid, A))
  {
    A = new TDataStd_Integer();
    A->SetID(theGuid);
    label.AddAttribute(A);
  }
  A->Set(V);
  return A;
}

occ::handle<TDataStd_Integer> TDataStd_Integer::Set(const TDF_Label& L, const int V)

{
  return SetAttr(L, V, GetID());
}

occ::handle<TDataStd_Integer> TDataStd_Integer::Set(const TDF_Label&     L,
                                                    const Standard_GUID& theGuid,
                                                    const int            V)
{
  return SetAttr(L, V, theGuid);
}

TDataStd_Integer::TDataStd_Integer()
    : myValue(-1),
      myID(GetID())
{
}

void TDataStd_Integer::Set(const int v)
{

  if (myValue == v)
    return;

  Backup();
  myValue = v;
}

int TDataStd_Integer::Get() const
{
  return myValue;
}

bool TDataStd_Integer::IsCaptured() const
{
  occ::handle<TDF_Reference> R;
  return (Label().FindAttribute(TDF_Reference::GetID(), R));
}

const Standard_GUID& TDataStd_Integer::ID() const
{
  return myID;
}

void TDataStd_Integer::SetID(const Standard_GUID& theGuid)
{
  if (myID == theGuid)
    return;

  Backup();
  myID = theGuid;
}

void TDataStd_Integer::SetID()
{
  Backup();
  myID = GetID();
}

occ::handle<TDF_Attribute> TDataStd_Integer::NewEmpty() const
{
  return new TDataStd_Integer();
}

void TDataStd_Integer::Restore(const occ::handle<TDF_Attribute>& With)
{
  occ::handle<TDataStd_Integer> anInt = occ::down_cast<TDataStd_Integer>(With);
  myValue                             = anInt->Get();
  myID                                = anInt->ID();
}

void TDataStd_Integer::Paste(const occ::handle<TDF_Attribute>& Into,
                             const occ::handle<TDF_RelocationTable>&) const
{
  occ::handle<TDataStd_Integer> anInt = occ::down_cast<TDataStd_Integer>(Into);
  anInt->Set(myValue);
  anInt->SetID(myID);
}

Standard_OStream& TDataStd_Integer::Dump(Standard_OStream& anOS) const
{
  anOS << "Integer:: " << this << " : ";
  anOS << myValue;
  char sguid[Standard_GUID_SIZE_ALLOC];
  myID.ToCString(sguid);
  anOS << sguid;

  anOS << "\nAttribute fields: ";
  TDF_Attribute::Dump(anOS);
  return anOS;
}

void TDataStd_Integer::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myValue)
}
