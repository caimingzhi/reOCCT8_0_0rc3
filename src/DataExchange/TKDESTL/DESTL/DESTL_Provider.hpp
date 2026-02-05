#pragma once

#include <DE_Provider.hpp>

//! The class to transfer STL files.
//! Reads and Writes any STL files into/from OCCT.
//! Each operation needs configuration node.
//!
//! Providers grouped by Vendor name and Format type.
//! The Vendor name is "OCC"
//! The Format type is "STL"
//! The import process is supported.
//! The export process is supported.
class DESTL_Provider : public DE_Provider
{
public:
  DEFINE_STANDARD_RTTIEXT(DESTL_Provider, DE_Provider)

public:
  //! Default constructor
  //! Configure translation process with global configuration
  Standard_EXPORT DESTL_Provider();

  //! Configure translation process
  //! @param[in] theNode object to copy
  Standard_EXPORT DESTL_Provider(const occ::handle<DE_ConfigurationNode>& theNode);

public:
  //! Reads a CAD file, according internal configuration
  //! @param[in] thePath path to the import CAD file
  //! @param[out] theDocument document to save result
  //! @param[in] theWS current work session
  //! @param[in] theProgress progress indicator
  //! @return true if Read operation has ended correctly
  Standard_EXPORT bool Read(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    occ::handle<XSControl_WorkSession>&  theWS,
    const Message_ProgressRange&         theProgress = Message_ProgressRange()) override;

  //! Writes a CAD file, according internal configuration
  //! @param[in] thePath path to the export CAD file
  //! @param[out] theDocument document to export
  //! @param[in] theWS current work session
  //! @param[in] theProgress progress indicator
  //! @return true if Write operation has ended correctly
  Standard_EXPORT bool Write(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    occ::handle<XSControl_WorkSession>&  theWS,
    const Message_ProgressRange&         theProgress = Message_ProgressRange()) override;

  //! Reads a CAD file, according internal configuration
  //! @param[in] thePath path to the import CAD file
  //! @param[out] theDocument document to save result
  //! @param[in] theProgress progress indicator
  //! @return true if Read operation has ended correctly
  Standard_EXPORT bool Read(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    const Message_ProgressRange&         theProgress = Message_ProgressRange()) override;

  //! Writes a CAD file, according internal configuration
  //! @param[in] thePath path to the export CAD file
  //! @param[out] theDocument document to export
  //! @param[in] theProgress progress indicator
  //! @return true if Write operation has ended correctly
  Standard_EXPORT bool Write(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    const Message_ProgressRange&         theProgress = Message_ProgressRange()) override;

  //! Reads a CAD file, according internal configuration
  //! @param[in] thePath path to the import CAD file
  //! @param[out] theShape shape to save result
  //! @param[in] theWS current work session
  //! @param[in] theProgress progress indicator
  //! @return true if Read operation has ended correctly
  Standard_EXPORT bool Read(
    const TCollection_AsciiString&      thePath,
    TopoDS_Shape&                       theShape,
    occ::handle<XSControl_WorkSession>& theWS,
    const Message_ProgressRange&        theProgress = Message_ProgressRange()) override;

  //! Writes a CAD file, according internal configuration
  //! @param[in] thePath path to the export CAD file
  //! @param[out] theShape shape to export
  //! @param[in] theWS current work session
  //! @param[in] theProgress progress indicator
  //! @return true if Write operation has ended correctly
  Standard_EXPORT bool Write(
    const TCollection_AsciiString&      thePath,
    const TopoDS_Shape&                 theShape,
    occ::handle<XSControl_WorkSession>& theWS,
    const Message_ProgressRange&        theProgress = Message_ProgressRange()) override;

  //! Reads streams according to internal configuration
  //! @param[in] theStreams streams to read from
  //! @param[out] theDocument document to save result
  //! @param[in] theWS current work session
  //! @param[in] theProgress progress indicator
  //! @return true if Read operation has ended correctly
  Standard_EXPORT bool Read(
    ReadStreamList&                      theStreams,
    const occ::handle<TDocStd_Document>& theDocument,
    occ::handle<XSControl_WorkSession>&  theWS,
    const Message_ProgressRange&         theProgress = Message_ProgressRange()) override;

  //! Writes streams according to internal configuration
  //! @param[in] theStreams streams to write to
  //! @param[out] theDocument document to export
  //! @param[in] theWS current work session
  //! @param[in] theProgress progress indicator
  //! @return true if Write operation has ended correctly
  Standard_EXPORT bool Write(
    WriteStreamList&                     theStreams,
    const occ::handle<TDocStd_Document>& theDocument,
    occ::handle<XSControl_WorkSession>&  theWS,
    const Message_ProgressRange&         theProgress = Message_ProgressRange()) override;

  //! Reads streams according to internal configuration
  //! @param[in] theStreams streams to read from
  //! @param[out] theShape shape to save result
  //! @param[in] theWS current work session
  //! @param[in] theProgress progress indicator
  //! @return true if Read operation has ended correctly
  Standard_EXPORT bool Read(
    ReadStreamList&                     theStreams,
    TopoDS_Shape&                       theShape,
    occ::handle<XSControl_WorkSession>& theWS,
    const Message_ProgressRange&        theProgress = Message_ProgressRange()) override;

  //! Writes streams according to internal configuration
  //! @param[in] theStreams streams to write to
  //! @param[out] theShape shape to export
  //! @param[in] theWS current work session
  //! @param[in] theProgress progress indicator
  //! @return true if Write operation has ended correctly
  Standard_EXPORT bool Write(
    WriteStreamList&                    theStreams,
    const TopoDS_Shape&                 theShape,
    occ::handle<XSControl_WorkSession>& theWS,
    const Message_ProgressRange&        theProgress = Message_ProgressRange()) override;

  //! Reads a CAD file, according internal configuration
  //! @param[in] thePath path to the import CAD file
  //! @param[out] theShape shape to save result
  //! @param[in] theProgress progress indicator
  //! @return true if Read operation has ended correctly
  Standard_EXPORT bool Read(
    const TCollection_AsciiString& thePath,
    TopoDS_Shape&                  theShape,
    const Message_ProgressRange&   theProgress = Message_ProgressRange()) override;

  //! Writes a CAD file, according internal configuration
  //! @param[in] thePath path to the export CAD file
  //! @param[out] theShape shape to export
  //! @param[in] theProgress progress indicator
  //! @return true if Write operation has ended correctly
  Standard_EXPORT bool Write(
    const TCollection_AsciiString& thePath,
    const TopoDS_Shape&            theShape,
    const Message_ProgressRange&   theProgress = Message_ProgressRange()) override;

  //! Reads streams according to internal configuration
  //! @param[in] theStreams streams to read from
  //! @param[out] theDocument document to save result
  //! @param[in] theProgress progress indicator
  //! @return true if Read operation has ended correctly
  Standard_EXPORT bool Read(
    ReadStreamList&                      theStreams,
    const occ::handle<TDocStd_Document>& theDocument,
    const Message_ProgressRange&         theProgress = Message_ProgressRange()) override;

  //! Writes streams according to internal configuration
  //! @param[in] theStreams streams to write to
  //! @param[out] theDocument document to export
  //! @param[in] theProgress progress indicator
  //! @return true if Write operation has ended correctly
  Standard_EXPORT bool Write(
    WriteStreamList&                     theStreams,
    const occ::handle<TDocStd_Document>& theDocument,
    const Message_ProgressRange&         theProgress = Message_ProgressRange()) override;

  //! Reads streams according to internal configuration
  //! @param[in] theStreams streams to read from
  //! @param[out] theShape shape to save result
  //! @param[in] theProgress progress indicator
  //! @return true if Read operation has ended correctly
  Standard_EXPORT bool Read(
    ReadStreamList&              theStreams,
    TopoDS_Shape&                theShape,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) override;

  //! Writes streams according to internal configuration
  //! @param[in] theStreams streams to write to
  //! @param[out] theShape shape to export
  //! @param[in] theProgress progress indicator
  //! @return true if Write operation has ended correctly
  Standard_EXPORT bool Write(
    WriteStreamList&             theStreams,
    const TopoDS_Shape&          theShape,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) override;

public:
  //! Gets CAD format name of associated provider
  //! @return provider CAD format
  Standard_EXPORT TCollection_AsciiString GetFormat() const override;

  //! Gets provider's vendor name of associated provider
  //! @return provider's vendor name
  Standard_EXPORT TCollection_AsciiString GetVendor() const override;
};
