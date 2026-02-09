#pragma once

#include <OSD_StreamBuffer.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_DefineAlloc.hpp>

class OSD_FileSystem : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(OSD_FileSystem, Standard_Transient)
public:
  Standard_EXPORT static const occ::handle<OSD_FileSystem>& DefaultFileSystem();

  Standard_EXPORT static void AddDefaultProtocol(const occ::handle<OSD_FileSystem>& theFileSystem,
                                                 bool theIsPreferred = false);

  Standard_EXPORT static void RemoveDefaultProtocol(
    const occ::handle<OSD_FileSystem>& theFileSystem);

public:
  virtual bool IsSupportedPath(const TCollection_AsciiString& theUrl) const = 0;

  virtual bool IsOpenIStream(const std::shared_ptr<std::istream>& theStream) const = 0;

  virtual bool IsOpenOStream(const std::shared_ptr<std::ostream>& theStream) const = 0;

  Standard_EXPORT virtual std::shared_ptr<std::istream> OpenIStream(
    const TCollection_AsciiString&       theUrl,
    const std::ios_base::openmode        theMode,
    const int64_t                        theOffset    = 0,
    const std::shared_ptr<std::istream>& theOldStream = std::shared_ptr<std::istream>());

  Standard_EXPORT virtual std::shared_ptr<std::ostream> OpenOStream(
    const TCollection_AsciiString& theUrl,
    const std::ios_base::openmode  theMode);

  virtual std::shared_ptr<std::streambuf> OpenStreamBuffer(const TCollection_AsciiString& theUrl,
                                                           const std::ios_base::openmode  theMode,
                                                           const int64_t theOffset = 0,
                                                           int64_t* theOutBufSize  = nullptr) = 0;

  Standard_EXPORT OSD_FileSystem();

  Standard_EXPORT ~OSD_FileSystem() override;
};
