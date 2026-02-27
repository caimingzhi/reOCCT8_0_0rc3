#pragma once

#include <DE_Provider.hpp>

class DEOBJ_Provider : public DE_Provider
{
public:
  DEFINE_STANDARD_RTTIEXT(DEOBJ_Provider, DE_Provider)

public:
  Standard_EXPORT DEOBJ_Provider();

  Standard_EXPORT DEOBJ_Provider(const occ::handle<DE_ConfigurationNode>& theNode);

public:
  Standard_EXPORT bool Read(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    occ::handle<XSControl_WorkSession>&  theWS,
    const System::log::Message_ProgressRange&         theProgress = System::log::Message_ProgressRange()) override;

  Standard_EXPORT bool Write(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    occ::handle<XSControl_WorkSession>&  theWS,
    const System::log::Message_ProgressRange&         theProgress = System::log::Message_ProgressRange()) override;

  Standard_EXPORT bool Read(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    const System::log::Message_ProgressRange&         theProgress = System::log::Message_ProgressRange()) override;

  Standard_EXPORT bool Write(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    const System::log::Message_ProgressRange&         theProgress = System::log::Message_ProgressRange()) override;

  Standard_EXPORT bool Read(
    const TCollection_AsciiString&      thePath,
    TopoDS_Shape&                       theShape,
    occ::handle<XSControl_WorkSession>& theWS,
    const System::log::Message_ProgressRange&        theProgress = System::log::Message_ProgressRange()) override;

  Standard_EXPORT bool Write(
    const TCollection_AsciiString&      thePath,
    const TopoDS_Shape&                 theShape,
    occ::handle<XSControl_WorkSession>& theWS,
    const System::log::Message_ProgressRange&        theProgress = System::log::Message_ProgressRange()) override;

  Standard_EXPORT bool Read(
    const TCollection_AsciiString& thePath,
    TopoDS_Shape&                  theShape,
    const System::log::Message_ProgressRange&   theProgress = System::log::Message_ProgressRange()) override;

  Standard_EXPORT bool Write(
    const TCollection_AsciiString& thePath,
    const TopoDS_Shape&            theShape,
    const System::log::Message_ProgressRange&   theProgress = System::log::Message_ProgressRange()) override;

public:
  Standard_EXPORT TCollection_AsciiString GetFormat() const override;

  Standard_EXPORT TCollection_AsciiString GetVendor() const override;
};
