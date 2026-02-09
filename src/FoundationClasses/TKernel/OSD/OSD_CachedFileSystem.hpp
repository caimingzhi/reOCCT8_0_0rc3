#pragma once

#include <OSD_FileSystem.hpp>

class OSD_CachedFileSystem : public OSD_FileSystem
{
  DEFINE_STANDARD_RTTIEXT(OSD_CachedFileSystem, OSD_FileSystem)
public:
  Standard_EXPORT OSD_CachedFileSystem(
    const occ::handle<OSD_FileSystem>& theLinkedFileSystem = occ::handle<OSD_FileSystem>());

  const occ::handle<OSD_FileSystem>& LinkedFileSystem() const { return myLinkedFS; }

  void SetLinkedFileSystem(const occ::handle<OSD_FileSystem>& theLinkedFileSystem)
  {
    myLinkedFS = theLinkedFileSystem;
  }

  Standard_EXPORT bool IsSupportedPath(const TCollection_AsciiString& theUrl) const override;

  Standard_EXPORT bool IsOpenIStream(const std::shared_ptr<std::istream>& theStream) const override;

  Standard_EXPORT bool IsOpenOStream(const std::shared_ptr<std::ostream>& theStream) const override;

  Standard_EXPORT std::shared_ptr<std::istream> OpenIStream(
    const TCollection_AsciiString&       theUrl,
    const std::ios_base::openmode        theParams,
    const int64_t                        theOffset,
    const std::shared_ptr<std::istream>& theOldStream) override;

  Standard_EXPORT std::shared_ptr<std::ostream> OpenOStream(
    const TCollection_AsciiString& theUrl,
    const std::ios_base::openmode  theMode) override;

  Standard_EXPORT std::shared_ptr<std::streambuf> OpenStreamBuffer(
    const TCollection_AsciiString& theUrl,
    const std::ios_base::openmode  theMode,
    const int64_t                  theOffset     = 0,
    int64_t*                       theOutBufSize = nullptr) override;

protected:
  struct OSD_CachedStream
  {
    TCollection_AsciiString         Url;
    std::shared_ptr<std::istream>   Stream;
    std::shared_ptr<std::streambuf> StreamBuf;

    void Reset()
    {
      Stream.reset();
      StreamBuf.reset();
    }
  };

protected:
  OSD_CachedStream            myStream;
  occ::handle<OSD_FileSystem> myLinkedFS;
};
