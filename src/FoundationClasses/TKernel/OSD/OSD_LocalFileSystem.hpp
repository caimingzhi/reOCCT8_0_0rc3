#pragma once

#include <OSD_FileSystem.hpp>

//! A file system opening local files (or files from mount systems).
class OSD_LocalFileSystem : public OSD_FileSystem
{
  DEFINE_STANDARD_RTTIEXT(OSD_LocalFileSystem, OSD_FileSystem)
public:
  //! Constructor.
  OSD_LocalFileSystem() = default;

  //! Returns TRUE if URL defines a supported protocol.
  Standard_EXPORT bool IsSupportedPath(const TCollection_AsciiString& theUrl) const override;

  //! Returns TRUE if current input stream is opened for reading operations.
  Standard_EXPORT bool IsOpenIStream(const std::shared_ptr<std::istream>& theStream) const override;

  //! Returns TRUE if current output stream is opened for writing operations.
  Standard_EXPORT bool IsOpenOStream(const std::shared_ptr<std::ostream>& theStream) const override;

  //! Opens stream buffer for specified file URL.
  Standard_EXPORT std::shared_ptr<std::streambuf> OpenStreamBuffer(
    const TCollection_AsciiString& theUrl,
    const std::ios_base::openmode  theMode,
    const int64_t                  theOffset     = 0,
    int64_t*                       theOutBufSize = nullptr) override;
};
