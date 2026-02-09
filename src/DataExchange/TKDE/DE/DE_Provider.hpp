#pragma once

#include <Message_ProgressRange.hpp>
#include <NCollection_List.hpp>
#include <Standard_IStream.hpp>
#include <Standard_OStream.hpp>

class DE_ConfigurationNode;
class TopoDS_Shape;
class XSControl_WorkSession;
class TDocStd_Document;

class DE_Provider : public Standard_Transient
{
public:
  DEFINE_STANDARD_RTTIEXT(DE_Provider, Standard_Transient)

  struct WriteStreamNode
  {
    TCollection_AsciiString Path;
    Standard_OStream&       Stream;

    WriteStreamNode(const TCollection_AsciiString& thePath, Standard_OStream& theStream)
        : Path(thePath),
          Stream(theStream)
    {
    }
  };

  struct ReadStreamNode
  {
    TCollection_AsciiString Path;
    Standard_IStream&       Stream;

    ReadStreamNode(const TCollection_AsciiString& thePath, Standard_IStream& theStream)
        : Path(thePath),
          Stream(theStream)
    {
    }
  };

public:
  using WriteStreamList = NCollection_List<WriteStreamNode>;

  using ReadStreamList = NCollection_List<ReadStreamNode>;

public:
  Standard_EXPORT DE_Provider();

  Standard_EXPORT DE_Provider(const occ::handle<DE_ConfigurationNode>& theNode);

public:
  Standard_EXPORT virtual bool Read(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    occ::handle<XSControl_WorkSession>&  theWS,
    const Message_ProgressRange&         theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Write(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    occ::handle<XSControl_WorkSession>&  theWS,
    const Message_ProgressRange&         theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Read(
    ReadStreamList&                      theStreams,
    const occ::handle<TDocStd_Document>& theDocument,
    occ::handle<XSControl_WorkSession>&  theWS,
    const Message_ProgressRange&         theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Write(
    WriteStreamList&                     theStreams,
    const occ::handle<TDocStd_Document>& theDocument,
    occ::handle<XSControl_WorkSession>&  theWS,
    const Message_ProgressRange&         theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Read(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    const Message_ProgressRange&         theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Write(
    const TCollection_AsciiString&       thePath,
    const occ::handle<TDocStd_Document>& theDocument,
    const Message_ProgressRange&         theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Read(
    ReadStreamList&                      theStreams,
    const occ::handle<TDocStd_Document>& theDocument,
    const Message_ProgressRange&         theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Write(
    WriteStreamList&                     theStreams,
    const occ::handle<TDocStd_Document>& theDocument,
    const Message_ProgressRange&         theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Read(
    const TCollection_AsciiString&      thePath,
    TopoDS_Shape&                       theShape,
    occ::handle<XSControl_WorkSession>& theWS,
    const Message_ProgressRange&        theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Write(
    const TCollection_AsciiString&      thePath,
    const TopoDS_Shape&                 theShape,
    occ::handle<XSControl_WorkSession>& theWS,
    const Message_ProgressRange&        theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Read(
    ReadStreamList&                     theStreams,
    TopoDS_Shape&                       theShape,
    occ::handle<XSControl_WorkSession>& theWS,
    const Message_ProgressRange&        theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Write(
    WriteStreamList&                    theStreams,
    const TopoDS_Shape&                 theShape,
    occ::handle<XSControl_WorkSession>& theWS,
    const Message_ProgressRange&        theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Read(
    const TCollection_AsciiString& thePath,
    TopoDS_Shape&                  theShape,
    const Message_ProgressRange&   theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Write(
    const TCollection_AsciiString& thePath,
    const TopoDS_Shape&            theShape,
    const Message_ProgressRange&   theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Read(
    ReadStreamList&              theStreams,
    TopoDS_Shape&                theShape,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Write(
    WriteStreamList&             theStreams,
    const TopoDS_Shape&          theShape,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

public:
  Standard_EXPORT virtual TCollection_AsciiString GetFormat() const = 0;

  Standard_EXPORT virtual TCollection_AsciiString GetVendor() const = 0;

  occ::handle<DE_ConfigurationNode> GetNode() const { return myNode; }

  void SetNode(const occ::handle<DE_ConfigurationNode>& theNode) { myNode = theNode; }

private:
  occ::handle<DE_ConfigurationNode> myNode;
};
