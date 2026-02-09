

#include <DEVRML_Provider.hpp>
#include <DEVRML_ConfigurationNode.hpp>
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

class DEVRML_ProviderTest : public ::testing::Test
{
protected:
  void SetUp() override
  {

    occ::handle<DEVRML_ConfigurationNode> aNode = new DEVRML_ConfigurationNode();
    myProvider                                  = new DEVRML_Provider(aNode);

    myBox            = BRepPrimAPI_MakeBox(10.0, 10.0, 10.0).Shape();
    mySphere         = BRepPrimAPI_MakeSphere(5.0).Shape();
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
  occ::handle<DEVRML_Provider>  myProvider;
  TopoDS_Shape                  myBox;
  TopoDS_Shape                  mySphere;
  TopoDS_Shape                  myTriangularFace;
  occ::handle<TDocStd_Document> myDocument;
};

TEST_F(DEVRML_ProviderTest, BasicProperties)
{
  EXPECT_STREQ("VRML", myProvider->GetFormat().ToCString());
  EXPECT_STREQ("OCC", myProvider->GetVendor().ToCString());
  EXPECT_FALSE(myProvider->GetNode().IsNull());
}

TEST_F(DEVRML_ProviderTest, StreamShapeWriteReadWireframe)
{

  occ::handle<DEVRML_ConfigurationNode> aNode =
    occ::down_cast<DEVRML_ConfigurationNode>(myProvider->GetNode());
  aNode->InternalParameters.WriteRepresentationType =
    DEVRML_ConfigurationNode::WriteMode_RepresentationType_Wireframe;

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("wireframe.vrml", anOStream));

  EXPECT_TRUE(myProvider->Write(aWriteStreams, myBox));

  std::string aVrmlContent = anOStream.str();
  EXPECT_FALSE(aVrmlContent.empty());
  EXPECT_TRUE(aVrmlContent.find("#VRML") != std::string::npos);

  if (!aVrmlContent.empty())
  {

    std::istringstream          anIStream(aVrmlContent);
    DE_Provider::ReadStreamList aReadStreams;
    aReadStreams.Append(DE_Provider::ReadStreamNode("wireframe.vrml", anIStream));

    TopoDS_Shape aReadShape;
    EXPECT_TRUE(myProvider->Read(aReadStreams, aReadShape));
    EXPECT_FALSE(aReadShape.IsNull());

    if (!aReadShape.IsNull())
    {

      int aReadEdges = CountShapeElements(aReadShape, TopAbs_EDGE);
      EXPECT_TRUE(aReadEdges > 0);
    }
  }
}

TEST_F(DEVRML_ProviderTest, StreamShapeWriteReadShaded)
{

  occ::handle<DEVRML_ConfigurationNode> aNode =
    occ::down_cast<DEVRML_ConfigurationNode>(myProvider->GetNode());
  aNode->InternalParameters.WriteRepresentationType =
    DEVRML_ConfigurationNode::WriteMode_RepresentationType_Shaded;

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("shaded.vrml", anOStream));

  EXPECT_TRUE(myProvider->Write(aWriteStreams, myTriangularFace));

  std::string aVrmlContent = anOStream.str();
  EXPECT_FALSE(aVrmlContent.empty());
  EXPECT_TRUE(aVrmlContent.find("#VRML") != std::string::npos);

  if (!aVrmlContent.empty())
  {

    std::istringstream          anIStream(aVrmlContent);
    DE_Provider::ReadStreamList aReadStreams;
    aReadStreams.Append(DE_Provider::ReadStreamNode("shaded.vrml", anIStream));

    TopoDS_Shape aReadShape;
    EXPECT_TRUE(myProvider->Read(aReadStreams, aReadShape));
    EXPECT_FALSE(aReadShape.IsNull());

    if (!aReadShape.IsNull())
    {

      int aReadFaces = CountShapeElements(aReadShape, TopAbs_FACE);
      EXPECT_TRUE(aReadFaces > 0);
    }
  }
}

TEST_F(DEVRML_ProviderTest, StreamDocumentWriteRead)
{

  occ::handle<DEVRML_ConfigurationNode> aNode =
    occ::down_cast<DEVRML_ConfigurationNode>(myProvider->GetNode());
  aNode->InternalParameters.WriteRepresentationType =
    DEVRML_ConfigurationNode::WriteMode_RepresentationType_Shaded;

  occ::handle<XCAFDoc_ShapeTool> aShapeTool  = XCAFDoc_DocumentTool::ShapeTool(myDocument->Main());
  TDF_Label                      aShapeLabel = aShapeTool->AddShape(myTriangularFace);
  EXPECT_FALSE(aShapeLabel.IsNull());

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("document.vrml", anOStream));

  EXPECT_TRUE(myProvider->Write(aWriteStreams, myDocument));

  std::string aVrmlContent = anOStream.str();
  EXPECT_FALSE(aVrmlContent.empty());
  EXPECT_TRUE(aVrmlContent.find("#VRML") != std::string::npos);

  if (!aVrmlContent.empty())
  {

    occ::handle<TDocStd_Application> anApp = new TDocStd_Application();
    occ::handle<TDocStd_Document>    aNewDocument;
    anApp->NewDocument("BinXCAF", aNewDocument);

    std::istringstream          anIStream(aVrmlContent);
    DE_Provider::ReadStreamList aReadStreams;
    aReadStreams.Append(DE_Provider::ReadStreamNode("document.vrml", anIStream));

    EXPECT_TRUE(myProvider->Read(aReadStreams, aNewDocument));

    occ::handle<XCAFDoc_ShapeTool> aNewShapeTool =
      XCAFDoc_DocumentTool::ShapeTool(aNewDocument->Main());
    NCollection_Sequence<TDF_Label> aLabels;
    aNewShapeTool->GetShapes(aLabels);
    EXPECT_GT(aLabels.Length(), 0);
  }
}

TEST_F(DEVRML_ProviderTest, StreamDocumentMultipleShapes)
{

  occ::handle<DEVRML_ConfigurationNode> aNode =
    occ::down_cast<DEVRML_ConfigurationNode>(myProvider->GetNode());
  aNode->InternalParameters.WriteRepresentationType =
    DEVRML_ConfigurationNode::WriteMode_RepresentationType_Shaded;

  occ::handle<XCAFDoc_ShapeTool> aShapeTool  = XCAFDoc_DocumentTool::ShapeTool(myDocument->Main());
  TDF_Label                      aFirstLabel = aShapeTool->AddShape(myTriangularFace);
  EXPECT_FALSE(aFirstLabel.IsNull());

  TDF_Label aSecondLabel = aShapeTool->AddShape(mySphere);
  EXPECT_FALSE(aSecondLabel.IsNull());

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("multi_shapes.vrml", anOStream));

  EXPECT_TRUE(myProvider->Write(aWriteStreams, myDocument));

  std::string aVrmlContent = anOStream.str();
  EXPECT_FALSE(aVrmlContent.empty());
  EXPECT_TRUE(aVrmlContent.find("#VRML") != std::string::npos);

  if (!aVrmlContent.empty())
  {

    occ::handle<TDocStd_Application> anApp = new TDocStd_Application();
    occ::handle<TDocStd_Document>    aNewDocument;
    anApp->NewDocument("BinXCAF", aNewDocument);

    std::istringstream          anIStream(aVrmlContent);
    DE_Provider::ReadStreamList aReadStreams;
    aReadStreams.Append(DE_Provider::ReadStreamNode("multi_shapes.vrml", anIStream));

    EXPECT_TRUE(myProvider->Read(aReadStreams, aNewDocument));

    occ::handle<XCAFDoc_ShapeTool> aNewShapeTool =
      XCAFDoc_DocumentTool::ShapeTool(aNewDocument->Main());
    NCollection_Sequence<TDF_Label> aLabels;
    aNewShapeTool->GetShapes(aLabels);
    EXPECT_GT(aLabels.Length(), 0);
  }
}

TEST_F(DEVRML_ProviderTest, DE_WrapperIntegration)
{

  DE_Wrapper                            aWrapper;
  occ::handle<DEVRML_ConfigurationNode> aNode = new DEVRML_ConfigurationNode();

  aNode->InternalParameters.WriteRepresentationType =
    DEVRML_ConfigurationNode::WriteMode_RepresentationType_Shaded;

  EXPECT_TRUE(aWrapper.Bind(aNode));

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("test.vrml", anOStream));

  EXPECT_TRUE(aWrapper.Write(aWriteStreams, myTriangularFace));

  std::string aVrmlContent = anOStream.str();
  EXPECT_FALSE(aVrmlContent.empty());
  EXPECT_TRUE(aVrmlContent.find("#VRML") != std::string::npos);

  if (!aVrmlContent.empty())
  {

    std::istringstream          anIStream(aVrmlContent);
    DE_Provider::ReadStreamList aReadStreams;
    aReadStreams.Append(DE_Provider::ReadStreamNode("test.vrml", anIStream));

    TopoDS_Shape aReadShape;
    bool         aWrapperResult = aWrapper.Read(aReadStreams, aReadShape);

    std::istringstream          anIStream2(aVrmlContent);
    DE_Provider::ReadStreamList aReadStreams2;
    aReadStreams2.Append(DE_Provider::ReadStreamNode("test.vrml", anIStream2));

    occ::handle<DEVRML_Provider> aDirectProvider = new DEVRML_Provider(aNode);
    TopoDS_Shape                 aDirectShape;
    bool                         aDirectResult = aDirectProvider->Read(aReadStreams2, aDirectShape);

    EXPECT_EQ(aWrapperResult, aDirectResult);
    EXPECT_EQ(aReadShape.IsNull(), aDirectShape.IsNull());

    if (aDirectResult && !aDirectShape.IsNull())
    {
      int aFaces = CountShapeElements(aDirectShape, TopAbs_FACE);
      EXPECT_GT(aFaces, 0);
    }
    else if (aWrapperResult && !aReadShape.IsNull())
    {
      int aFaces = CountShapeElements(aReadShape, TopAbs_FACE);
      EXPECT_GT(aFaces, 0);
    }
  }
}

TEST_F(DEVRML_ProviderTest, DE_WrapperDocumentOperations)
{

  DE_Wrapper                            aWrapper;
  occ::handle<DEVRML_ConfigurationNode> aNode = new DEVRML_ConfigurationNode();

  aNode->InternalParameters.WriteRepresentationType =
    DEVRML_ConfigurationNode::WriteMode_RepresentationType_Shaded;

  EXPECT_TRUE(aWrapper.Bind(aNode));

  occ::handle<XCAFDoc_ShapeTool> aShapeTool  = XCAFDoc_DocumentTool::ShapeTool(myDocument->Main());
  TDF_Label                      aShapeLabel = aShapeTool->AddShape(myTriangularFace);
  EXPECT_FALSE(aShapeLabel.IsNull());

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("doc.vrml", anOStream));

  EXPECT_TRUE(aWrapper.Write(aWriteStreams, myDocument));

  std::string aVrmlContent = anOStream.str();
  EXPECT_FALSE(aVrmlContent.empty());
  EXPECT_TRUE(aVrmlContent.find("#VRML") != std::string::npos);

  if (!aVrmlContent.empty())
  {

    occ::handle<TDocStd_Application> anApp = new TDocStd_Application();
    occ::handle<TDocStd_Document>    aNewDocument;
    anApp->NewDocument("BinXCAF", aNewDocument);

    std::istringstream          anIStream(aVrmlContent);
    DE_Provider::ReadStreamList aReadStreams;
    aReadStreams.Append(DE_Provider::ReadStreamNode("doc.vrml", anIStream));

    bool aWrapperDocResult = aWrapper.Read(aReadStreams, aNewDocument);

    if (aWrapperDocResult)
    {
      occ::handle<XCAFDoc_ShapeTool> aNewShapeTool =
        XCAFDoc_DocumentTool::ShapeTool(aNewDocument->Main());
      NCollection_Sequence<TDF_Label> aLabels;
      aNewShapeTool->GetShapes(aLabels);
      EXPECT_GT(aLabels.Length(), 0);
    }
    else
    {

      occ::handle<TDocStd_Application> anApp2 = new TDocStd_Application();
      occ::handle<TDocStd_Document>    aTestDocument;
      anApp2->NewDocument("BinXCAF", aTestDocument);

      std::istringstream          anIStream2(aVrmlContent);
      DE_Provider::ReadStreamList aReadStreams2;
      aReadStreams2.Append(DE_Provider::ReadStreamNode("doc.vrml", anIStream2));

      occ::handle<DEVRML_Provider> aDirectProvider = new DEVRML_Provider(aNode);
      bool aDirectDocResult = aDirectProvider->Read(aReadStreams2, aTestDocument);

      if (aDirectDocResult)
      {
        occ::handle<XCAFDoc_ShapeTool> aTestShapeTool =
          XCAFDoc_DocumentTool::ShapeTool(aTestDocument->Main());
        NCollection_Sequence<TDF_Label> aTestLabels;
        aTestShapeTool->GetShapes(aTestLabels);
        EXPECT_GT(aTestLabels.Length(), 0);
      }
    }
  }
}

TEST_F(DEVRML_ProviderTest, ErrorHandling)
{

  DE_Provider::WriteStreamList anEmptyWriteStreams;
  EXPECT_FALSE(myProvider->Write(anEmptyWriteStreams, myBox));

  DE_Provider::ReadStreamList anEmptyReadStreams;
  TopoDS_Shape                aShape;
  EXPECT_FALSE(myProvider->Read(anEmptyReadStreams, aShape));

  std::ostringstream           anOStream;
  DE_Provider::WriteStreamList aWriteStreams;
  aWriteStreams.Append(DE_Provider::WriteStreamNode("null_test.vrml", anOStream));
  TopoDS_Shape aNullShape;

  myProvider->Write(aWriteStreams, aNullShape);
  std::string aContent = anOStream.str();
  EXPECT_FALSE(aContent.empty());

  std::string                 anInvalidContent = "This is not valid VRML content";
  std::istringstream          anInvalidStream(anInvalidContent);
  DE_Provider::ReadStreamList anInvalidReadStreams;
  anInvalidReadStreams.Append(DE_Provider::ReadStreamNode("invalid.vrml", anInvalidStream));

  TopoDS_Shape anInvalidShape;
  EXPECT_FALSE(myProvider->Read(anInvalidReadStreams, anInvalidShape));

  occ::handle<TDocStd_Document> aNullDoc;
  EXPECT_FALSE(myProvider->Write(aWriteStreams, aNullDoc));
  EXPECT_FALSE(myProvider->Read(anEmptyReadStreams, aNullDoc));
}

TEST_F(DEVRML_ProviderTest, ConfigurationModes)
{
  occ::handle<DEVRML_ConfigurationNode> aNode =
    occ::down_cast<DEVRML_ConfigurationNode>(myProvider->GetNode());

  aNode->InternalParameters.WriteRepresentationType =
    DEVRML_ConfigurationNode::WriteMode_RepresentationType_Wireframe;
  EXPECT_EQ(aNode->InternalParameters.WriteRepresentationType,
            DEVRML_ConfigurationNode::WriteMode_RepresentationType_Wireframe);

  aNode->InternalParameters.WriteRepresentationType =
    DEVRML_ConfigurationNode::WriteMode_RepresentationType_Shaded;
  EXPECT_EQ(aNode->InternalParameters.WriteRepresentationType,
            DEVRML_ConfigurationNode::WriteMode_RepresentationType_Shaded);

  aNode->InternalParameters.WriteRepresentationType =
    DEVRML_ConfigurationNode::WriteMode_RepresentationType_Both;
  EXPECT_EQ(aNode->InternalParameters.WriteRepresentationType,
            DEVRML_ConfigurationNode::WriteMode_RepresentationType_Both);

  aNode->InternalParameters.WriterVersion = DEVRML_ConfigurationNode::WriteMode_WriterVersion_1;
  EXPECT_EQ(aNode->InternalParameters.WriterVersion,
            DEVRML_ConfigurationNode::WriteMode_WriterVersion_1);

  aNode->InternalParameters.WriterVersion = DEVRML_ConfigurationNode::WriteMode_WriterVersion_2;
  EXPECT_EQ(aNode->InternalParameters.WriterVersion,
            DEVRML_ConfigurationNode::WriteMode_WriterVersion_2);

  EXPECT_STREQ("VRML", myProvider->GetFormat().ToCString());
  EXPECT_STREQ("OCC", myProvider->GetVendor().ToCString());
}
