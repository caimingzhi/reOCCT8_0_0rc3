

#include <DESTL_Provider.hpp>

#include <BRep_Builder.hpp>
#include <DE_ValidationUtils.hpp>
#include <DESTL_ConfigurationNode.hpp>
#include <Message.hpp>
#include <NCollection_Vector.hpp>
#include <Poly_Triangle.hpp>
#include <RWStl.hpp>
#include <RWStl_Reader.hpp>
#include <StlAPI.hpp>
#include <StlAPI_Reader.hpp>
#include <StlAPI_Writer.hpp>
#include <Standard_ReadLineBuffer.hpp>
#include <TDocStd_Document.hpp>
#include <XCAFDoc_DocumentTool.hpp>
#include <XCAFDoc_ShapeTool.hpp>
#include <cstring>

IMPLEMENT_STANDARD_RTTIEXT(DESTL_Provider, DE_Provider)

DESTL_Provider::DESTL_Provider() = default;

DESTL_Provider::DESTL_Provider(const occ::handle<DE_ConfigurationNode>& theNode)
    : DE_Provider(theNode)
{
}

bool DESTL_Provider::Read(const TCollection_AsciiString&       thePath,
                          const occ::handle<TDocStd_Document>& theDocument,
                          occ::handle<XSControl_WorkSession>&  theWS,
                          const Message_ProgressRange&         theProgress)
{
  (void)theWS;
  return Read(thePath, theDocument, theProgress);
}

bool DESTL_Provider::Write(const TCollection_AsciiString&       thePath,
                           const occ::handle<TDocStd_Document>& theDocument,
                           occ::handle<XSControl_WorkSession>&  theWS,
                           const Message_ProgressRange&         theProgress)
{
  (void)theWS;
  return Write(thePath, theDocument, theProgress);
}

bool DESTL_Provider::Read(const TCollection_AsciiString&       thePath,
                          const occ::handle<TDocStd_Document>& theDocument,
                          const Message_ProgressRange&         theProgress)
{
  TCollection_AsciiString aContext = TCollection_AsciiString("reading the file ") + thePath;
  if (!DE_ValidationUtils::ValidateDocument(theDocument, aContext))
  {
    return false;
  }
  TopoDS_Shape aShape;
  if (!Read(thePath, aShape, theProgress))
  {
    return false;
  }
  occ::handle<XCAFDoc_ShapeTool> aShapeTool = XCAFDoc_DocumentTool::ShapeTool(theDocument->Main());
  aShapeTool->AddShape(aShape);
  return true;
}

bool DESTL_Provider::Write(const TCollection_AsciiString&       thePath,
                           const occ::handle<TDocStd_Document>& theDocument,
                           const Message_ProgressRange&         theProgress)
{
  TCollection_AsciiString aContext = TCollection_AsciiString("writing the file ") + thePath;
  if (!DE_ValidationUtils::ValidateDocument(theDocument, aContext))
  {
    return false;
  }

  NCollection_Sequence<TDF_Label> aLabels;
  occ::handle<XCAFDoc_ShapeTool>  aSTool = XCAFDoc_DocumentTool::ShapeTool(theDocument->Main());
  aSTool->GetFreeShapes(aLabels);

  if (aLabels.Length() <= 0)
  {
    Message::SendFail() << "Error in the DESTL_Provider during writing the file " << thePath
                        << ": Document contain no shapes";
    return false;
  }

  if (!DE_ValidationUtils::ValidateConfigurationNode(GetNode(),
                                                     STANDARD_TYPE(DESTL_ConfigurationNode),
                                                     aContext))
  {
    return false;
  }

  occ::handle<DESTL_ConfigurationNode> aNode = occ::down_cast<DESTL_ConfigurationNode>(GetNode());
  DE_ValidationUtils::WarnLengthUnitNotSupported(aNode->GlobalParameters.LengthUnit, aContext);

  TopoDS_Shape aShape;
  if (aLabels.Length() == 1)
  {
    aShape = aSTool->GetShape(aLabels.Value(1));
  }
  else
  {
    TopoDS_Compound aComp;
    BRep_Builder    aBuilder;
    aBuilder.MakeCompound(aComp);
    for (int anIndex = 1; anIndex <= aLabels.Length(); anIndex++)
    {
      TopoDS_Shape aS = aSTool->GetShape(aLabels.Value(anIndex));
      aBuilder.Add(aComp, aS);
    }
    aShape = aComp;
  }

  return Write(thePath, aShape, theProgress);
}

bool DESTL_Provider::Read(const TCollection_AsciiString&      thePath,
                          TopoDS_Shape&                       theShape,
                          occ::handle<XSControl_WorkSession>& theWS,
                          const Message_ProgressRange&        theProgress)
{
  (void)theWS;
  return Read(thePath, theShape, theProgress);
}

bool DESTL_Provider::Write(const TCollection_AsciiString&      thePath,
                           const TopoDS_Shape&                 theShape,
                           occ::handle<XSControl_WorkSession>& theWS,
                           const Message_ProgressRange&        theProgress)
{
  (void)theWS;
  return Write(thePath, theShape, theProgress);
}

bool DESTL_Provider::Read(const TCollection_AsciiString& thePath,
                          TopoDS_Shape&                  theShape,
                          const Message_ProgressRange&   theProgress)
{
  Message::SendWarning()
    << "OCCT Stl reader does not support model scaling according to custom length unit";

  TCollection_AsciiString aContext = TCollection_AsciiString("reading the file ") + thePath;
  if (!DE_ValidationUtils::ValidateConfigurationNode(GetNode(),
                                                     STANDARD_TYPE(DESTL_ConfigurationNode),
                                                     aContext))
  {
    return false;
  }

  occ::handle<DESTL_ConfigurationNode> aNode = occ::down_cast<DESTL_ConfigurationNode>(GetNode());
  double aMergeAngle = aNode->InternalParameters.ReadMergeAngle * M_PI / 180.0;

  if (aMergeAngle != M_PI_2)
  {
    if (aMergeAngle < 0.0 || aMergeAngle > M_PI_2)
    {
      Message::SendFail() << "Error in the DESTL_Provider during reading the file " << thePath
                          << "\t: The merge angle is out of the valid range";
      return false;
    }
  }

  if (!aNode->InternalParameters.ReadBRep)
  {
    occ::handle<Poly_Triangulation> aTriangulation =
      RWStl::ReadFile(thePath.ToCString(), aMergeAngle, theProgress);

    TopoDS_Face  aFace;
    BRep_Builder aB;
    aB.MakeFace(aFace);
    aB.UpdateFace(aFace, aTriangulation);
    theShape = aFace;
  }
  else
  {
    Standard_DISABLE_DEPRECATION_WARNINGS

      if (!StlAPI::Read(theShape, thePath.ToCString()))
    {
      Message::SendFail() << "Error in the DESTL_Provider during reading the file " << thePath;
      return false;
    }
    Standard_ENABLE_DEPRECATION_WARNINGS
  }
  return true;
}

bool DESTL_Provider::Write(const TCollection_AsciiString& thePath,
                           const TopoDS_Shape&            theShape,
                           const Message_ProgressRange&   theProgress)
{
  Message::SendWarning()
    << "OCCT Stl writer does not support model scaling according to custom length unit";

  TCollection_AsciiString aContext = TCollection_AsciiString("writing the file ") + thePath;
  if (!DE_ValidationUtils::ValidateConfigurationNode(GetNode(),
                                                     STANDARD_TYPE(DESTL_ConfigurationNode),
                                                     aContext))
  {
    return false;
  }

  occ::handle<DESTL_ConfigurationNode> aNode = occ::down_cast<DESTL_ConfigurationNode>(GetNode());
  DE_ValidationUtils::WarnLengthUnitNotSupported(aNode->GlobalParameters.LengthUnit, aContext);

  StlAPI_Writer aWriter;
  aWriter.ASCIIMode() = aNode->InternalParameters.WriteAscii;
  if (!aWriter.Write(theShape, thePath.ToCString(), theProgress))
  {
    Message::SendFail() << "Error in the DESTL_Provider during writing the file " << thePath
                        << "\t: Mesh writing has been failed";
    return false;
  }
  return true;
}

bool DESTL_Provider::Read(ReadStreamList&                      theStreams,
                          const occ::handle<TDocStd_Document>& theDocument,
                          occ::handle<XSControl_WorkSession>&  theWS,
                          const Message_ProgressRange&         theProgress)
{
  (void)theWS;
  return Read(theStreams, theDocument, theProgress);
}

bool DESTL_Provider::Write(WriteStreamList&                     theStreams,
                           const occ::handle<TDocStd_Document>& theDocument,
                           occ::handle<XSControl_WorkSession>&  theWS,
                           const Message_ProgressRange&         theProgress)
{
  (void)theWS;
  return Write(theStreams, theDocument, theProgress);
}

bool DESTL_Provider::Read(ReadStreamList&                     theStreams,
                          TopoDS_Shape&                       theShape,
                          occ::handle<XSControl_WorkSession>& theWS,
                          const Message_ProgressRange&        theProgress)
{
  (void)theWS;
  return Read(theStreams, theShape, theProgress);
}

bool DESTL_Provider::Write(WriteStreamList&                    theStreams,
                           const TopoDS_Shape&                 theShape,
                           occ::handle<XSControl_WorkSession>& theWS,
                           const Message_ProgressRange&        theProgress)
{
  (void)theWS;
  return Write(theStreams, theShape, theProgress);
}

bool DESTL_Provider::Read(ReadStreamList&                      theStreams,
                          const occ::handle<TDocStd_Document>& theDocument,
                          const Message_ProgressRange&         theProgress)
{
  TCollection_AsciiString aContext = "reading stream";
  if (!DE_ValidationUtils::ValidateReadStreamList(theStreams, aContext))
  {
    return false;
  }

  const TCollection_AsciiString& aFirstKey    = theStreams.First().Path;
  TCollection_AsciiString        aFullContext = aContext + " " + aFirstKey;
  if (!DE_ValidationUtils::ValidateDocument(theDocument, aFullContext))
  {
    return false;
  }

  TopoDS_Shape aShape;
  if (!Read(theStreams, aShape, theProgress))
  {
    return false;
  }

  occ::handle<XCAFDoc_ShapeTool> aShapeTool = XCAFDoc_DocumentTool::ShapeTool(theDocument->Main());
  aShapeTool->AddShape(aShape);
  return true;
}

bool DESTL_Provider::Write(WriteStreamList&                     theStreams,
                           const occ::handle<TDocStd_Document>& theDocument,
                           const Message_ProgressRange&         theProgress)
{
  TCollection_AsciiString aContext = "writing stream";
  if (!DE_ValidationUtils::ValidateWriteStreamList(theStreams, aContext))
  {
    return false;
  }

  const TCollection_AsciiString& aFirstKey    = theStreams.First().Path;
  TCollection_AsciiString        aFullContext = aContext + " " + aFirstKey;
  if (!DE_ValidationUtils::ValidateDocument(theDocument, aFullContext))
  {
    return false;
  }

  NCollection_Sequence<TDF_Label> aLabels;
  occ::handle<XCAFDoc_ShapeTool>  aSTool = XCAFDoc_DocumentTool::ShapeTool(theDocument->Main());
  aSTool->GetFreeShapes(aLabels);

  if (aLabels.Length() <= 0)
  {
    Message::SendFail() << "Error in the DESTL_Provider during writing stream " << aFirstKey
                        << ": Document contain no shapes";
    return false;
  }

  if (!DE_ValidationUtils::ValidateConfigurationNode(GetNode(),
                                                     STANDARD_TYPE(DESTL_ConfigurationNode),
                                                     aFullContext))
  {
    return false;
  }

  occ::handle<DESTL_ConfigurationNode> aNode = occ::down_cast<DESTL_ConfigurationNode>(GetNode());
  TCollection_AsciiString aLengthContext = TCollection_AsciiString("writing stream ") + aFirstKey;
  DE_ValidationUtils::WarnLengthUnitNotSupported(aNode->GlobalParameters.LengthUnit,
                                                 aLengthContext);

  TopoDS_Shape aShape;
  if (aLabels.Length() == 1)
  {
    aShape = aSTool->GetShape(aLabels.Value(1));
  }
  else
  {
    TopoDS_Compound aComp;
    BRep_Builder    aBuilder;
    aBuilder.MakeCompound(aComp);
    for (int anIndex = 1; anIndex <= aLabels.Length(); anIndex++)
    {
      TopoDS_Shape aS = aSTool->GetShape(aLabels.Value(anIndex));
      aBuilder.Add(aComp, aS);
    }
    aShape = aComp;
  }

  return Write(theStreams, aShape, theProgress);
}

bool DESTL_Provider::Read(ReadStreamList&              theStreams,
                          TopoDS_Shape&                theShape,
                          const Message_ProgressRange& theProgress)
{

  if (theStreams.IsEmpty())
  {
    Message::SendFail() << "Error: DESTL_Provider stream map is empty";
    return false;
  }
  if (theStreams.Size() > 1)
  {
    Message::SendWarning() << "Warning: DESTL_Provider received " << theStreams.Size()
                           << " streams for reading, using only the first one";
  }

  const TCollection_AsciiString& aFirstKey = theStreams.First().Path;
  Standard_IStream&              aStream   = theStreams.First().Stream;

  Message::SendWarning()
    << "OCCT Stl reader does not support model scaling according to custom length unit";

  TCollection_AsciiString aNodeContext = TCollection_AsciiString("reading stream ") + aFirstKey;
  if (!DE_ValidationUtils::ValidateConfigurationNode(GetNode(),
                                                     STANDARD_TYPE(DESTL_ConfigurationNode),
                                                     aNodeContext))
  {
    return false;
  }

  occ::handle<DESTL_ConfigurationNode> aNode = occ::down_cast<DESTL_ConfigurationNode>(GetNode());
  double aMergeAngle = aNode->InternalParameters.ReadMergeAngle * M_PI / 180.0;

  if (aMergeAngle != M_PI_2)
  {
    if (aMergeAngle < 0.0 || aMergeAngle > M_PI_2)
    {
      Message::SendFail() << "Error in the DESTL_Provider during reading stream " << aFirstKey
                          << ": The merge angle is out of the valid range";
      return false;
    }
  }

  if (!aNode->InternalParameters.ReadBRep)
  {
    occ::handle<Poly_Triangulation> aTriangulation =
      RWStl::ReadStream(aStream, aMergeAngle, theProgress);
    if (aTriangulation.IsNull())
    {
      Message::SendFail() << "Error in the DESTL_Provider during reading stream " << aFirstKey
                          << ": Failed to create triangulation";
      return false;
    }

    TopoDS_Face  aFace;
    BRep_Builder aB;
    aB.MakeFace(aFace);
    aB.UpdateFace(aFace, aTriangulation);
    theShape = aFace;
  }
  else
  {
    Standard_DISABLE_DEPRECATION_WARNINGS

      StlAPI_Reader aReader;
    if (!aReader.Read(theShape, aStream))
    {
      Message::SendFail() << "Error in the DESTL_Provider during reading stream " << aFirstKey;
      return false;
    }
    Standard_ENABLE_DEPRECATION_WARNINGS
  }

  return true;
}

bool DESTL_Provider::Write(WriteStreamList&             theStreams,
                           const TopoDS_Shape&          theShape,
                           const Message_ProgressRange& theProgress)
{

  if (theStreams.IsEmpty())
  {
    Message::SendFail() << "Error: DESTL_Provider stream map is empty";
    return false;
  }
  if (theStreams.Size() > 1)
  {
    Message::SendWarning() << "Warning: DESTL_Provider received " << theStreams.Size()
                           << " streams for writing, using only the first one";
  }

  const TCollection_AsciiString& aFirstKey = theStreams.First().Path;
  Standard_OStream&              aStream   = theStreams.First().Stream;

  Message::SendWarning()
    << "OCCT Stl writer does not support model scaling according to custom length unit";

  TCollection_AsciiString aNodeContext = TCollection_AsciiString("writing stream ") + aFirstKey;
  if (!DE_ValidationUtils::ValidateConfigurationNode(GetNode(),
                                                     STANDARD_TYPE(DESTL_ConfigurationNode),
                                                     aNodeContext))
  {
    return false;
  }

  occ::handle<DESTL_ConfigurationNode> aNode = occ::down_cast<DESTL_ConfigurationNode>(GetNode());
  TCollection_AsciiString aLengthContext = TCollection_AsciiString("writing stream ") + aFirstKey;
  DE_ValidationUtils::WarnLengthUnitNotSupported(aNode->GlobalParameters.LengthUnit,
                                                 aLengthContext);

  StlAPI_Writer aWriter;
  aWriter.ASCIIMode() = aNode->InternalParameters.WriteAscii;
  if (!aWriter.Write(theShape, aStream, theProgress))
  {
    Message::SendFail() << "Error in the DESTL_Provider during writing stream " << aFirstKey
                        << ": Mesh writing has been failed";
    return false;
  }

  return true;
}

TCollection_AsciiString DESTL_Provider::GetFormat() const
{
  return TCollection_AsciiString("STL");
}

TCollection_AsciiString DESTL_Provider::GetVendor() const
{
  return TCollection_AsciiString("OCC");
}
