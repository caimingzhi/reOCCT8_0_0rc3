

#include <gp_Trsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <Precision.hpp>

#include <gtest/gtest.h>

TEST(gp_TrsfTest, OCC23361_TransformationComposition)
{
  gp_Pnt aP(0, 0, 2);

  gp_Trsf aT1, aT2;
  aT1.SetRotation(gp_Ax1(aP, gp_Dir(gp_Dir::D::Y)), -0.49328285294022267);
  aT2.SetRotation(gp_Ax1(aP, gp_Dir(gp_Dir::D::Z)), 0.87538474718473880);

  gp_Trsf aTComp = aT2 * aT1;

  gp_Pnt aP1(10, 3, 4);
  gp_Pnt aP2 = aP1.Transformed(aTComp);
  gp_Pnt aP3 = aP1.Transformed(aT1);
  aP3.Transform(aT2);

  EXPECT_TRUE(aP2.IsEqual(aP3, Precision::Confusion()));
}
