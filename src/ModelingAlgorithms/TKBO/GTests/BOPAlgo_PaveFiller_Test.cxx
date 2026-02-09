

#include <gtest/gtest.h>

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepAlgoAPI_Fuse.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepBuilderAPI_MakeVertex.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <BRepGProp.hpp>
#include <BRepOffsetAPI_ThruSections.hpp>
#include <BRepPrimAPI_MakeBox.hpp>
#include <BRepPrimAPI_MakeCone.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Line.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_Surface.hpp>
#include <gp_Ax3.hpp>
#include <gp_Circ.hpp>
#include <gp_Pnt.hpp>
#include <GProp_GProps.hpp>
#include <Precision.hpp>
#include <ShapeFix_Shape.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>

class BOPAlgo_PaveFillerTest : public ::testing::Test
{
protected:
  static TopoDS_Wire CreateCircularWire(double theRadius, double theZ)
  {
    gp_Circ                 aCircle(gp_Ax2(gp_Pnt(0, 0, theZ), gp_Dir(0, 0, 1)), theRadius);
    BRepBuilderAPI_MakeEdge anEdgeMaker(aCircle);
    BRepBuilderAPI_MakeWire aWireMaker(anEdgeMaker.Edge());
    return aWireMaker.Wire();
  }

  static TopoDS_Vertex CreateVertex(const gp_Pnt& thePoint)
  {
    BRepBuilderAPI_MakeVertex aVertexMaker(thePoint);
    return aVertexMaker.Vertex();
  }

  static bool HasDegeneratedEdgesWithoutPCurves(const TopoDS_Shape& theShape)
  {
    for (TopExp_Explorer aFaceExp(theShape, TopAbs_FACE); aFaceExp.More(); aFaceExp.Next())
    {
      const TopoDS_Face& aFace = TopoDS::Face(aFaceExp.Current());
      for (TopExp_Explorer anEdgeExp(aFace, TopAbs_EDGE); anEdgeExp.More(); anEdgeExp.Next())
      {
        const TopoDS_Edge& anEdge = TopoDS::Edge(anEdgeExp.Current());
        if (BRep_Tool::Degenerated(anEdge))
        {
          double                    aFirst, aLast;
          occ::handle<Geom2d_Curve> aPCurve =
            BRep_Tool::CurveOnSurface(anEdge, aFace, aFirst, aLast);
          if (aPCurve.IsNull())
          {
            return true;
          }
        }
      }
    }
    return false;
  }

  static double GetVolume(const TopoDS_Shape& theShape)
  {
    GProp_GProps aProps;
    BRepGProp::VolumeProperties(theShape, aProps);
    return aProps.Mass();
  }
};

TEST_F(BOPAlgo_PaveFillerTest, FuseConeLoftWithBox_DegeneratedEdge)
{

  TopoDS_Wire   aBaseWire = CreateCircularWire(10.0, 0.0);
  TopoDS_Vertex anApex    = CreateVertex(gp_Pnt(0, 0, 20.0));

  BRepOffsetAPI_ThruSections aLoftMaker(true, true);
  aLoftMaker.AddWire(aBaseWire);
  aLoftMaker.AddVertex(anApex);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Loft operation should succeed";
  TopoDS_Shape aLoft = aLoftMaker.Shape();
  ASSERT_FALSE(aLoft.IsNull()) << "Loft shape should not be null";

  BRepPrimAPI_MakeBox aBoxMaker(gp_Pnt(-5, -5, 5), 10.0, 10.0, 10.0);
  TopoDS_Shape        aBox = aBoxMaker.Shape();

  BRepAlgoAPI_Fuse aFuser(aLoft, aBox);

  EXPECT_TRUE(aFuser.IsDone()) << "Boolean fuse should succeed for loft with degenerated edges";
  EXPECT_FALSE(aFuser.Shape().IsNull()) << "Result shape should not be null";

  double aLoftVolume   = GetVolume(aLoft);
  double aBoxVolume    = GetVolume(aBox);
  double aResultVolume = GetVolume(aFuser.Shape());

  EXPECT_GT(aResultVolume, 0.0) << "Result should have positive volume";
  EXPECT_LT(aResultVolume, aLoftVolume + aBoxVolume)
    << "Result volume should be less than sum of inputs";
}

TEST_F(BOPAlgo_PaveFillerTest, FuseConeWithBox_DegeneratedEdge)
{

  BRepPrimAPI_MakeCone aConeMaker(10.0, 0.0, 20.0);
  TopoDS_Shape         aCone = aConeMaker.Shape();
  ASSERT_FALSE(aCone.IsNull()) << "Cone should be created";

  BRepPrimAPI_MakeBox aBoxMaker(gp_Pnt(-5, -5, 15), 10.0, 10.0, 10.0);
  TopoDS_Shape        aBox = aBoxMaker.Shape();

  BRepAlgoAPI_Fuse aFuser(aCone, aBox);

  EXPECT_TRUE(aFuser.IsDone()) << "Boolean fuse of cone and box should succeed";
  EXPECT_FALSE(aFuser.Shape().IsNull()) << "Result shape should not be null";

  double aResultVolume = GetVolume(aFuser.Shape());
  EXPECT_GT(aResultVolume, 0.0) << "Result should have positive volume";
}

TEST_F(BOPAlgo_PaveFillerTest, FuseTwoLofts_RobustnessCheck)
{

  BRepBuilderAPI_MakeWire aWireMaker1;
  aWireMaker1.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(10, -10, 0), gp_Pnt(100, -10, 0)).Edge());
  aWireMaker1.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(100, -10, 0), gp_Pnt(100, -100, 0)).Edge());
  aWireMaker1.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(100, -100, 0), gp_Pnt(10, -100, 0)).Edge());
  aWireMaker1.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(10, -100, 0), gp_Pnt(10, -10, 0)).Edge());
  TopoDS_Wire aBottom1 = aWireMaker1.Wire();

  BRepBuilderAPI_MakeWire aWireMaker2;
  aWireMaker2.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0, 0, 10), gp_Pnt(100, 0, 10)).Edge());
  aWireMaker2.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(100, 0, 10), gp_Pnt(100, -100, 10)).Edge());
  aWireMaker2.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(100, -100, 10), gp_Pnt(0, -100, 10)).Edge());
  aWireMaker2.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0, -100, 10), gp_Pnt(0, 0, 10)).Edge());
  TopoDS_Wire aTop1 = aWireMaker2.Wire();

  BRepOffsetAPI_ThruSections aLoft1(true, true);
  aLoft1.AddWire(aBottom1);
  aLoft1.AddWire(aTop1);
  aLoft1.Build();
  ASSERT_TRUE(aLoft1.IsDone()) << "First loft should succeed";

  BRepBuilderAPI_MakeWire aWireMaker3;
  aWireMaker3.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0, 0, 10), gp_Pnt(100, 0, 10)).Edge());
  aWireMaker3.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(100, 0, 10), gp_Pnt(100, -100, 10)).Edge());
  aWireMaker3.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(100, -100, 10), gp_Pnt(0, -100, 10)).Edge());
  aWireMaker3.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0, -100, 10), gp_Pnt(0, 0, 10)).Edge());
  TopoDS_Wire aBottom2 = aWireMaker3.Wire();

  BRepBuilderAPI_MakeWire aWireMaker4;
  aWireMaker4.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0, 0, 250), gp_Pnt(100, 0, 250)).Edge());
  aWireMaker4.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(100, 0, 250), gp_Pnt(100, -100, 250)).Edge());
  aWireMaker4.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(100, -100, 250), gp_Pnt(0, -100, 250)).Edge());
  aWireMaker4.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0, -100, 250), gp_Pnt(0, 0, 250)).Edge());
  TopoDS_Wire aTop2 = aWireMaker4.Wire();

  BRepOffsetAPI_ThruSections aLoft2(true, true);
  aLoft2.AddWire(aBottom2);
  aLoft2.AddWire(aTop2);
  aLoft2.Build();
  ASSERT_TRUE(aLoft2.IsDone()) << "Second loft should succeed";

  BRepAlgoAPI_Fuse aFuser(aLoft1.Shape(), aLoft2.Shape());

  EXPECT_TRUE(aFuser.IsDone()) << "Boolean fuse of two lofts should succeed";
  EXPECT_FALSE(aFuser.Shape().IsNull()) << "Result shape should not be null";

  double aResultVolume = GetVolume(aFuser.Shape());
  EXPECT_GT(aResultVolume, 0.0) << "Result should have positive volume";
}

TEST_F(BOPAlgo_PaveFillerTest, FuseConeWithRemovedPCurve_NullPCurveHandling)
{

  BRepPrimAPI_MakeCone aConeMaker(10.0, 0.0, 20.0);
  TopoDS_Shape         aCone = aConeMaker.Shape();
  ASSERT_FALSE(aCone.IsNull()) << "Cone should be created";

  TopoDS_Face aConicalFace;
  TopoDS_Edge aDegeneratedEdge;

  for (TopExp_Explorer aFaceExp(aCone, TopAbs_FACE); aFaceExp.More(); aFaceExp.Next())
  {
    const TopoDS_Face& aFace = TopoDS::Face(aFaceExp.Current());
    for (TopExp_Explorer anEdgeExp(aFace, TopAbs_EDGE); anEdgeExp.More(); anEdgeExp.Next())
    {
      const TopoDS_Edge& anEdge = TopoDS::Edge(anEdgeExp.Current());
      if (BRep_Tool::Degenerated(anEdge))
      {
        aConicalFace     = aFace;
        aDegeneratedEdge = anEdge;
        break;
      }
    }
    if (!aDegeneratedEdge.IsNull())
      break;
  }

  if (!aDegeneratedEdge.IsNull())
  {

    occ::handle<Geom_Surface> aSurf  = BRep_Tool::Surface(aConicalFace);
    double                    aFirst = 0.0;
    double                    aLast  = 2.0 * M_PI;
    TopoDS_Vertex             aVertex =
      TopoDS::Vertex(TopExp_Explorer(aDegeneratedEdge, TopAbs_VERTEX).Current());

    BRep_Builder aBuilder;
    TopoDS_Edge  aNewDegEdge;
    aBuilder.MakeEdge(aNewDegEdge);
    aBuilder.Add(aNewDegEdge, aVertex.Oriented(TopAbs_FORWARD));
    aBuilder.Add(aNewDegEdge, aVertex.Oriented(TopAbs_REVERSED));
    aBuilder.Degenerated(aNewDegEdge, true);
    aBuilder.Range(aNewDegEdge, aFirst, aLast);

    TopoDS_Wire aNewWire;
    aBuilder.MakeWire(aNewWire);

    for (TopExp_Explorer aWireExp(aConicalFace, TopAbs_WIRE); aWireExp.More(); aWireExp.Next())
    {
      const TopoDS_Wire& aWire = TopoDS::Wire(aWireExp.Current());
      for (TopExp_Explorer anEdgeExp(aWire, TopAbs_EDGE); anEdgeExp.More(); anEdgeExp.Next())
      {
        const TopoDS_Edge& anEdge = TopoDS::Edge(anEdgeExp.Current());
        if (BRep_Tool::Degenerated(anEdge))
        {
          aBuilder.Add(aNewWire, aNewDegEdge.Oriented(anEdge.Orientation()));
        }
        else
        {
          aBuilder.Add(aNewWire, anEdge);
        }
      }
      break;
    }

    TopoDS_Face aNewFace;
    aBuilder.MakeFace(aNewFace, aSurf, Precision::Confusion());
    aBuilder.Add(aNewFace, aNewWire);

    TopoDS_Shell aNewShell;
    aBuilder.MakeShell(aNewShell);

    for (TopExp_Explorer aFaceExp2(aCone, TopAbs_FACE); aFaceExp2.More(); aFaceExp2.Next())
    {
      const TopoDS_Face& aFace = TopoDS::Face(aFaceExp2.Current());
      if (aFace.IsSame(aConicalFace))
      {
        aBuilder.Add(aNewShell, aNewFace);
      }
      else
      {
        aBuilder.Add(aNewShell, aFace);
      }
    }

    TopoDS_Solid aNewSolid;
    aBuilder.MakeSolid(aNewSolid);
    aBuilder.Add(aNewSolid, aNewShell);

    EXPECT_TRUE(HasDegeneratedEdgesWithoutPCurves(aNewSolid))
      << "Modified cone should have degenerated edge without pcurve";

    BRepPrimAPI_MakeBox aBoxMaker(gp_Pnt(-5, -5, 15), 10.0, 10.0, 10.0);
    TopoDS_Shape        aBox = aBoxMaker.Shape();

    BRepAlgoAPI_Fuse aFuser(aNewSolid, aBox);

    EXPECT_NO_THROW({
      bool isDone = aFuser.IsDone();
      (void)isDone;
    }) << "Boolean fuse should not crash even with missing pcurve";
  }
  else
  {

    BRepPrimAPI_MakeBox aBoxMaker(gp_Pnt(-5, -5, 15), 10.0, 10.0, 10.0);
    BRepAlgoAPI_Fuse    aFuser(aCone, aBoxMaker.Shape());
    EXPECT_TRUE(aFuser.IsDone());
  }
}
