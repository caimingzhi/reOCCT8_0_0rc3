#pragma once

#include <OSD_FileSystem.hpp>

#include <NCollection_List.hpp>

//! File system implementation which tried to open stream using registered list of file systems.
class OSD_FileSystemSelector : public OSD_FileSystem
{
  DEFINE_STANDARD_RTTIEXT(OSD_FileSystemSelector, OSD_FileSystem)
public:
  //! Constructor.
  OSD_FileSystemSelector() = default;

  //! Registers file system within this selector.
  //! @param[in] theFileSystem   file system to register
  //! @param[in] theIsPreferred  add to the beginning of the list when TRUE, or add to the end
  //! otherwise
  Standard_EXPORT void AddProtocol(const occ::handle<OSD_FileSystem>& theFileSystem,
                                   bool                               theIsPreferred = false);

  //! Unregisters file system within this selector.
  Standard_EXPORT void RemoveProtocol(const occ::handle<OSD_FileSystem>& theFileSystem);

public:
  //! Returns TRUE if URL defines a supported protocol.
  Standard_EXPORT bool IsSupportedPath(const TCollection_AsciiString& theUrl) const override;

  //! Returns TRUE if current input stream is opened for reading operations.
  Standard_EXPORT bool IsOpenIStream(const std::shared_ptr<std::istream>& theStream) const override;

  //! Returns TRUE if current output stream is opened for writing operations.
  Standard_EXPORT bool IsOpenOStream(const std::shared_ptr<std::ostream>& theStream) const override;

  //! Opens input stream using one of registered protocols.
  Standard_EXPORT std::shared_ptr<std::istream> OpenIStream(
    const TCollection_AsciiString&       theUrl,
    const std::ios_base::openmode        theMode,
    const int64_t                        theOffset    = 0,
    const std::shared_ptr<std::istream>& theOldStream = std::shared_ptr<std::istream>()) override;

  //! Opens output stream using one of registered protocols.
  Standard_EXPORT std::shared_ptr<std::ostream> OpenOStream(
    const TCollection_AsciiString& theUrl,
    const std::ios_base::openmode  theMode) override;

  //! Opens stream buffer using one of registered protocols.
  Standard_EXPORT std::shared_ptr<std::streambuf> OpenStreamBuffer(
    const TCollection_AsciiString& theUrl,
    const std::ios_base::openmode  theMode,
    const int64_t                  theOffset     = 0,
    int64_t*                       theOutBufSize = nullptr) override;

protected:
  NCollection_List<occ::handle<OSD_FileSystem>> myProtocols;
};
