

#include <OSD_FileSystemSelector.hpp>

IMPLEMENT_STANDARD_RTTIEXT(OSD_FileSystemSelector, OSD_FileSystem)

void OSD_FileSystemSelector::AddProtocol(const occ::handle<OSD_FileSystem>& theFileSystem,
                                         bool                               theIsPreferred)
{
  myProtocols.Remove(theFileSystem);
  if (theIsPreferred)
  {
    myProtocols.Prepend(theFileSystem);
  }
  else
  {
    myProtocols.Append(theFileSystem);
  }
}

void OSD_FileSystemSelector::RemoveProtocol(const occ::handle<OSD_FileSystem>& theFileSystem)
{
  myProtocols.Remove(theFileSystem);
}

bool OSD_FileSystemSelector::IsSupportedPath(const TCollection_AsciiString& theUrl) const
{
  for (NCollection_List<occ::handle<OSD_FileSystem>>::Iterator aProtIter(myProtocols);
       aProtIter.More();
       aProtIter.Next())
  {
    if (aProtIter.Value()->IsSupportedPath(theUrl))
    {
      return true;
    }
  }
  return false;
}

bool OSD_FileSystemSelector::IsOpenIStream(const std::shared_ptr<std::istream>& theStream) const
{
  std::shared_ptr<OSD_IStreamBuffer> aFileStream =
    std::dynamic_pointer_cast<OSD_IStreamBuffer>(theStream);
  if (aFileStream.get() == nullptr)
  {
    return false;
  }
  for (NCollection_List<occ::handle<OSD_FileSystem>>::Iterator aProtIter(myProtocols);
       aProtIter.More();
       aProtIter.Next())
  {
    const occ::handle<OSD_FileSystem>& aFileSystem = aProtIter.Value();
    if (aFileSystem->IsSupportedPath(TCollection_AsciiString(aFileStream->Url().c_str())))
    {
      if (aFileSystem->IsOpenIStream(theStream))
      {
        return true;
      }
    }
  }
  return false;
}

bool OSD_FileSystemSelector::IsOpenOStream(const std::shared_ptr<std::ostream>& theStream) const
{
  std::shared_ptr<OSD_OStreamBuffer> aFileStream =
    std::dynamic_pointer_cast<OSD_OStreamBuffer>(theStream);
  if (aFileStream.get() == nullptr)
  {
    return false;
  }
  for (NCollection_List<occ::handle<OSD_FileSystem>>::Iterator aProtIter(myProtocols);
       aProtIter.More();
       aProtIter.Next())
  {
    const occ::handle<OSD_FileSystem>& aFileSystem = aProtIter.Value();
    if (aFileSystem->IsSupportedPath(TCollection_AsciiString(aFileStream->Url().c_str())))
    {
      if (aFileSystem->IsOpenOStream(theStream))
      {
        return true;
      }
    }
  }
  return false;
}

std::shared_ptr<std::istream> OSD_FileSystemSelector::OpenIStream(
  const TCollection_AsciiString&       theUrl,
  const std::ios_base::openmode        theMode,
  const int64_t                        theOffset,
  const std::shared_ptr<std::istream>& theOldStream)
{
  for (NCollection_List<occ::handle<OSD_FileSystem>>::Iterator aProtIter(myProtocols);
       aProtIter.More();
       aProtIter.Next())
  {
    const occ::handle<OSD_FileSystem>& aFileSystem = aProtIter.Value();
    if (aFileSystem->IsSupportedPath(theUrl))
    {
      std::shared_ptr<std::istream> aStream =
        aFileSystem->OpenIStream(theUrl, theMode, theOffset, theOldStream);
      if (aStream.get() != nullptr)
      {
        return aStream;
      }
    }
  }
  return std::shared_ptr<std::istream>();
}

std::shared_ptr<std::ostream> OSD_FileSystemSelector::OpenOStream(
  const TCollection_AsciiString& theUrl,
  const std::ios_base::openmode  theMode)
{
  for (NCollection_List<occ::handle<OSD_FileSystem>>::Iterator aProtIter(myProtocols);
       aProtIter.More();
       aProtIter.Next())
  {
    const occ::handle<OSD_FileSystem>& aFileSystem = aProtIter.Value();
    if (aFileSystem->IsSupportedPath(theUrl))
    {
      std::shared_ptr<std::ostream> aStream = aFileSystem->OpenOStream(theUrl, theMode);
      if (aStream.get() != nullptr)
      {
        return aStream;
      }
    }
  }
  return std::shared_ptr<std::ostream>();
}

std::shared_ptr<std::streambuf> OSD_FileSystemSelector::OpenStreamBuffer(
  const TCollection_AsciiString& theUrl,
  const std::ios_base::openmode  theMode,
  const int64_t                  theOffset,
  int64_t*                       theOutBufSize)
{
  for (NCollection_List<occ::handle<OSD_FileSystem>>::Iterator aProtIter(myProtocols);
       aProtIter.More();
       aProtIter.Next())
  {
    const occ::handle<OSD_FileSystem>& aFileSystem = aProtIter.Value();
    if (aFileSystem->IsSupportedPath(theUrl))
    {
      std::shared_ptr<std::streambuf> aBuf =
        aFileSystem->OpenStreamBuffer(theUrl, theMode, theOffset, theOutBufSize);
      if (aBuf.get() != nullptr)
      {
        return aBuf;
      }
    }
  }
  return std::shared_ptr<std::streambuf>();
}
