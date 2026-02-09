

#include <gtest/gtest.h>

#include <BRepAdaptor_CompCurve.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <gp_Pnt.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Wire.hpp>

TEST(BRepAdaptor_CompCurve_Test, OCC5696_EdgeMethod)
{

  TopoDS_Edge anEdge = BRepBuilderAPI_MakeEdge(gp_Pnt(0, 0, 0), gp_Pnt(2, 0, 0));

  TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(anEdge);

  BRepAdaptor_CompCurve aCurve(aWire);

  double aFirst = aCurve.FirstParameter();
  double aLast  = aCurve.LastParameter();
  double aPar   = (aFirst + aLast) / 2.0;

  double      aParEdge = 0.0;
  TopoDS_Edge anEdgeFound;

  EXPECT_NO_THROW({ aCurve.Edge(aPar, anEdgeFound, aParEdge); })
    << "Edge() method should not throw an exception";

  EXPECT_FALSE(anEdgeFound.IsNull()) << "Returned edge should not be null";

  EXPECT_GE(aParEdge, 0.0) << "Edge parameter should be non-negative";
  EXPECT_LE(aParEdge, 2.0) << "Edge parameter should not exceed edge length";

  EXPECT_NEAR(1.0, aParEdge, 0.01) << "Edge parameter should be approximately 1.0";
}
