

#include <Standard_ErrorHandler.hpp>
#include <Storage_TypeData.hpp>
#include <Storage_BaseDriver.hpp>
#include <Storage_StreamTypeMismatchError.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(app::storage::Storage_TypeData, Standard_Transient)

app::storage::Storage_TypeData::Storage_TypeData()
    : myErrorStatus(Storage_VSOk)
{
}

bool app::storage::Storage_TypeData::Read(const occ::handle<app::storage::Storage_BaseDriver>& theDriver)
{

  if (theDriver->OpenMode() != Storage_VSRead && theDriver->OpenMode() != Storage_VSReadWrite)
  {
    myErrorStatus    = Storage_VSModeError;
    myErrorStatusExt = "OpenMode";
    return false;
  }

  myErrorStatus = theDriver->BeginReadTypeSection();
  if (myErrorStatus != Storage_VSOk)
  {
    myErrorStatusExt = "BeginReadTypeSection";
    return false;
  }

  int                     aTypeNum;
  TCollection_AsciiString aTypeName;

  int len = theDriver->TypeSectionSize();
  for (int i = 1; i <= len; i++)
  {
    try
    {
      OCC_CATCH_SIGNALS
      theDriver->ReadTypeInformations(aTypeNum, aTypeName);
    }
    catch (const app::storage::Storage_StreamTypeMismatchError&)
    {
      myErrorStatus    = Storage_VSTypeMismatch;
      myErrorStatusExt = "ReadTypeInformations";
      return false;
    }

    myPt.Add(aTypeName, aTypeNum);
  }

  myErrorStatus = theDriver->EndReadTypeSection();
  if (myErrorStatus != Storage_VSOk)
  {
    myErrorStatusExt = "EndReadTypeSection";
    return false;
  }

  return true;
}

int app::storage::Storage_TypeData::NumberOfTypes() const
{
  return myPt.Extent();
}

bool app::storage::Storage_TypeData::IsType(const TCollection_AsciiString& aName) const
{
  return myPt.Contains(aName);
}

occ::handle<NCollection_HSequence<TCollection_AsciiString>> app::storage::Storage_TypeData::Types() const
{
  occ::handle<NCollection_HSequence<TCollection_AsciiString>> r =
    new NCollection_HSequence<TCollection_AsciiString>;
  int i;

  for (i = 1; i <= myPt.Extent(); i++)
  {
    r->Append(myPt.FindKey(i));
  }

  return r;
}

void app::storage::Storage_TypeData::AddType(const TCollection_AsciiString& aName, const int aTypeNum)
{
  myPt.Add(aName, aTypeNum);
}

TCollection_AsciiString app::storage::Storage_TypeData::Type(const int aTypeNum) const
{
  TCollection_AsciiString r;

  if (aTypeNum <= myPt.Extent() && aTypeNum > 0)
  {
    r = myPt.FindKey(aTypeNum);
  }
  else
  {
    throw Standard_NoSuchObject("app::storage::Storage_TypeData::Type - aTypeNum not in range");
  }

  return r;
}

int app::storage::Storage_TypeData::Type(const TCollection_AsciiString& aTypeName) const
{
  int r = 0;

  if (myPt.Contains(aTypeName))
  {
    r = myPt.FindFromKey(aTypeName);
  }
  else
  {
    throw Standard_NoSuchObject("app::storage::Storage_TypeData::Type - aTypeName not found");
  }

  return r;
}

void app::storage::Storage_TypeData::Clear()
{
  myPt.Clear();
}

Storage_Error app::storage::Storage_TypeData::ErrorStatus() const
{
  return myErrorStatus;
}

void app::storage::Storage_TypeData::SetErrorStatus(const Storage_Error anError)
{
  myErrorStatus = anError;
}

void app::storage::Storage_TypeData::ClearErrorStatus()
{
  myErrorStatus = Storage_VSOk;
  myErrorStatusExt.Clear();
}

TCollection_AsciiString app::storage::Storage_TypeData::ErrorStatusExtension() const
{
  return myErrorStatusExt;
}

void app::storage::Storage_TypeData::SetErrorStatusExtension(const TCollection_AsciiString& anErrorExt)
{
  myErrorStatusExt = anErrorExt;
}
