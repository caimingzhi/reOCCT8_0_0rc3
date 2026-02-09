#include <TDF_TagSource.hpp>

#include <Standard_Dump.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDF_TagSource, TDF_Attribute)

const Standard_GUID& TDF_TagSource::GetID()
{

  static Standard_GUID TDF_TagSourceID("2a96b611-ec8b-11d0-bee7-080009dc3333");
  return TDF_TagSourceID;
}

occ::handle<TDF_TagSource> TDF_TagSource::Set(const TDF_Label& L)
{

  occ::handle<TDF_TagSource> T;
  if (!L.FindAttribute(TDF_TagSource::GetID(), T))
  {
    T = new TDF_TagSource();
    L.AddAttribute(T);
  }
  return T;
}

TDF_Label TDF_TagSource::NewChild(const TDF_Label& L)
{
  occ::handle<TDF_TagSource> T;
  if (!L.FindAttribute(GetID(), T))
  {
    T = new TDF_TagSource();
    L.AddAttribute(T);
  }
  return T->NewChild();
}

TDF_TagSource::TDF_TagSource()
    : myTag(0)
{
}

int TDF_TagSource::NewTag()
{

  Backup();
  return ++myTag;
}

TDF_Label TDF_TagSource::NewChild()
{
  return Label().FindChild(NewTag(), true);
}

int TDF_TagSource::Get() const
{
  return myTag;
}

void TDF_TagSource::Set(const int T)
{

  if (myTag == T)
    return;

  Backup();
  myTag = T;
}

const Standard_GUID& TDF_TagSource::ID() const
{
  return GetID();
}

occ::handle<TDF_Attribute> TDF_TagSource::NewEmpty() const
{
  return new TDF_TagSource();
}

void TDF_TagSource::Restore(const occ::handle<TDF_Attribute>& With)
{
  myTag = occ::down_cast<TDF_TagSource>(With)->Get();
}

void TDF_TagSource::Paste(const occ::handle<TDF_Attribute>& Into,
                          const occ::handle<TDF_RelocationTable>&) const
{
  occ::down_cast<TDF_TagSource>(Into)->Set(myTag);
}

void TDF_TagSource::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myTag)
}
