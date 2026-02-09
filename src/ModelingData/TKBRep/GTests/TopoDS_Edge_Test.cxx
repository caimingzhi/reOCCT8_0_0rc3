

#include <gtest/gtest.h>

#include <BRepBuilderAPI_MakeEdge.hpp>
#include <gp_Pnt.hpp>
#include <TopoDS_Edge.hpp>

TEST(TopoDS_Edge_Test, BUC60828_InfiniteFlag)
{

  TopoDS_Edge anEdge = BRepBuilderAPI_MakeEdge(gp_Pnt(0., 0., 0.), gp_Pnt(0., 0., 1.));

  bool anInitialValue = anEdge.Infinite();
  EXPECT_FALSE(anInitialValue) << "Initial Infinite flag should be false";

  anEdge.Infinite(true);

  bool aCurrentValue = anEdge.Infinite();
  EXPECT_TRUE(aCurrentValue) << "Infinite flag should be true after setting";
}
