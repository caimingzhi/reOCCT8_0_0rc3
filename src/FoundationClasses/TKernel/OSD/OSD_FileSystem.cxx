

#include <OSD_FileSystem.hpp>
#include <OSD_FileSystemSelector.hpp>
#include <OSD_LocalFileSystem.hpp>

IMPLEMENT_STANDARD_RTTIEXT(System::os::OSD_FileSystem, Standard_Transient)

static occ::handle<System::os::OSD_FileSystem> createDefaultFileSystem()
{
  occ::handle<System::os::OSD_FileSystemSelector> aSystem = new System::os::OSD_FileSystemSelector();
  aSystem->AddProtocol(new System::os::OSD_LocalFileSystem());
  return aSystem;
}

System::os::OSD_FileSystem::OSD_FileSystem() = default;

System::os::OSD_FileSystem::~OSD_FileSystem() = default;

const occ::handle<System::os::OSD_FileSystem>& System::os::OSD_FileSystem::DefaultFileSystem()
{
  static const occ::handle<System::os::OSD_FileSystem> aDefSystem = createDefaultFileSystem();
  return aDefSystem;
}

void System::os::OSD_FileSystem::AddDefaultProtocol(const occ::handle<System::os::OSD_FileSystem>& theFileSystem,
                                        bool                               theIsPreferred)
{
  occ::handle<System::os::OSD_FileSystemSelector> aFileSelector =
    occ::down_cast<System::os::OSD_FileSystemSelector>(DefaultFileSystem());
  aFileSelector->AddProtocol(theFileSystem, theIsPreferred);
}

void System::os::OSD_FileSystem::RemoveDefaultProtocol(const occ::handle<System::os::OSD_FileSystem>& theFileSystem)
{
  occ::handle<System::os::OSD_FileSystemSelector> aFileSelector =
    occ::down_cast<System::os::OSD_FileSystemSelector>(DefaultFileSystem());
  aFileSelector->RemoveProtocol(theFileSystem);
}

std::shared_ptr<std::istream> System::os::OSD_FileSystem::OpenIStream(
  const TCollection_AsciiString&       theUrl,
  const std::ios_base::openmode        theMode,
  const int64_t                        theOffset,
  const std::shared_ptr<std::istream>& theOldStream)
{
  Standard_ASSERT_RAISE(theOffset >= -1,
                        "Incorrect negative stream position during stream opening");

  std::shared_ptr<std::istream>      aNewStream;
  std::shared_ptr<OSD_IStreamBuffer> anOldStream =
    std::dynamic_pointer_cast<OSD_IStreamBuffer>(theOldStream);
  if (anOldStream.get() != nullptr && theUrl.IsEqual(anOldStream->Url().c_str())
      && IsOpenIStream(anOldStream))
  {
    if (!anOldStream->good())
    {

      anOldStream->clear();
    }
    aNewStream = anOldStream;
    if (theOffset >= 0)
    {
      aNewStream->seekg((std::streamoff)theOffset, std::ios_base::beg);
    }
  }
  if (aNewStream.get() == nullptr)
  {
    std::shared_ptr<std::streambuf> aFileBuf =
      OpenStreamBuffer(theUrl, theMode | std::ios_base::in);
    if (aFileBuf.get() == nullptr)
    {
      return std::shared_ptr<std::istream>();
    }

    aNewStream.reset(new OSD_IStreamBuffer(theUrl.ToCString(), aFileBuf));
    if (theOffset > 0)
    {
      aNewStream->seekg((std::streamoff)theOffset, std::ios_base::beg);
    }
  }
  return aNewStream;
}

std::shared_ptr<std::ostream> System::os::OSD_FileSystem::OpenOStream(const TCollection_AsciiString& theUrl,
                                                          const std::ios_base::openmode  theMode)
{
  std::shared_ptr<std::ostream>   aNewStream;
  std::shared_ptr<std::streambuf> aFileBuf = OpenStreamBuffer(theUrl, theMode | std::ios_base::out);
  if (aFileBuf.get() == nullptr)
  {
    return std::shared_ptr<std::ostream>();
  }

  aNewStream.reset(new OSD_OStreamBuffer(theUrl.ToCString(), aFileBuf));
  return aNewStream;
}
