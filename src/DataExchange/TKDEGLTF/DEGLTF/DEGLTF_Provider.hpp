#pragma once

#include <DEGLTF_ConfigurationNode.hpp>
#include <DE_Provider.hpp>
#include <RWGltf_CafReader.hpp>

class DEGLTF_Provider : public DE_Provider
{
public:
  DEFINE_STANDARD_RTTIEXT(DEGLTF_Provider, DE_Provider)

public:
  Standard_EXPORT DEGLTF_Provider();

  Standard_EXPORT DEGLTF_Provider(const occ::handle<DE_ConfigurationNode>& theNode);

public:
  Standard_EXPORT bool Read(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    occ::handle<XSControl_WorkSession>&  theWS,
    const Message_ProgressRange&         theProgress = Message_ProgressRange()) override;

  Standard_EXPORT bool Write(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    occ::handle<XSControl_WorkSession>&  theWS,
    const Message_ProgressRange&         theProgress = Message_ProgressRange()) override;

  Standard_EXPORT bool Read(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    const Message_ProgressRange&         theProgress = Message_ProgressRange()) override;

  Standard_EXPORT bool Write(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    const Message_ProgressRange&         theProgress = Message_ProgressRange()) override;

  Standard_EXPORT bool Read(
    const TCollection_AsciiString&      thePath,
    TopoDS_Shape&                       theShape,
    occ::handle<XSControl_WorkSession>& theWS,
    const Message_ProgressRange&        theProgress = Message_ProgressRange()) override;

  Standard_EXPORT bool Write(
    const TCollection_AsciiString&      thePath,
    const TopoDS_Shape&                 theShape,
    occ::handle<XSControl_WorkSession>& theWS,
    const Message_ProgressRange&        theProgress = Message_ProgressRange()) override;

  Standard_EXPORT bool Read(
    const TCollection_AsciiString& thePath,
    TopoDS_Shape&                  theShape,
    const Message_ProgressRange&   theProgress = Message_ProgressRange()) override;

  Standard_EXPORT bool Write(
    const TCollection_AsciiString& thePath,
    const TopoDS_Shape&            theShape,
    const Message_ProgressRange&   theProgress = Message_ProgressRange()) override;

public:
  Standard_EXPORT TCollection_AsciiString GetFormat() const override;

  Standard_EXPORT TCollection_AsciiString GetVendor() const override;
};
