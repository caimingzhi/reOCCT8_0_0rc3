#include <TDataStd_Real.hpp>

#include <Standard_Dump.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDataStd.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_Reference.hpp>
#include <TDF_RelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_Real, TDF_Attribute)

const Standard_GUID& TDataStd_Real::GetID()
{
  static Standard_GUID TDataStd_RealID("2a96b60f-ec8b-11d0-bee7-080009dc3333");
  return TDataStd_RealID;
}

static occ::handle<TDataStd_Real> SetAttr(const TDF_Label&     label,
                                          const double         V,
                                          const Standard_GUID& theGuid)
{
  occ::handle<TDataStd_Real> A;
  if (!label.FindAttribute(theGuid, A))
  {
    A = new TDataStd_Real();
    A->SetID(theGuid);
    label.AddAttribute(A);
  }
  A->Set(V);
  return A;
}

occ::handle<TDataStd_Real> TDataStd_Real::Set(const TDF_Label& L, const double V)
{
  return SetAttr(L, V, GetID());
}

occ::handle<TDataStd_Real> TDataStd_Real::Set(const TDF_Label&     L,
                                              const Standard_GUID& theGuid,
                                              const double         V)
{
  return SetAttr(L, V, theGuid);
}

TDataStd_Real::TDataStd_Real()
    : myValue(RealFirst()),
      myDimension(TDataStd_SCALAR),
      myID(GetID())
{
}

bool TDataStd_Real::IsCaptured() const
{
  occ::handle<TDF_Reference> reference;

  if (Label().FindAttribute(TDF_Reference::GetID(), reference))
  {
    const TDF_Label& aLabel = reference->Get();
    return aLabel.IsAttribute(myID);
  }
  return false;
}

void TDataStd_Real::Set(const double v)
{

  if (myValue == v)
    return;

  Backup();
  myValue = v;
}

double TDataStd_Real::Get() const
{
  return myValue;
}

void TDataStd_Real::SetDimension(const TDataStd_RealEnum DIM)
{

  if (myDimension == DIM)
    return;

  Backup();
  myDimension = DIM;
}

TDataStd_RealEnum TDataStd_Real::GetDimension() const
{
  return myDimension;
}

const Standard_GUID& TDataStd_Real::ID() const
{
  return myID;
}

void TDataStd_Real::SetID(const Standard_GUID& theGuid)
{
  if (myID == theGuid)
    return;

  Backup();
  myID = theGuid;
}

void TDataStd_Real::SetID()
{
  Backup();
  myID = GetID();
}

occ::handle<TDF_Attribute> TDataStd_Real::NewEmpty() const
{
  return new TDataStd_Real();
}

void TDataStd_Real::Restore(const occ::handle<TDF_Attribute>& With)
{
  occ::handle<TDataStd_Real> R                      = occ::down_cast<TDataStd_Real>(With);
  myValue                                           = R->Get();
  Standard_DISABLE_DEPRECATION_WARNINGS myDimension = R->GetDimension();
  Standard_ENABLE_DEPRECATION_WARNINGS  myID        = R->ID();
}

void TDataStd_Real::Paste(const occ::handle<TDF_Attribute>& Into,
                          const occ::handle<TDF_RelocationTable>&) const
{
  occ::handle<TDataStd_Real> R = occ::down_cast<TDataStd_Real>(Into);
  R->Set(myValue);
  Standard_DISABLE_DEPRECATION_WARNINGS R->SetDimension(myDimension);
  Standard_ENABLE_DEPRECATION_WARNINGS  R->SetID(myID);
}

Standard_OStream& TDataStd_Real::Dump(Standard_OStream& anOS) const
{
  anOS << "Real ";
  Standard_DISABLE_DEPRECATION_WARNINGS TDataStd::Print(GetDimension(), anOS);
  Standard_ENABLE_DEPRECATION_WARNINGS  anOS << myValue;
  char                                  sguid[Standard_GUID_SIZE_ALLOC];
  myID.ToCString(sguid);
  anOS << sguid;
  return anOS;
}

void TDataStd_Real::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myValue)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myDimension)
}
