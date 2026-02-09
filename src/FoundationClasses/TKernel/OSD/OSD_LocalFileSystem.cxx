

#include <OSD_LocalFileSystem.hpp>
#include <OSD_OpenFile.hpp>
#include <OSD_Path.hpp>
#include <Standard_Assert.hpp>

IMPLEMENT_STANDARD_RTTIEXT(OSD_LocalFileSystem, OSD_FileSystem)

bool OSD_LocalFileSystem::IsSupportedPath(const TCollection_AsciiString& theUrl) const
{
  return !OSD_Path::IsRemoteProtocolPath(theUrl.ToCString());
}

bool OSD_LocalFileSystem::IsOpenIStream(const std::shared_ptr<std::istream>& theStream) const
{
  std::shared_ptr<OSD_IStreamBuffer> aFileStream =
    std::dynamic_pointer_cast<OSD_IStreamBuffer>(theStream);
  if (aFileStream.get() == nullptr)
  {
    return false;
  }
  const std::filebuf* aFileBuf = dynamic_cast<const std::filebuf*>(aFileStream->rdbuf());
  return (aFileBuf != nullptr) ? aFileBuf->is_open() : false;
}

bool OSD_LocalFileSystem::IsOpenOStream(const std::shared_ptr<std::ostream>& theStream) const
{
  std::shared_ptr<OSD_OStreamBuffer> aFileStream =
    std::dynamic_pointer_cast<OSD_OStreamBuffer>(theStream);
  if (aFileStream.get() == nullptr)
  {
    return false;
  }
  const std::filebuf* aFileBuf = dynamic_cast<const std::filebuf*>(aFileStream->rdbuf());
  return (aFileBuf != nullptr) ? aFileBuf->is_open() : false;
}

std::shared_ptr<std::streambuf> OSD_LocalFileSystem::OpenStreamBuffer(
  const TCollection_AsciiString& theUrl,
  const std::ios_base::openmode  theMode,
  const int64_t                  theOffset,
  int64_t*                       theOutBufSize)
{
  Standard_ASSERT_RAISE(theOffset >= 0,
                        "Incorrect negative stream position during stream buffer opening");
  std::shared_ptr<std::filebuf> aNewBuf(new std::filebuf());
  if (!OSD_OpenStream(*aNewBuf, TCollection_ExtendedString(theUrl), theMode))
  {
    return std::shared_ptr<std::streambuf>();
  }

  if (theOutBufSize && ((theMode & std::ios::in) != 0))
  {
    *theOutBufSize = (int64_t)aNewBuf->pubseekoff(0, std::ios_base::end, std::ios_base::in);
    if (aNewBuf->pubseekoff((std::streamoff)theOffset, std::ios_base::beg, std::ios_base::in) < 0)
    {
      *theOutBufSize = 0;
      return std::shared_ptr<std::streambuf>();
    }
  }
  else if (theOffset > 0
           && aNewBuf->pubseekoff((std::streamoff)theOffset,
                                  std::ios_base::beg,
                                  (theMode & std::ios::in) != 0 ? std::ios_base::in
                                                                : std::ios_base::out)
                < 0)
  {
    return std::shared_ptr<std::streambuf>();
  }
  return aNewBuf;
}
