#include <XCAFDoc_Location.hpp>

#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>
#include <TopLoc_Location.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XCAFDoc_Location, TDF_Attribute)

XCAFDoc_Location::XCAFDoc_Location() = default;

const Standard_GUID& XCAFDoc_Location::GetID()
{
  static Standard_GUID LocationID("efd212ef-6dfd-11d4-b9c8-0060b0ee281b");
  return LocationID;
}

occ::handle<XCAFDoc_Location> XCAFDoc_Location::Set(const TDF_Label& L, const TopLoc_Location& Loc)
{
  occ::handle<XCAFDoc_Location> A;
  if (!L.FindAttribute(XCAFDoc_Location::GetID(), A))
  {
    A = new XCAFDoc_Location();
    L.AddAttribute(A);
  }
  A->Set(Loc);
  return A;
}

void XCAFDoc_Location::Set(const TopLoc_Location& Loc)
{
  Backup();
  myLocation = Loc;
}

const TopLoc_Location& XCAFDoc_Location::Get() const
{
  return myLocation;
}

const Standard_GUID& XCAFDoc_Location::ID() const
{
  return GetID();
}

void XCAFDoc_Location::Restore(const occ::handle<TDF_Attribute>& With)
{
  myLocation = occ::down_cast<XCAFDoc_Location>(With)->Get();
}

occ::handle<TDF_Attribute> XCAFDoc_Location::NewEmpty() const
{
  return new XCAFDoc_Location();
}

void XCAFDoc_Location::Paste(const occ::handle<TDF_Attribute>& Into,
                             const occ::handle<TDF_RelocationTable>&) const
{
  occ::down_cast<XCAFDoc_Location>(Into)->Set(myLocation);
}

void XCAFDoc_Location::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myLocation)
}
