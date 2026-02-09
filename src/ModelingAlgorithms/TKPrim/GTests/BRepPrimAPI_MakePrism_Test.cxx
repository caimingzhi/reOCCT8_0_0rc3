

#include <BRepBuilderAPI_MakeVertex.hpp>
#include <BRepPrimAPI_MakePrism.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

#include <gtest/gtest.h>

TEST(BRepPrimAPI_MakePrism_Test, OCC31294_GeneratedListForNonBaseShape)
{

  BRepBuilderAPI_MakeVertex aMkVert(gp_Pnt(0., 0., 0.));
  BRepBuilderAPI_MakeVertex aMkDummy(gp_Pnt(0., 0., 0.));
  BRepPrimAPI_MakePrism     aMkPrism(aMkVert.Shape(), gp_Vec(0., 0., 1.));

  int aNbGen = aMkPrism.Generated(aMkVert.Shape()).Extent();
  EXPECT_EQ(aNbGen, 1);

  int aNbDummy = aMkPrism.Generated(aMkDummy.Shape()).Extent();
  EXPECT_EQ(aNbDummy, 0);
}
