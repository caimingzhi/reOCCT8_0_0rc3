#include <OSD_Environment.hpp>
#include <OSD_FileIterator.hpp>
#include <OSD_Host.hpp>
#include <OSD_Path.hpp>
#include <OSD_Protection.hpp>
#include <OSD_SingleProtection.hpp>
#include <Resource_Manager.hpp>
#include <Resource_Unicode.hpp>
#include <Standard_GUID.hpp>
#include <Storage_BaseDriver.hpp>
#include <Storage_Data.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>
#include <UTL.hpp>

TCollection_ExtendedString UTL::xgetenv(const char* aCString)
{
  TCollection_ExtendedString x;
  OSD_Environment            theEnv(aCString);
  TCollection_AsciiString    theValue = theEnv.Value();
  if (!theValue.IsEmpty())
    x = TCollection_ExtendedString(theValue);
  return x;
}

TCollection_ExtendedString UTL::Extension(const TCollection_ExtendedString& aFileName)
{
  TCollection_AsciiString aFileNameU(aFileName);
  OSD_Path                p            = OSD_Path(aFileNameU);
  TCollection_AsciiString theExtension = p.Extension();
  if (theExtension.Value(1) == '.')
    theExtension.Remove(1, 1);
  return TCollection_ExtendedString(theExtension);
}

Storage_Error UTL::OpenFile(const occ::handle<Storage_BaseDriver>& aDriver,
                            const TCollection_ExtendedString&      aFileName,
                            const Storage_OpenMode                 aMode)
{
  return aDriver->Open(TCollection_AsciiString(aFileName), aMode);
}

void UTL::AddToUserInfo(const occ::handle<Storage_Data>&  aData,
                        const TCollection_ExtendedString& anInfo)
{
  aData->AddToUserInfo(TCollection_AsciiString(anInfo));
}

OSD_Path UTL::Path(const TCollection_ExtendedString& aFileName)
{
  OSD_Path p = OSD_Path(TCollection_AsciiString(aFileName));
  return p;
}

TCollection_ExtendedString UTL::Disk(const OSD_Path& aPath)
{
  return TCollection_ExtendedString(aPath.Disk());
}

TCollection_ExtendedString UTL::Trek(const OSD_Path& aPath)
{
  return TCollection_ExtendedString(aPath.Trek());
}

TCollection_ExtendedString UTL::Name(const OSD_Path& aPath)
{
  return TCollection_ExtendedString(aPath.Name());
}

TCollection_ExtendedString UTL::Extension(const OSD_Path& aPath)
{
  return TCollection_ExtendedString(aPath.Extension());
}

OSD_FileIterator UTL::FileIterator(const OSD_Path& aPath, const TCollection_ExtendedString& aMask)
{
  OSD_FileIterator it = OSD_FileIterator(aPath, TCollection_AsciiString(aMask));
  return it;
}

TCollection_ExtendedString UTL::LocalHost()
{
  OSD_Host h;
  return TCollection_ExtendedString(h.HostName());
}

TCollection_ExtendedString UTL::ExtendedString(const TCollection_AsciiString& anAsciiString)
{
  return TCollection_ExtendedString(anAsciiString);
}

Standard_GUID UTL::GUID(const TCollection_ExtendedString& anXString)
{
  return Standard_GUID(TCollection_AsciiString(anXString, '?').ToCString());
}

bool UTL::Find(const occ::handle<Resource_Manager>& aResourceManager,
               const TCollection_ExtendedString&    aResourceName)
{
  return aResourceManager->Find(TCollection_AsciiString(aResourceName).ToCString());
}

TCollection_ExtendedString UTL::Value(const occ::handle<Resource_Manager>& aResourceManager,
                                      const TCollection_ExtendedString&    aResourceName)
{
  TCollection_AsciiString aResourceNameU(aResourceName);
  return TCollection_ExtendedString(aResourceManager->Value(aResourceNameU.ToCString()), true);
}

int UTL::IntegerValue(const TCollection_ExtendedString& anExtendedString)
{
  TCollection_AsciiString a(anExtendedString);
  return a.IntegerValue();
}

const char* UTL::CString(const TCollection_ExtendedString& anExtendedString)
{
  static TCollection_AsciiString theValue;
  theValue = TCollection_AsciiString(anExtendedString);
  return theValue.ToCString();
}

bool UTL::IsReadOnly(const TCollection_ExtendedString& aFileName)
{
  switch (OSD_File(UTL::Path(aFileName)).Protection().User())
  {
    case OSD_W:
    case OSD_RW:
    case OSD_WX:
    case OSD_RWX:
    case OSD_RWD:
    case OSD_WXD:
    case OSD_RWXD:
      return false;
    default:
      return true;
  }
}
