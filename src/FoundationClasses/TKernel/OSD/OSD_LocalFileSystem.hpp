#pragma once

#include <OSD_FileSystem.hpp>

class OSD_LocalFileSystem : public OSD_FileSystem
{
  DEFINE_STANDARD_RTTIEXT(OSD_LocalFileSystem, OSD_FileSystem)
public:
  OSD_LocalFileSystem() = default;

  Standard_EXPORT bool IsSupportedPath(const TCollection_AsciiString& theUrl) const override;

  Standard_EXPORT bool IsOpenIStream(const std::shared_ptr<std::istream>& theStream) const override;

  Standard_EXPORT bool IsOpenOStream(const std::shared_ptr<std::ostream>& theStream) const override;

  Standard_EXPORT std::shared_ptr<std::streambuf> OpenStreamBuffer(
    const TCollection_AsciiString& theUrl,
    const std::ios_base::openmode  theMode,
    const int64_t                  theOffset     = 0,
    int64_t*                       theOutBufSize = nullptr) override;
};
