#pragma once

#include <OSD_FileSystem.hpp>

#include <NCollection_List.hpp>

class OSD_FileSystemSelector : public OSD_FileSystem
{
  DEFINE_STANDARD_RTTIEXT(OSD_FileSystemSelector, OSD_FileSystem)
public:
  OSD_FileSystemSelector() = default;

  Standard_EXPORT void AddProtocol(const occ::handle<OSD_FileSystem>& theFileSystem,
                                   bool                               theIsPreferred = false);

  Standard_EXPORT void RemoveProtocol(const occ::handle<OSD_FileSystem>& theFileSystem);

public:
  Standard_EXPORT bool IsSupportedPath(const TCollection_AsciiString& theUrl) const override;

  Standard_EXPORT bool IsOpenIStream(const std::shared_ptr<std::istream>& theStream) const override;

  Standard_EXPORT bool IsOpenOStream(const std::shared_ptr<std::ostream>& theStream) const override;

  Standard_EXPORT std::shared_ptr<std::istream> OpenIStream(
    const TCollection_AsciiString&       theUrl,
    const std::ios_base::openmode        theMode,
    const int64_t                        theOffset    = 0,
    const std::shared_ptr<std::istream>& theOldStream = std::shared_ptr<std::istream>()) override;

  Standard_EXPORT std::shared_ptr<std::ostream> OpenOStream(
    const TCollection_AsciiString& theUrl,
    const std::ios_base::openmode  theMode) override;

  Standard_EXPORT std::shared_ptr<std::streambuf> OpenStreamBuffer(
    const TCollection_AsciiString& theUrl,
    const std::ios_base::openmode  theMode,
    const int64_t                  theOffset     = 0,
    int64_t*                       theOutBufSize = nullptr) override;

protected:
  NCollection_List<occ::handle<OSD_FileSystem>> myProtocols;
};
