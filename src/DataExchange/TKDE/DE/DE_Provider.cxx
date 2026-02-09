

#include <DE_Provider.hpp>

#include <DE_ConfigurationNode.hpp>
#include <Message.hpp>
#include <NCollection_IndexedDataMap.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DE_Provider, Standard_Transient)

DE_Provider::DE_Provider() = default;

DE_Provider::DE_Provider(const occ::handle<DE_ConfigurationNode>& theNode)
    : myNode(theNode)
{
}

bool DE_Provider::Read(const TCollection_AsciiString&       thePath,
                       const occ::handle<TDocStd_Document>& theDocument,
                       occ::handle<XSControl_WorkSession>&  theWS,
                       const Message_ProgressRange&         theProgress)
{
  (void)thePath;
  (void)theDocument;
  (void)theWS;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support read operation";
  return false;
}

bool DE_Provider::Write(const TCollection_AsciiString&       thePath,
                        const occ::handle<TDocStd_Document>& theDocument,
                        occ::handle<XSControl_WorkSession>&  theWS,
                        const Message_ProgressRange&         theProgress)
{
  (void)thePath;
  (void)theDocument;
  (void)theWS;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support write operation";
  return false;
}

bool DE_Provider::Read(const TCollection_AsciiString&       thePath,
                       const occ::handle<TDocStd_Document>& theDocument,
                       const Message_ProgressRange&         theProgress)
{
  (void)thePath;
  (void)theDocument;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support read operation";
  return false;
}

bool DE_Provider::Write(const TCollection_AsciiString&       thePath,
                        const occ::handle<TDocStd_Document>& theDocument,
                        const Message_ProgressRange&         theProgress)
{
  (void)thePath;
  (void)theDocument;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support write operation";
  return false;
}

bool DE_Provider::Read(const TCollection_AsciiString&      thePath,
                       TopoDS_Shape&                       theShape,
                       occ::handle<XSControl_WorkSession>& theWS,
                       const Message_ProgressRange&        theProgress)
{
  (void)thePath;
  (void)theShape;
  (void)theWS;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support read operation";
  return false;
}

bool DE_Provider::Write(const TCollection_AsciiString&      thePath,
                        const TopoDS_Shape&                 theShape,
                        occ::handle<XSControl_WorkSession>& theWS,
                        const Message_ProgressRange&        theProgress)
{
  (void)thePath;
  (void)theShape;
  (void)theWS;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support write operation";
  return false;
}

bool DE_Provider::Read(const TCollection_AsciiString& thePath,
                       TopoDS_Shape&                  theShape,
                       const Message_ProgressRange&   theProgress)
{
  (void)thePath;
  (void)theShape;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support read operation";
  return false;
}

bool DE_Provider::Write(const TCollection_AsciiString& thePath,
                        const TopoDS_Shape&            theShape,
                        const Message_ProgressRange&   theProgress)
{
  (void)thePath;
  (void)theShape;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support write operation";
  return false;
}

bool DE_Provider::Read(ReadStreamList&                      theStreams,
                       const occ::handle<TDocStd_Document>& theDocument,
                       occ::handle<XSControl_WorkSession>&  theWS,
                       const Message_ProgressRange&         theProgress)
{
  (void)theStreams;
  (void)theDocument;
  (void)theWS;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support stream read operation";
  return false;
}

bool DE_Provider::Write(WriteStreamList&                     theStreams,
                        const occ::handle<TDocStd_Document>& theDocument,
                        occ::handle<XSControl_WorkSession>&  theWS,
                        const Message_ProgressRange&         theProgress)
{
  (void)theStreams;
  (void)theDocument;
  (void)theWS;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support stream write operation";
  return false;
}

bool DE_Provider::Read(ReadStreamList&                     theStreams,
                       TopoDS_Shape&                       theShape,
                       occ::handle<XSControl_WorkSession>& theWS,
                       const Message_ProgressRange&        theProgress)
{
  (void)theStreams;
  (void)theShape;
  (void)theWS;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support stream read operation";
  return false;
}

bool DE_Provider::Write(WriteStreamList&                    theStreams,
                        const TopoDS_Shape&                 theShape,
                        occ::handle<XSControl_WorkSession>& theWS,
                        const Message_ProgressRange&        theProgress)
{
  (void)theStreams;
  (void)theShape;
  (void)theWS;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support stream write operation";
  return false;
}

bool DE_Provider::Read(ReadStreamList&                      theStreams,
                       const occ::handle<TDocStd_Document>& theDocument,
                       const Message_ProgressRange&         theProgress)
{
  (void)theStreams;
  (void)theDocument;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support stream read operation";
  return false;
}

bool DE_Provider::Write(WriteStreamList&                     theStreams,
                        const occ::handle<TDocStd_Document>& theDocument,
                        const Message_ProgressRange&         theProgress)
{
  (void)theStreams;
  (void)theDocument;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support stream write operation";
  return false;
}

bool DE_Provider::Read(ReadStreamList&              theStreams,
                       TopoDS_Shape&                theShape,
                       const Message_ProgressRange& theProgress)
{
  (void)theStreams;
  (void)theShape;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support stream read operation";
  return false;
}

bool DE_Provider::Write(WriteStreamList&             theStreams,
                        const TopoDS_Shape&          theShape,
                        const Message_ProgressRange& theProgress)
{
  (void)theStreams;
  (void)theShape;
  (void)theProgress;
  Message::SendFail() << "Error: provider " << GetFormat() << " " << GetVendor()
                      << " doesn't support stream write operation";
  return false;
}
