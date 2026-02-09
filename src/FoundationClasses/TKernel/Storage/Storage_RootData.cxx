

#include <Standard_Persistent.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Storage_RootData.hpp>
#include <Storage_Root.hpp>
#include <Storage_BaseDriver.hpp>
#include <Storage_StreamTypeMismatchError.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_DataMap.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Storage_RootData, Standard_Transient)

Storage_RootData::Storage_RootData()
    : myErrorStatus(Storage_VSOk)
{
}

bool Storage_RootData::Read(const occ::handle<Storage_BaseDriver>& theDriver)
{

  if (theDriver->OpenMode() != Storage_VSRead && theDriver->OpenMode() != Storage_VSReadWrite)
  {
    myErrorStatus    = Storage_VSModeError;
    myErrorStatusExt = "OpenMode";
    return false;
  }

  myErrorStatus = theDriver->BeginReadRootSection();
  if (myErrorStatus != Storage_VSOk)
  {
    myErrorStatusExt = "BeginReadRootSection";
    return false;
  }

  TCollection_AsciiString aRootName, aTypeName;
  int                     aRef;

  int len = theDriver->RootSectionSize();
  for (int i = 1; i <= len; i++)
  {
    try
    {
      OCC_CATCH_SIGNALS
      theDriver->ReadRoot(aRootName, aRef, aTypeName);
    }
    catch (Storage_StreamTypeMismatchError const&)
    {
      myErrorStatus    = Storage_VSTypeMismatch;
      myErrorStatusExt = "ReadRoot";
      return false;
    }

    occ::handle<Storage_Root> aRoot = new Storage_Root(aRootName, aRef, aTypeName);
    myObjects.Bind(aRootName, aRoot);
  }

  myErrorStatus = theDriver->EndReadRootSection();
  if (myErrorStatus != Storage_VSOk)
  {
    myErrorStatusExt = "EndReadRootSection";
    return false;
  }

  return true;
}

int Storage_RootData::NumberOfRoots() const
{
  return myObjects.Extent();
}

void Storage_RootData::AddRoot(const occ::handle<Storage_Root>& aRoot)
{
  myObjects.Bind(aRoot->Name(), aRoot);
}

occ::handle<NCollection_HSequence<occ::handle<Storage_Root>>> Storage_RootData::Roots() const
{
  occ::handle<NCollection_HSequence<occ::handle<Storage_Root>>> anObjectsSeq =
    new NCollection_HSequence<occ::handle<Storage_Root>>;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Storage_Root>>::Iterator it(myObjects);

  for (; it.More(); it.Next())
  {
    anObjectsSeq->Append(it.Value());
  }

  return anObjectsSeq;
}

occ::handle<Storage_Root> Storage_RootData::Find(const TCollection_AsciiString& aName) const
{
  occ::handle<Storage_Root> p;

  if (myObjects.IsBound(aName))
  {
    p = myObjects.Find(aName);
  }

  return p;
}

bool Storage_RootData::IsRoot(const TCollection_AsciiString& aName) const
{
  return myObjects.IsBound(aName);
}

void Storage_RootData::RemoveRoot(const TCollection_AsciiString& aName)
{
  if (myObjects.IsBound(aName))
  {
    myObjects.UnBind(aName);
  }
}

void Storage_RootData::UpdateRoot(const TCollection_AsciiString&          aName,
                                  const occ::handle<Standard_Persistent>& aPers)
{
  if (myObjects.IsBound(aName))
  {
    myObjects.ChangeFind(aName)->SetObject(aPers);
  }
  else
  {
    throw Standard_NoSuchObject();
  }
}

Storage_Error Storage_RootData::ErrorStatus() const
{
  return myErrorStatus;
}

void Storage_RootData::SetErrorStatus(const Storage_Error anError)
{
  myErrorStatus = anError;
}

void Storage_RootData::ClearErrorStatus()
{
  myErrorStatus = Storage_VSOk;
  myErrorStatusExt.Clear();
}

TCollection_AsciiString Storage_RootData::ErrorStatusExtension() const
{
  return myErrorStatusExt;
}

void Storage_RootData::SetErrorStatusExtension(const TCollection_AsciiString& anErrorExt)
{
  myErrorStatusExt = anErrorExt;
}
