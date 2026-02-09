

#include <DESTEP_Provider.hpp>
#include <DESTEP_ConfigurationNode.hpp>
#include <DE_Wrapper.hpp>

#include <BRepPrimAPI_MakeBox.hpp>
#include <BRepPrimAPI_MakeSphere.hpp>
#include <BRepPrimAPI_MakeCylinder.hpp>
#include <TopoDS_Shape.hpp>
#include <TopExp_Explorer.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TDocStd_Document.hpp>
#include <TDocStd_Application.hpp>
#include <XCAFDoc_DocumentTool.hpp>
#include <XCAFDoc_ShapeTool.hpp>
#include <XSControl_WorkSession.hpp>

#include <sstream>
#include <gtest/gtest.h>

class DESTEP_ProviderTest : public ::testing::Test
{
protected:
  void SetUp() override
  {

    occ::handle<DESTEP_ConfigurationNode> aNode = new DESTEP_ConfigurationNode();
    myProvider                                  = new DESTEP_Provider(aNode);

    myBox      = BRepPrimAPI_MakeBox(10.0, 10.0, 10.0).Shape();
    mySphere   = BRepPrimAPI_MakeSphere(5.0).Shape();
    myCylinder = BRepPrimAPI_MakeCylinder(3.0, 8.0).Shape();

    occ::handle<TDocStd_Application> anApp = new TDocStd_Application();
    anApp->NewDocument("BinXCAF", myDocument);
  }

  void TearDown() override
  {
    myProvider.Nullify();
    myDocument.Nullify();
  }

  int CountShapeElements(const TopoDS_Shape& theShape, TopAbs_ShapeEnum theType)
  {
    int aCount = 0;
    for (TopExp_Explorer anExplorer(theShape, theType); anExplorer.More(); anExplorer.Next())
    {
      aCount++;
    }
    return aCount;
  }

  bool IsValidSTEPContent(const std::string& theContent)
  {
    return !theContent.empty() && theContent.find("ISO-10303-21;") != std::string::npos
           && theContent.find("HEADER;") != std::string::npos
           && theContent.find("DATA;") != std::string::npos
           && theContent.find("ENDSEC;") != std::string::npos;
  }

protected:
  occ::handle<DESTEP_Provider>  myProvider;
  TopoDS_Shape                  myBox;
  TopoDS_Shape                  mySphere;
  TopoDS_Shape                  myCylinder;
  occ::handle<TDocStd_Document> myDocument;
};

TEST_F(DESTEP_ProviderTest, BasicProperties)
{
  EXPECT_STREQ("STEP", myProvider->GetFormat().ToCString());
  EXPECT_STREQ("OCC", myProvider->GetVendor().ToCString());
  EXPECT_FALSE(myProvider->GetNode().IsNull());
}

TEST_F(DESTEP_ProviderTest, StreamShapeWriteRead)
{
  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("test.step", anOStream));

  EXPECT_TRUE(myProvider->Write(aWriteStreams, myBox));

  std::string aStepContent = anOStream.str();
  EXPECT_FALSE(aStepContent.empty());
  EXPECT_TRUE(IsValidSTEPContent(aStepContent));

  if (!aStepContent.empty())
  {

    std::istringstream          anIStream(aStepContent);
    DE_Provider::ReadStreamList aReadStreams;
    aReadStreams.Append(DE_Provider::ReadStreamNode("test.step", anIStream));

    TopoDS_Shape aReadShape;
    EXPECT_TRUE(myProvider->Read(aReadStreams, aReadShape));
    EXPECT_FALSE(aReadShape.IsNull());

    if (!aReadShape.IsNull())
    {

      int aReadSolids     = CountShapeElements(aReadShape, TopAbs_SOLID);
      int aOriginalSolids = CountShapeElements(myBox, TopAbs_SOLID);
      EXPECT_EQ(aReadSolids, aOriginalSolids);
    }
  }
}

TEST_F(DESTEP_ProviderTest, StreamDocumentWriteRead)
{

  occ::handle<XCAFDoc_ShapeTool> aShapeTool  = XCAFDoc_DocumentTool::ShapeTool(myDocument->Main());
  TDF_Label                      aShapeLabel = aShapeTool->AddShape(myBox);
  EXPECT_FALSE(aShapeLabel.IsNull());

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("document.step", anOStream));

  EXPECT_TRUE(myProvider->Write(aWriteStreams, myDocument));

  std::string aStepContent = anOStream.str();
  EXPECT_FALSE(aStepContent.empty());
  EXPECT_TRUE(IsValidSTEPContent(aStepContent));

  if (!aStepContent.empty())
  {

    occ::handle<TDocStd_Application> anApp = new TDocStd_Application();
    occ::handle<TDocStd_Document>    aNewDocument;
    anApp->NewDocument("BinXCAF", aNewDocument);

    std::istringstream          anIStream(aStepContent);
    DE_Provider::ReadStreamList aReadStreams;
    aReadStreams.Append(DE_Provider::ReadStreamNode("document.step", anIStream));

    EXPECT_TRUE(myProvider->Read(aReadStreams, aNewDocument));

    occ::handle<XCAFDoc_ShapeTool> aNewShapeTool =
      XCAFDoc_DocumentTool::ShapeTool(aNewDocument->Main());
    NCollection_Sequence<TDF_Label> aLabels;
    aNewShapeTool->GetShapes(aLabels);
    EXPECT_GT(aLabels.Length(), 0);
  }
}

TEST_F(DESTEP_ProviderTest, DE_WrapperIntegration)
{

  DE_Wrapper                            aWrapper;
  occ::handle<DESTEP_ConfigurationNode> aNode = new DESTEP_ConfigurationNode();

  EXPECT_TRUE(aWrapper.Bind(aNode));

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("test.step", anOStream));

  EXPECT_TRUE(aWrapper.Write(aWriteStreams, mySphere));

  std::string aStepContent = anOStream.str();
  EXPECT_FALSE(aStepContent.empty());
  EXPECT_TRUE(IsValidSTEPContent(aStepContent));

  if (!aStepContent.empty())
  {

    std::istringstream          anIStream(aStepContent);
    DE_Provider::ReadStreamList aReadStreams;
    aReadStreams.Append(DE_Provider::ReadStreamNode("test.step", anIStream));

    TopoDS_Shape aReadShape;
    bool         aWrapperResult = aWrapper.Read(aReadStreams, aReadShape);

    std::istringstream          anIStream2(aStepContent);
    DE_Provider::ReadStreamList aReadStreams2;
    aReadStreams2.Append(DE_Provider::ReadStreamNode("test.step", anIStream2));

    occ::handle<DESTEP_Provider> aDirectProvider = new DESTEP_Provider(aNode);
    TopoDS_Shape                 aDirectShape;
    bool                         aDirectResult = aDirectProvider->Read(aReadStreams2, aDirectShape);

    EXPECT_EQ(aWrapperResult, aDirectResult);
    EXPECT_EQ(aReadShape.IsNull(), aDirectShape.IsNull());

    if (aDirectResult && !aDirectShape.IsNull())
    {
      int aSolids = CountShapeElements(aDirectShape, TopAbs_SOLID);
      EXPECT_GT(aSolids, 0);
    }
  }
}

TEST_F(DESTEP_ProviderTest, MultipleShapesInDocument)
{

  occ::handle<XCAFDoc_ShapeTool> aShapeTool   = XCAFDoc_DocumentTool::ShapeTool(myDocument->Main());
  TDF_Label                      aBoxLabel    = aShapeTool->AddShape(myBox);
  TDF_Label                      aSphereLabel = aShapeTool->AddShape(mySphere);
  TDF_Label                      aCylinderLabel = aShapeTool->AddShape(myCylinder);

  EXPECT_FALSE(aBoxLabel.IsNull());
  EXPECT_FALSE(aSphereLabel.IsNull());
  EXPECT_FALSE(aCylinderLabel.IsNull());

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("multi_shapes.step", anOStream));

  EXPECT_TRUE(myProvider->Write(aWriteStreams, myDocument));

  std::string aStepContent = anOStream.str();
  EXPECT_FALSE(aStepContent.empty());
  EXPECT_TRUE(IsValidSTEPContent(aStepContent));

  occ::handle<TDocStd_Application> anApp = new TDocStd_Application();
  occ::handle<TDocStd_Document>    aNewDocument;
  anApp->NewDocument("BinXCAF", aNewDocument);

  std::istringstream          anIStream(aStepContent);
  DE_Provider::ReadStreamList aReadStreams;
  aReadStreams.Append(DE_Provider::ReadStreamNode("multi_shapes.step", anIStream));

  EXPECT_TRUE(myProvider->Read(aReadStreams, aNewDocument));

  occ::handle<XCAFDoc_ShapeTool> aNewShapeTool =
    XCAFDoc_DocumentTool::ShapeTool(aNewDocument->Main());
  NCollection_Sequence<TDF_Label> aLabels;
  aNewShapeTool->GetShapes(aLabels);
  EXPECT_EQ(aLabels.Length(), 3);
}

TEST_F(DESTEP_ProviderTest, DifferentBRepGeometries)
{

  std::ostringstream           aBoxStream;
  DE_Provider::WriteStreamList aBoxWriteStreams;
  aBoxWriteStreams.Append(DE_Provider::WriteStreamNode("box.step", aBoxStream));

  EXPECT_TRUE(myProvider->Write(aBoxWriteStreams, myBox));
  std::string aBoxContent = aBoxStream.str();

  std::ostringstream           aSphereStream;
  DE_Provider::WriteStreamList aSphereWriteStreams;
  aSphereWriteStreams.Append(DE_Provider::WriteStreamNode("sphere.step", aSphereStream));

  EXPECT_TRUE(myProvider->Write(aSphereWriteStreams, mySphere));
  std::string aSphereContent = aSphereStream.str();

  std::ostringstream           aCylinderStream;
  DE_Provider::WriteStreamList aCylinderWriteStreams;
  aCylinderWriteStreams.Append(DE_Provider::WriteStreamNode("cylinder.step", aCylinderStream));

  EXPECT_TRUE(myProvider->Write(aCylinderWriteStreams, myCylinder));
  std::string aCylinderContent = aCylinderStream.str();

  EXPECT_TRUE(IsValidSTEPContent(aBoxContent));
  EXPECT_TRUE(IsValidSTEPContent(aSphereContent));
  EXPECT_TRUE(IsValidSTEPContent(aCylinderContent));

  EXPECT_NE(aBoxContent, aSphereContent);
  EXPECT_NE(aBoxContent, aCylinderContent);
  EXPECT_NE(aSphereContent, aCylinderContent);

  std::istringstream          aBoxIStream(aBoxContent);
  DE_Provider::ReadStreamList aBoxReadStreams;
  aBoxReadStreams.Append(DE_Provider::ReadStreamNode("box.step", aBoxIStream));

  TopoDS_Shape aBoxReadShape;
  EXPECT_TRUE(myProvider->Read(aBoxReadStreams, aBoxReadShape));
  EXPECT_FALSE(aBoxReadShape.IsNull());

  std::istringstream          aSphereIStream(aSphereContent);
  DE_Provider::ReadStreamList aSphereReadStreams;
  aSphereReadStreams.Append(DE_Provider::ReadStreamNode("sphere.step", aSphereIStream));

  TopoDS_Shape aSphereReadShape;
  EXPECT_TRUE(myProvider->Read(aSphereReadStreams, aSphereReadShape));
  EXPECT_FALSE(aSphereReadShape.IsNull());
}

TEST_F(DESTEP_ProviderTest, DE_WrapperFileExtensions)
{
  DE_Wrapper                            aWrapper;
  occ::handle<DESTEP_ConfigurationNode> aNode = new DESTEP_ConfigurationNode();
  EXPECT_TRUE(aWrapper.Bind(aNode));

  std::vector<std::string> aExtensions = {"test.step", "test.STEP", "test.stp", "test.STP"};

  for (const auto& anExt : aExtensions)
  {
    std::ostringstream           anOStream;
    DE_Provider::WriteStreamList aWriteStreams;
    aWriteStreams.Append(DE_Provider::WriteStreamNode(anExt.c_str(), anOStream));

    EXPECT_TRUE(aWrapper.Write(aWriteStreams, myBox))
      << "Failed to write with extension: " << anExt;

    std::string aContent = anOStream.str();
    EXPECT_FALSE(aContent.empty()) << "Empty content for extension: " << anExt;
    EXPECT_TRUE(IsValidSTEPContent(aContent)) << "Invalid STEP content for extension: " << anExt;

    std::istringstream          anIStream(aContent);
    DE_Provider::ReadStreamList aReadStreams;
    aReadStreams.Append(DE_Provider::ReadStreamNode(anExt.c_str(), anIStream));

    TopoDS_Shape aReadShape;
    EXPECT_TRUE(aWrapper.Read(aReadStreams, aReadShape))
      << "Failed to read with extension: " << anExt;
    EXPECT_FALSE(aReadShape.IsNull()) << "Null shape read with extension: " << anExt;
  }
}

TEST_F(DESTEP_ProviderTest, ErrorHandling)
{

  DE_Provider::WriteStreamList anEmptyWriteStreams;
  EXPECT_FALSE(myProvider->Write(anEmptyWriteStreams, myBox));

  DE_Provider::ReadStreamList anEmptyReadStreams;
  TopoDS_Shape                aShape;
  EXPECT_FALSE(myProvider->Read(anEmptyReadStreams, aShape));

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("null_test.step", anOStream));
  TopoDS_Shape aNullShape;

  EXPECT_FALSE(myProvider->Write(aWriteStreams, aNullShape));

  std::string                 anInvalidContent = "This is not valid STEP content";
  std::istringstream          anInvalidStream(anInvalidContent);
  DE_Provider::ReadStreamList anInvalidReadStreams;
  anInvalidReadStreams.Append(DE_Provider::ReadStreamNode("invalid.step", anInvalidStream));

  TopoDS_Shape anInvalidShape;
  EXPECT_FALSE(myProvider->Read(anInvalidReadStreams, anInvalidShape));

  occ::handle<TDocStd_Document> aNullDoc;
  EXPECT_FALSE(myProvider->Write(aWriteStreams, aNullDoc));
  EXPECT_FALSE(myProvider->Read(anEmptyReadStreams, aNullDoc));
}

TEST_F(DESTEP_ProviderTest, ConfigurationModes)
{
  occ::handle<DESTEP_ConfigurationNode> aNode =
    occ::down_cast<DESTEP_ConfigurationNode>(myProvider->GetNode());

  EXPECT_FALSE(aNode.IsNull());

  EXPECT_STREQ("STEP", myProvider->GetFormat().ToCString());
  EXPECT_STREQ("OCC", myProvider->GetVendor().ToCString());

  occ::handle<DESTEP_ConfigurationNode> aNewNode     = new DESTEP_ConfigurationNode();
  occ::handle<DESTEP_Provider>          aNewProvider = new DESTEP_Provider(aNewNode);

  EXPECT_STREQ("STEP", aNewProvider->GetFormat().ToCString());
  EXPECT_STREQ("OCC", aNewProvider->GetVendor().ToCString());
  EXPECT_FALSE(aNewProvider->GetNode().IsNull());
}

TEST_F(DESTEP_ProviderTest, WorkSessionIntegration)
{
  occ::handle<XSControl_WorkSession> aWS = new XSControl_WorkSession();

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("ws_test.step", anOStream));

  EXPECT_TRUE(myProvider->Write(aWriteStreams, myBox, aWS));

  std::string aStepContent = anOStream.str();
  EXPECT_FALSE(aStepContent.empty());
  EXPECT_TRUE(IsValidSTEPContent(aStepContent));

  std::istringstream          anIStream(aStepContent);
  DE_Provider::ReadStreamList aReadStreams;
  aReadStreams.Append(DE_Provider::ReadStreamNode("ws_test.step", anIStream));

  TopoDS_Shape aReadShape;
  EXPECT_TRUE(myProvider->Read(aReadStreams, aReadShape, aWS));
  EXPECT_FALSE(aReadShape.IsNull());
}

TEST_F(DESTEP_ProviderTest, DocumentWorkSessionIntegration)
{

  occ::handle<XCAFDoc_ShapeTool> aShapeTool  = XCAFDoc_DocumentTool::ShapeTool(myDocument->Main());
  TDF_Label                      aShapeLabel = aShapeTool->AddShape(mySphere);
  EXPECT_FALSE(aShapeLabel.IsNull());

  occ::handle<XSControl_WorkSession> aWS = new XSControl_WorkSession();

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("doc_ws_test.step", anOStream));

  EXPECT_TRUE(myProvider->Write(aWriteStreams, myDocument, aWS));

  std::string aStepContent = anOStream.str();
  EXPECT_FALSE(aStepContent.empty());
  EXPECT_TRUE(IsValidSTEPContent(aStepContent));

  occ::handle<TDocStd_Application> anApp = new TDocStd_Application();
  occ::handle<TDocStd_Document>    aNewDocument;
  anApp->NewDocument("BinXCAF", aNewDocument);

  std::istringstream          anIStream(aStepContent);
  DE_Provider::ReadStreamList aReadStreams;
  aReadStreams.Append(DE_Provider::ReadStreamNode("doc_ws_test.step", anIStream));

  EXPECT_TRUE(myProvider->Read(aReadStreams, aNewDocument, aWS));

  occ::handle<XCAFDoc_ShapeTool> aNewShapeTool =
    XCAFDoc_DocumentTool::ShapeTool(aNewDocument->Main());
  NCollection_Sequence<TDF_Label> aLabels;
  aNewShapeTool->GetShapes(aLabels);
  EXPECT_GT(aLabels.Length(), 0);
}
