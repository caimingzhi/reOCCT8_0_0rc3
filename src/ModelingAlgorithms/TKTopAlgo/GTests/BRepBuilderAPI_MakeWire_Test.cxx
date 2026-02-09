

#include <BRep_Builder.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <gp_Pnt.hpp>

#include <gtest/gtest.h>

TEST(BRepBuilderAPI_MakeWire_Test, OCC27552_AddEdgesAndListOfEdges)
{

  BRep_Builder  aBB;
  TopoDS_Vertex aV1, aV2, aV3;
  TopoDS_Edge   anE1, anE2;

  aBB.MakeVertex(aV1, gp_Pnt(0, 0, 0), 0.1);
  aBB.MakeVertex(aV2, gp_Pnt(5, 0, 0), 0.1);
  aBB.MakeVertex(aV3, gp_Pnt(10, 0, 0), 0.1);

  anE1 = BRepBuilderAPI_MakeEdge(aV1, aV2).Edge();
  anE2 = BRepBuilderAPI_MakeEdge(aV2, aV3).Edge();

  BRepBuilderAPI_MakeWire aMW;
  EXPECT_NO_THROW(aMW.Add(anE1));
  EXPECT_NO_THROW(aMW.Add(anE2));

  TopoDS_Vertex aV4, aV5, aV6, aV7;
  TopoDS_Edge   anE3, anE4;
  aBB.MakeVertex(aV4, gp_Pnt(10, 0.05, 0), 0.07);
  aBB.MakeVertex(aV5, gp_Pnt(10, -0.05, 0), 0.07);
  aBB.MakeVertex(aV6, gp_Pnt(10, 2, 0), 0.07);
  aBB.MakeVertex(aV7, gp_Pnt(10, -2, 0), 0.07);

  anE3 = BRepBuilderAPI_MakeEdge(aV4, aV6).Edge();
  anE4 = BRepBuilderAPI_MakeEdge(aV5, aV7).Edge();

  NCollection_List<TopoDS_Shape> aListOfEdges;
  aListOfEdges.Append(anE3);
  aListOfEdges.Append(anE4);

  EXPECT_NO_THROW(aMW.Add(aListOfEdges));

  EXPECT_TRUE(aMW.IsDone()) << "Wire builder should complete successfully";
  TopoDS_Wire aWire = aMW.Wire();
  EXPECT_FALSE(aWire.IsNull()) << "Resulting wire should not be null";
}
