

#include <OSD_CachedFileSystem.hpp>
#include <OSD_OpenFile.hpp>

IMPLEMENT_STANDARD_RTTIEXT(OSD_CachedFileSystem, OSD_FileSystem)

OSD_CachedFileSystem::OSD_CachedFileSystem(const occ::handle<OSD_FileSystem>& theLinkedFileSystem)
    : myLinkedFS(!theLinkedFileSystem.IsNull() ? theLinkedFileSystem
                                               : OSD_FileSystem::DefaultFileSystem())
{
}

bool OSD_CachedFileSystem::IsSupportedPath(const TCollection_AsciiString& theUrl) const
{
  return myLinkedFS->IsSupportedPath(theUrl);
}

bool OSD_CachedFileSystem::IsOpenIStream(const std::shared_ptr<std::istream>& theStream) const
{
  return myLinkedFS->IsOpenIStream(theStream);
}

bool OSD_CachedFileSystem::IsOpenOStream(const std::shared_ptr<std::ostream>& theStream) const
{
  return myLinkedFS->IsOpenOStream(theStream);
}

std::shared_ptr<std::istream> OSD_CachedFileSystem::OpenIStream(
  const TCollection_AsciiString& theUrl,
  const std::ios_base::openmode  theParams,
  const int64_t                  theOffset,
  const std::shared_ptr<std::istream>&)
{
  if (myStream.Url != theUrl)
  {
    myStream.Url = theUrl;
    myStream.Reset();
  }
  myStream.Stream = myLinkedFS->OpenIStream(theUrl, theParams, theOffset, myStream.Stream);
  return myStream.Stream;
}

std::shared_ptr<std::ostream> OSD_CachedFileSystem::OpenOStream(
  const TCollection_AsciiString& theUrl,
  const std::ios_base::openmode  theMode)
{
  return myLinkedFS->OpenOStream(theUrl, theMode);
}

std::shared_ptr<std::streambuf> OSD_CachedFileSystem::OpenStreamBuffer(
  const TCollection_AsciiString& theUrl,
  const std::ios_base::openmode  theMode,
  const int64_t                  theOffset,
  int64_t*                       theOutBufSize)
{
  if ((theMode & std::ios::out) == std::ios::out)
  {
    return myLinkedFS->OpenStreamBuffer(theUrl, theMode, theOffset, theOutBufSize);
  }
  if (myStream.Url != theUrl)
  {
    myStream.Url = theUrl;
    myStream.Reset();
  }
  myStream.StreamBuf = myLinkedFS->OpenStreamBuffer(theUrl, theMode, theOffset, theOutBufSize);
  return myStream.StreamBuf;
}
