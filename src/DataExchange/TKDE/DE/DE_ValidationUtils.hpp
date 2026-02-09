#pragma once

#include <TCollection_AsciiString.hpp>
#include <DE_ConfigurationNode.hpp>
#include <DE_Provider.hpp>

class TDocStd_Document;

class DE_ValidationUtils
{
public:
  Standard_EXPORT static bool ValidateConfigurationNode(
    const occ::handle<DE_ConfigurationNode>& theNode,
    const occ::handle<Standard_Type>&        theExpectedType,
    const TCollection_AsciiString&           theContext,
    const bool                               theIsVerbose = true);

  Standard_EXPORT static bool ValidateFileForReading(const TCollection_AsciiString& thePath,
                                                     const TCollection_AsciiString& theContext,
                                                     const bool theIsVerbose = true);

  Standard_EXPORT static bool ValidateFileForWriting(const TCollection_AsciiString& thePath,
                                                     const TCollection_AsciiString& theContext,
                                                     const bool theIsVerbose = true);

  Standard_EXPORT static bool ValidateReadStreamList(const DE_Provider::ReadStreamList& theStreams,
                                                     const TCollection_AsciiString&     theContext,
                                                     const bool theIsVerbose = true);

  Standard_EXPORT static bool ValidateWriteStreamList(DE_Provider::WriteStreamList&  theStreams,
                                                      const TCollection_AsciiString& theContext,
                                                      const bool theIsVerbose = true);

  Standard_EXPORT static bool ValidateDocument(const occ::handle<TDocStd_Document>& theDocument,
                                               const TCollection_AsciiString&       theContext,
                                               const bool theIsVerbose = true);

  Standard_EXPORT static bool WarnLengthUnitNotSupported(const double theLengthUnit,
                                                         const TCollection_AsciiString& theContext,
                                                         const bool theIsVerbose = true);

  Standard_EXPORT static bool CreateContentBuffer(const TCollection_AsciiString&   thePath,
                                                  occ::handle<NCollection_Buffer>& theBuffer);

  Standard_EXPORT static bool CreateContentBuffer(std::istream&                    theStream,
                                                  occ::handle<NCollection_Buffer>& theBuffer);
};
