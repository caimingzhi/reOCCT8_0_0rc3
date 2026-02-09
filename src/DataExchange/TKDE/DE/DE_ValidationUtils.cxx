

#include <DE_ValidationUtils.hpp>

#include <Message.hpp>
#include <NCollection_Buffer.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <OSD_FileSystem.hpp>
#include <OSD_Path.hpp>
#include <OSD_File.hpp>
#include <OSD_Protection.hpp>
#include <fstream>

bool DE_ValidationUtils::ValidateConfigurationNode(
  const occ::handle<DE_ConfigurationNode>& theNode,
  const occ::handle<Standard_Type>&        theExpectedType,
  const TCollection_AsciiString&           theContext,
  const bool                               theIsVerbose)
{
  if (theNode.IsNull())
  {
    if (theIsVerbose)
    {
      Message::SendFail() << "Error during " << theContext << ": Configuration Node is null";
    }
    return false;
  }

  if (!theNode->IsKind(theExpectedType))
  {
    if (theIsVerbose)
    {
      Message::SendFail() << "Error during " << theContext
                          << ": Configuration Node is not of expected type. Expected: "
                          << theExpectedType->Name() << ", got: " << theNode->DynamicType()->Name();
    }
    return false;
  }

  return true;
}

bool DE_ValidationUtils::ValidateFileForReading(const TCollection_AsciiString& thePath,
                                                const TCollection_AsciiString& theContext,
                                                const bool                     theIsVerbose)
{
  if (thePath.IsEmpty())
  {
    if (theIsVerbose)
    {
      Message::SendFail() << "Error during " << theContext << ": File path is empty";
    }
    return false;
  }

  try
  {
    OSD_Path aOSDPath(thePath);
    OSD_File aFile(aOSDPath);

    if (!aFile.Exists())
    {
      if (theIsVerbose)
      {
        Message::SendFail() << "Error during " << theContext << ": File '" << thePath
                            << "' does not exist";
      }
      return false;
    }

    std::ifstream aTestFile(thePath.ToCString());
    if (!aTestFile.is_open() || !aTestFile.good())
    {
      if (theIsVerbose)
      {
        Message::SendFail() << "Error during " << theContext << ": Cannot open file '" << thePath
                            << "' for reading";
      }
      return false;
    }
  }
  catch (const std::exception& anException)
  {
    if (theIsVerbose)
    {
      Message::SendFail() << "Error during " << theContext << ": Cannot access file '" << thePath
                          << "': " << anException.what();
    }
    return false;
  }

  return true;
}

bool DE_ValidationUtils::ValidateFileForWriting(const TCollection_AsciiString& thePath,
                                                const TCollection_AsciiString& theContext,
                                                const bool                     theIsVerbose)
{
  if (thePath.IsEmpty())
  {
    if (theIsVerbose)
    {
      Message::SendFail() << "Error during " << theContext << ": File path is empty";
    }
    return false;
  }

  try
  {

    std::ofstream aTestFile(thePath.ToCString(), std::ios::out | std::ios::app);
    if (!aTestFile.is_open() || !aTestFile.good())
    {
      if (theIsVerbose)
      {
        Message::SendFail() << "Error during " << theContext << ": Cannot open file '" << thePath
                            << "' for writing";
      }
      return false;
    }
  }
  catch (const std::exception& anException)
  {
    if (theIsVerbose)
    {
      Message::SendFail() << "Error during " << theContext << ": Cannot access file '" << thePath
                          << "': " << anException.what();
    }
    return false;
  }

  return true;
}

bool DE_ValidationUtils::ValidateReadStreamList(const DE_Provider::ReadStreamList& theStreams,
                                                const TCollection_AsciiString&     theContext,
                                                const bool                         theIsVerbose)
{
  if (theStreams.IsEmpty())
  {
    if (theIsVerbose)
    {
      Message::SendFail() << "Error during " << theContext << ": Stream list is empty";
    }
    return false;
  }

  if (theStreams.Size() > 1)
  {
    if (theIsVerbose)
    {
      Message::SendWarning() << "Warning during " << theContext << ": Received "
                             << theStreams.Size() << " streams, using only the first one";
    }
  }

  try
  {
    const DE_Provider::ReadStreamNode& aNode = theStreams.First();
    if (aNode.Stream.fail())
    {
      if (theIsVerbose)
      {
        TCollection_AsciiString aKeyInfo = aNode.Path.IsEmpty() ? "<empty path>" : aNode.Path;
        Message::SendFail() << "Error during " << theContext << ": Input stream '" << aKeyInfo
                            << "' is in invalid state";
      }
      return false;
    }
  }
  catch (const std::exception&)
  {
    if (theIsVerbose)
    {
      const DE_Provider::ReadStreamNode& aNode = theStreams.First();
      TCollection_AsciiString aKeyInfo         = aNode.Path.IsEmpty() ? "<empty path>" : aNode.Path;
      Message::SendFail() << "Error during " << theContext << ": Cannot access input stream '"
                          << aKeyInfo << "'";
    }
    return false;
  }

  return true;
}

bool DE_ValidationUtils::ValidateWriteStreamList(DE_Provider::WriteStreamList&  theStreams,
                                                 const TCollection_AsciiString& theContext,
                                                 const bool                     theIsVerbose)
{
  if (theStreams.IsEmpty())
  {
    if (theIsVerbose)
    {
      Message::SendFail() << "Error during " << theContext << ": Stream list is empty";
    }
    return false;
  }

  if (theStreams.Size() > 1)
  {
    if (theIsVerbose)
    {
      Message::SendWarning() << "Warning during " << theContext << ": Received "
                             << theStreams.Size() << " streams, using only the first one";
    }
  }

  try
  {
    const DE_Provider::WriteStreamNode& aNode = theStreams.First();
    if (aNode.Stream.fail())
    {
      if (theIsVerbose)
      {
        TCollection_AsciiString aKeyInfo = aNode.Path.IsEmpty() ? "<empty path>" : aNode.Path;
        Message::SendFail() << "Error during " << theContext << ": Output stream '" << aKeyInfo
                            << "' is in invalid state";
      }
      return false;
    }
  }
  catch (const std::exception&)
  {
    if (theIsVerbose)
    {
      const DE_Provider::WriteStreamNode& aNode = theStreams.First();
      TCollection_AsciiString aKeyInfo = aNode.Path.IsEmpty() ? "<empty path>" : aNode.Path;
      Message::SendFail() << "Error during " << theContext << ": Cannot access output stream '"
                          << aKeyInfo << "'";
    }
    return false;
  }

  return true;
}

bool DE_ValidationUtils::ValidateDocument(const occ::handle<TDocStd_Document>& theDocument,
                                          const TCollection_AsciiString&       theContext,
                                          const bool                           theIsVerbose)
{
  if (theDocument.IsNull())
  {
    if (theIsVerbose)
    {
      Message::SendFail() << "Error during " << theContext << ": Document handle is null";
    }
    return false;
  }

  return true;
}

bool DE_ValidationUtils::WarnLengthUnitNotSupported(const double                   theLengthUnit,
                                                    const TCollection_AsciiString& theContext,
                                                    const bool                     theIsVerbose)
{
  if (theIsVerbose && theLengthUnit != 1.0)
  {
    Message::SendWarning() << "Warning during " << theContext
                           << ": Format doesn't support custom length unit scaling (unit: "
                           << theLengthUnit << ")";
  }

  return true;
}

bool DE_ValidationUtils::CreateContentBuffer(const TCollection_AsciiString&   thePath,
                                             occ::handle<NCollection_Buffer>& theBuffer)
{
  const occ::handle<OSD_FileSystem>& aFileSystem = OSD_FileSystem::DefaultFileSystem();
  std::shared_ptr<std::istream>      aStream =
    aFileSystem->OpenIStream(thePath, std::ios::in | std::ios::binary);

  if (aStream.get() == nullptr)
  {
    theBuffer.Nullify();
    return false;
  }

  return CreateContentBuffer(*aStream, theBuffer);
}

bool DE_ValidationUtils::CreateContentBuffer(std::istream&                    theStream,
                                             occ::handle<NCollection_Buffer>& theBuffer)
{
  constexpr std::streamsize aBufferLength = 2048;

  theBuffer =
    new NCollection_Buffer(NCollection_BaseAllocator::CommonBaseAllocator(), aBufferLength);

  std::streampos aOriginalPos = theStream.tellg();

  theStream.read(reinterpret_cast<char*>(theBuffer->ChangeData()), aBufferLength);
  const std::streamsize aBytesRead = theStream.gcount();
  theBuffer->ChangeData()[aBytesRead < aBufferLength ? aBytesRead : aBufferLength - 1] = '\0';

  theStream.clear();

  theStream.seekg(aOriginalPos);

  return true;
}
