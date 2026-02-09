#include <TDocStd_XLinkRoot.hpp>

#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Data.hpp>
#include <TDF_RelocationTable.hpp>
#include <TDocStd_XLink.hpp>
#include <TDocStd_XLinkIterator.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDocStd_XLinkRoot, TDF_Attribute)

const Standard_GUID& TDocStd_XLinkRoot::GetID()
{
  static Standard_GUID myID("5d587401-5690-11d1-8940-080009dc3333");
  return myID;
}

occ::handle<TDocStd_XLinkRoot> TDocStd_XLinkRoot::Set(const occ::handle<TDF_Data>& aDF)
{
  occ::handle<TDocStd_XLinkRoot> xRefRoot;
  if (!aDF->Root().FindAttribute(TDocStd_XLinkRoot::GetID(), xRefRoot))
  {
    xRefRoot = new TDocStd_XLinkRoot;
    aDF->Root().AddAttribute(xRefRoot);
  }
  return xRefRoot;
}

void TDocStd_XLinkRoot::Insert(const TDocStd_XLinkPtr& anXLinkPtr)
{
  occ::handle<TDocStd_XLinkRoot> xRefRoot = TDocStd_XLinkRoot::Set(anXLinkPtr->Label().Data());

  anXLinkPtr->Next(xRefRoot->First());
  xRefRoot->First(anXLinkPtr);
}

void TDocStd_XLinkRoot::Remove(const TDocStd_XLinkPtr& anXLinkPtr)
{
  occ::handle<TDocStd_XLinkRoot> xRefRoot;
  if (anXLinkPtr->Label().Root().FindAttribute(TDocStd_XLinkRoot::GetID(), xRefRoot))
  {
    TDocStd_XLink* previous = xRefRoot->First();
    if (previous == anXLinkPtr)
    {
      xRefRoot->First(anXLinkPtr->Next());
      previous = nullptr;
      anXLinkPtr->Next(previous);
    }
    else
    {
      while (previous != nullptr && previous->Next() != anXLinkPtr)
        previous = previous->Next();
      if (previous != nullptr)
      {
        previous->Next(anXLinkPtr->Next());
        previous = nullptr;
        anXLinkPtr->Next(previous);
      }
    }
  }
}

TDocStd_XLinkRoot::TDocStd_XLinkRoot()
    : myFirst(nullptr)
{
}

const Standard_GUID& TDocStd_XLinkRoot::ID() const
{
  return GetID();
}

occ::handle<TDF_Attribute> TDocStd_XLinkRoot::BackupCopy() const
{
  return new TDocStd_XLinkRoot;
}

void TDocStd_XLinkRoot::Restore(const occ::handle<TDF_Attribute>&) {}

occ::handle<TDF_Attribute> TDocStd_XLinkRoot::NewEmpty() const
{
  return new TDocStd_XLinkRoot;
}

void TDocStd_XLinkRoot::Paste(const occ::handle<TDF_Attribute>&,
                              const occ::handle<TDF_RelocationTable>&) const
{
}

Standard_OStream& TDocStd_XLinkRoot::Dump(Standard_OStream& anOS) const
{
  return anOS;
}
