

#include <DESTL_Provider.hpp>
#include <DESTL_ConfigurationNode.hpp>
#include <DE_Wrapper.hpp>

#include <BRepPrimAPI_MakeBox.hpp>
#include <BRepPrimAPI_MakeSphere.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRep_Builder.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Face.hpp>
#include <TopExp_Explorer.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pln.hpp>
#include <gp_Dir.hpp>
#include <Poly_Triangulation.hpp>
#include <Poly_Triangle.hpp>
#include <NCollection_Array1.hpp>
#include <BRep_Tool.hpp>
#include <TopLoc_Location.hpp>
#include <TDocStd_Document.hpp>
#include <TDocStd_Application.hpp>
#include <XCAFDoc_DocumentTool.hpp>
#include <XCAFDoc_ShapeTool.hpp>

#include <sstream>
#include <gtest/gtest.h>

class DESTL_ProviderTest : public ::testing::Test
{
protected:
  void SetUp() override
  {

    occ::handle<DESTL_ConfigurationNode> aNode = new DESTL_ConfigurationNode();
    myProvider                                 = new DESTL_Provider(aNode);

    myTriangularFace = CreateTriangulatedFace();

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

  TopoDS_Shape CreateTriangulatedFace()
  {

    NCollection_Array1<gp_Pnt> aNodes(1, 4);
    aNodes.SetValue(1, gp_Pnt(0.0, 0.0, 0.0));
    aNodes.SetValue(2, gp_Pnt(10.0, 0.0, 0.0));
    aNodes.SetValue(3, gp_Pnt(10.0, 10.0, 0.0));
    aNodes.SetValue(4, gp_Pnt(0.0, 10.0, 0.0));

    NCollection_Array1<Poly_Triangle> aTriangles(1, 2);
    aTriangles.SetValue(1, Poly_Triangle(1, 2, 3));
    aTriangles.SetValue(2, Poly_Triangle(1, 3, 4));

    occ::handle<Poly_Triangulation> aTriangulation = new Poly_Triangulation(aNodes, aTriangles);

    gp_Pln                  aPlane(gp_Pnt(0.0, 0.0, 0.0), gp_Dir(gp_Dir::D::Z));
    BRepBuilderAPI_MakeFace aFaceBuilder(aPlane, 0.0, 10.0, 0.0, 10.0);

    if (!aFaceBuilder.IsDone())
    {
      return TopoDS_Shape();
    }

    TopoDS_Face aFace = aFaceBuilder.Face();

    BRep_Builder aBuilder;
    aBuilder.UpdateFace(aFace, aTriangulation);

    return aFace;
  }

protected:
  occ::handle<DESTL_Provider>   myProvider;
  TopoDS_Shape                  myTriangularFace;
  occ::handle<TDocStd_Document> myDocument;
};

TEST_F(DESTL_ProviderTest, BasicProperties)
{
  EXPECT_STREQ("STL", myProvider->GetFormat().ToCString());
  EXPECT_STREQ("OCC", myProvider->GetVendor().ToCString());
  EXPECT_FALSE(myProvider->GetNode().IsNull());
}

TEST_F(DESTL_ProviderTest, StreamShapeWriteRead)
{
  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("test.stl", anOStream));

  EXPECT_TRUE(myProvider->Write(aWriteStreams, myTriangularFace));

  std::string aStlContent = anOStream.str();
  EXPECT_FALSE(aStlContent.empty());
  EXPECT_TRUE(aStlContent.find("solid") != std::string::npos
              || aStlContent.find("facet") != std::string::npos);

  if (!aStlContent.empty())
  {

    std::istringstream          anIStream(aStlContent);
    DE_Provider::ReadStreamList aReadStreams;
    aReadStreams.Append(DE_Provider::ReadStreamNode("test.stl", anIStream));

    TopoDS_Shape aReadShape;
    EXPECT_TRUE(myProvider->Read(aReadStreams, aReadShape));
    EXPECT_FALSE(aReadShape.IsNull());

    if (!aReadShape.IsNull())
    {

      int aReadFaces = CountShapeElements(aReadShape, TopAbs_FACE);
      EXPECT_GT(aReadFaces, 0);
    }
  }
}

TEST_F(DESTL_ProviderTest, StreamDocumentWriteRead)
{

  occ::handle<XCAFDoc_ShapeTool> aShapeTool  = XCAFDoc_DocumentTool::ShapeTool(myDocument->Main());
  TDF_Label                      aShapeLabel = aShapeTool->AddShape(myTriangularFace);
  EXPECT_FALSE(aShapeLabel.IsNull());

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("document.stl", anOStream));

  EXPECT_TRUE(myProvider->Write(aWriteStreams, myDocument));

  std::string aStlContent = anOStream.str();
  EXPECT_FALSE(aStlContent.empty());

  if (!aStlContent.empty())
  {

    occ::handle<TDocStd_Application> anApp = new TDocStd_Application();
    occ::handle<TDocStd_Document>    aNewDocument;
    anApp->NewDocument("BinXCAF", aNewDocument);

    std::istringstream          anIStream(aStlContent);
    DE_Provider::ReadStreamList aReadStreams;
    aReadStreams.Append(DE_Provider::ReadStreamNode("document.stl", anIStream));

    EXPECT_TRUE(myProvider->Read(aReadStreams, aNewDocument));

    occ::handle<XCAFDoc_ShapeTool> aNewShapeTool =
      XCAFDoc_DocumentTool::ShapeTool(aNewDocument->Main());
    NCollection_Sequence<TDF_Label> aLabels;
    aNewShapeTool->GetShapes(aLabels);
    EXPECT_GT(aLabels.Length(), 0);
  }
}

TEST_F(DESTL_ProviderTest, DE_WrapperIntegration)
{

  DE_Wrapper                           aWrapper;
  occ::handle<DESTL_ConfigurationNode> aNode = new DESTL_ConfigurationNode();

  EXPECT_TRUE(aWrapper.Bind(aNode));

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("test.stl", anOStream));

  EXPECT_TRUE(aWrapper.Write(aWriteStreams, myTriangularFace));

  std::string aStlContent = anOStream.str();
  EXPECT_FALSE(aStlContent.empty());

  if (!aStlContent.empty())
  {

    std::istringstream          anIStream(aStlContent);
    DE_Provider::ReadStreamList aReadStreams;
    aReadStreams.Append(DE_Provider::ReadStreamNode("test.stl", anIStream));

    TopoDS_Shape aReadShape;
    bool         aWrapperResult = aWrapper.Read(aReadStreams, aReadShape);

    std::istringstream          anIStream2(aStlContent);
    DE_Provider::ReadStreamList aReadStreams2;
    aReadStreams2.Append(DE_Provider::ReadStreamNode("test.stl", anIStream2));

    occ::handle<DESTL_Provider> aDirectProvider = new DESTL_Provider(aNode);
    TopoDS_Shape                aDirectShape;
    bool                        aDirectResult = aDirectProvider->Read(aReadStreams2, aDirectShape);

    EXPECT_EQ(aWrapperResult, aDirectResult);
    EXPECT_EQ(aReadShape.IsNull(), aDirectShape.IsNull());

    if (aDirectResult && !aDirectShape.IsNull())
    {
      int aFaces = CountShapeElements(aDirectShape, TopAbs_FACE);
      EXPECT_GT(aFaces, 0);
    }
  }
}

TEST_F(DESTL_ProviderTest, ErrorHandling)
{

  DE_Provider::WriteStreamList anEmptyWriteStreams;
  EXPECT_FALSE(myProvider->Write(anEmptyWriteStreams, myTriangularFace));

  DE_Provider::ReadStreamList anEmptyReadStreams;
  TopoDS_Shape                aShape;
  EXPECT_FALSE(myProvider->Read(anEmptyReadStreams, aShape));

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("null_test.stl", anOStream));
  TopoDS_Shape aNullShape;

  myProvider->Write(aWriteStreams, aNullShape);
  std::string aContent = anOStream.str();

  std::string                 anInvalidContent = "This is not valid STL content";
  std::istringstream          anInvalidStream(anInvalidContent);
  DE_Provider::ReadStreamList anInvalidReadStreams;
  anInvalidReadStreams.Append(DE_Provider::ReadStreamNode("invalid.stl", anInvalidStream));

  TopoDS_Shape anInvalidShape;
  EXPECT_FALSE(myProvider->Read(anInvalidReadStreams, anInvalidShape));

  occ::handle<TDocStd_Document> aNullDoc;
  EXPECT_FALSE(myProvider->Write(aWriteStreams, aNullDoc));
  EXPECT_FALSE(myProvider->Read(anEmptyReadStreams, aNullDoc));
}

TEST_F(DESTL_ProviderTest, ConfigurationModes)
{
  occ::handle<DESTL_ConfigurationNode> aNode =
    occ::down_cast<DESTL_ConfigurationNode>(myProvider->GetNode());

  aNode->InternalParameters.WriteAscii = true;
  EXPECT_TRUE(aNode->InternalParameters.WriteAscii);

  aNode->InternalParameters.WriteAscii = false;
  EXPECT_FALSE(aNode->InternalParameters.WriteAscii);

  aNode->InternalParameters.ReadMergeAngle = 45.0;
  EXPECT_DOUBLE_EQ(45.0, aNode->InternalParameters.ReadMergeAngle);

  EXPECT_STREQ("STL", myProvider->GetFormat().ToCString());
  EXPECT_STREQ("OCC", myProvider->GetVendor().ToCString());
}

TEST_F(DESTL_ProviderTest, AsciiVsBinaryModes)
{
  occ::handle<DESTL_ConfigurationNode> aNode =
    occ::down_cast<DESTL_ConfigurationNode>(myProvider->GetNode());

  aNode->InternalParameters.WriteAscii = true;

  std::ostringstream           anAsciiStream;
  DE_Provider::WriteStreamList anAsciiWriteStreams;
  anAsciiWriteStreams.Append(DE_Provider::WriteStreamNode("ascii_test.stl", anAsciiStream));

  EXPECT_TRUE(myProvider->Write(anAsciiWriteStreams, myTriangularFace));
  std::string anAsciiContent = anAsciiStream.str();
  EXPECT_FALSE(anAsciiContent.empty());
  EXPECT_TRUE(anAsciiContent.find("solid") != std::string::npos);

  aNode->InternalParameters.WriteAscii = false;

  std::ostringstream           aBinaryStream;
  DE_Provider::WriteStreamList aBinaryWriteStreams;
  aBinaryWriteStreams.Append(DE_Provider::WriteStreamNode("binary_test.stl", aBinaryStream));

  EXPECT_TRUE(myProvider->Write(aBinaryWriteStreams, myTriangularFace));
  std::string aBinaryContent = aBinaryStream.str();
  EXPECT_FALSE(aBinaryContent.empty());

  EXPECT_NE(anAsciiContent, aBinaryContent);
}

TEST_F(DESTL_ProviderTest, MultipleShapesInDocument)
{

  occ::handle<XCAFDoc_ShapeTool> aShapeTool  = XCAFDoc_DocumentTool::ShapeTool(myDocument->Main());
  TDF_Label                      aFaceLabel1 = aShapeTool->AddShape(myTriangularFace);
  TDF_Label                      aFaceLabel2 = aShapeTool->AddShape(myTriangularFace);

  EXPECT_FALSE(aFaceLabel1.IsNull());
  EXPECT_FALSE(aFaceLabel2.IsNull());

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("multi_shapes.stl", anOStream));

  EXPECT_TRUE(myProvider->Write(aWriteStreams, myDocument));

  std::string aStlContent = anOStream.str();
  EXPECT_FALSE(aStlContent.empty());

  occ::handle<TDocStd_Application> anApp = new TDocStd_Application();
  occ::handle<TDocStd_Document>    aNewDocument;
  anApp->NewDocument("BinXCAF", aNewDocument);

  std::istringstream          anIStream(aStlContent);
  DE_Provider::ReadStreamList aReadStreams;
  aReadStreams.Append(DE_Provider::ReadStreamNode("multi_shapes.stl", anIStream));

  EXPECT_TRUE(myProvider->Read(aReadStreams, aNewDocument));

  occ::handle<XCAFDoc_ShapeTool> aNewShapeTool =
    XCAFDoc_DocumentTool::ShapeTool(aNewDocument->Main());
  NCollection_Sequence<TDF_Label> aLabels;
  aNewShapeTool->GetShapes(aLabels);
  EXPECT_GT(aLabels.Length(), 0);
}

TEST_F(DESTL_ProviderTest, TriangulatedFaceHandling)
{

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("triangulated_face.stl", anOStream));

  EXPECT_TRUE(myProvider->Write(aWriteStreams, myTriangularFace));

  std::string aStlContent = anOStream.str();
  EXPECT_FALSE(aStlContent.empty());
  EXPECT_GT(aStlContent.size(), 100);

  std::istringstream          anIStream(aStlContent);
  DE_Provider::ReadStreamList aReadStreams;
  aReadStreams.Append(DE_Provider::ReadStreamNode("triangulated_face.stl", anIStream));

  TopoDS_Shape aReadShape;
  EXPECT_TRUE(myProvider->Read(aReadStreams, aReadShape));
  EXPECT_FALSE(aReadShape.IsNull());
}

TEST_F(DESTL_ProviderTest, DE_WrapperFileExtensions)
{
  DE_Wrapper                           aWrapper;
  occ::handle<DESTL_ConfigurationNode> aNode = new DESTL_ConfigurationNode();
  EXPECT_TRUE(aWrapper.Bind(aNode));

  std::vector<std::string> aExtensions = {"test.stl", "test.STL", "mesh.stl"};

  for (const auto& anExt : aExtensions)
  {
    std::ostringstream           anOStream;
    DE_Provider::WriteStreamList aWriteStreams;
    aWriteStreams.Append(DE_Provider::WriteStreamNode(anExt.c_str(), anOStream));

    EXPECT_TRUE(aWrapper.Write(aWriteStreams, myTriangularFace))
      << "Failed to write with extension: " << anExt;

    std::string aContent = anOStream.str();
    EXPECT_FALSE(aContent.empty()) << "Empty content for extension: " << anExt;

    std::istringstream          anIStream(aContent);
    DE_Provider::ReadStreamList aReadStreams;
    aReadStreams.Append(DE_Provider::ReadStreamNode(anExt.c_str(), anIStream));

    TopoDS_Shape aReadShape;
    EXPECT_TRUE(aWrapper.Read(aReadStreams, aReadShape))
      << "Failed to read with extension: " << anExt;
    EXPECT_FALSE(aReadShape.IsNull()) << "Null shape read with extension: " << anExt;
  }
}

TEST_F(DESTL_ProviderTest, StreamErrorConditions)
{

  DE_Provider::WriteStreamList anEmptyWriteStreams;
  EXPECT_FALSE(myProvider->Write(anEmptyWriteStreams, myTriangularFace));

  DE_Provider::ReadStreamList anEmptyReadStreams;
  TopoDS_Shape                aShape;
  EXPECT_FALSE(myProvider->Read(anEmptyReadStreams, aShape));

  std::string                 aCorruptedData = "This is not STL data at all";
  std::istringstream          aCorruptedStream(aCorruptedData);
  DE_Provider::ReadStreamList aCorruptedReadStreams;
  aCorruptedReadStreams.Append(DE_Provider::ReadStreamNode("corrupted.stl", aCorruptedStream));

  TopoDS_Shape aCorruptedShape;
  EXPECT_FALSE(myProvider->Read(aCorruptedReadStreams, aCorruptedShape));

  std::string                 aPartialData = "solid test\n  facet normal 0 0 1\n";
  std::istringstream          aPartialStream(aPartialData);
  DE_Provider::ReadStreamList aPartialReadStreams;
  aPartialReadStreams.Append(DE_Provider::ReadStreamNode("partial.stl", aPartialStream));

  TopoDS_Shape aPartialShape;
  EXPECT_FALSE(myProvider->Read(aPartialReadStreams, aPartialShape));
}

TEST_F(DESTL_ProviderTest, ConfigurationParameterValidation)
{
  occ::handle<DESTL_ConfigurationNode> aNode =
    occ::down_cast<DESTL_ConfigurationNode>(myProvider->GetNode());

  aNode->InternalParameters.ReadMergeAngle = 30.0;
  EXPECT_DOUBLE_EQ(30.0, aNode->InternalParameters.ReadMergeAngle);

  aNode->InternalParameters.ReadMergeAngle = 0.0;
  EXPECT_DOUBLE_EQ(0.0, aNode->InternalParameters.ReadMergeAngle);

  aNode->InternalParameters.ReadMergeAngle = 90.0;
  EXPECT_DOUBLE_EQ(90.0, aNode->InternalParameters.ReadMergeAngle);

  aNode->InternalParameters.ReadBRep = true;
  EXPECT_TRUE(aNode->InternalParameters.ReadBRep);

  aNode->InternalParameters.ReadBRep = false;
  EXPECT_FALSE(aNode->InternalParameters.ReadBRep);
}

TEST_F(DESTL_ProviderTest, MultipleTriangulatedFaces)
{

  NCollection_Array1<gp_Pnt> aNodes(1, 3);
  aNodes.SetValue(1, gp_Pnt(0.0, 0.0, 0.0));
  aNodes.SetValue(2, gp_Pnt(5.0, 0.0, 0.0));
  aNodes.SetValue(3, gp_Pnt(2.5, 5.0, 0.0));

  NCollection_Array1<Poly_Triangle> aTriangles(1, 1);
  aTriangles.SetValue(1, Poly_Triangle(1, 2, 3));

  occ::handle<Poly_Triangulation> aTriangulation = new Poly_Triangulation(aNodes, aTriangles);

  gp_Pln                  aPlane(gp_Pnt(0.0, 0.0, 0.0), gp_Dir(gp_Dir::D::Z));
  BRepBuilderAPI_MakeFace aFaceBuilder(aPlane, 0.0, 5.0, 0.0, 5.0);
  TopoDS_Face             aTriangleFace = aFaceBuilder.Face();

  BRep_Builder aBuilder;
  aBuilder.UpdateFace(aTriangleFace, aTriangulation);

  std::ostringstream           aStream1;
  DE_Provider::WriteStreamList aWriteStreams1;
  aWriteStreams1.Append(DE_Provider::WriteStreamNode("face1.stl", aStream1));

  EXPECT_TRUE(myProvider->Write(aWriteStreams1, myTriangularFace));
  std::string aContent1 = aStream1.str();

  std::ostringstream           aStream2;
  DE_Provider::WriteStreamList aWriteStreams2;
  aWriteStreams2.Append(DE_Provider::WriteStreamNode("face2.stl", aStream2));

  EXPECT_TRUE(myProvider->Write(aWriteStreams2, aTriangleFace));
  std::string aContent2 = aStream2.str();

  EXPECT_FALSE(aContent1.empty());
  EXPECT_FALSE(aContent2.empty());

  EXPECT_NE(aContent1, aContent2);

  std::istringstream          aIStream1(aContent1);
  DE_Provider::ReadStreamList aReadStreams1;
  aReadStreams1.Append(DE_Provider::ReadStreamNode("face1.stl", aIStream1));

  TopoDS_Shape aReadShape1;
  EXPECT_TRUE(myProvider->Read(aReadStreams1, aReadShape1));
  EXPECT_FALSE(aReadShape1.IsNull());

  std::istringstream          aIStream2(aContent2);
  DE_Provider::ReadStreamList aReadStreams2;
  aReadStreams2.Append(DE_Provider::ReadStreamNode("face2.stl", aIStream2));

  TopoDS_Shape aReadShape2;
  EXPECT_TRUE(myProvider->Read(aReadStreams2, aReadShape2));
  EXPECT_FALSE(aReadShape2.IsNull());
}
