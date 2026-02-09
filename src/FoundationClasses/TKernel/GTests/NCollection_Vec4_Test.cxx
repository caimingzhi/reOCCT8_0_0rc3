

#include <NCollection_Vec4.hpp>
#include <NCollection_Vec3.hpp>
#include <NCollection_Mat4.hpp>

#include <gtest/gtest.h>
#include <cmath>

class NCollection_Vec4Test : public testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(NCollection_Vec4Test, BasicConstruction)
{

  NCollection_Vec4<float> aVec1;
  EXPECT_EQ(0.0f, aVec1.x());
  EXPECT_EQ(0.0f, aVec1.y());
  EXPECT_EQ(0.0f, aVec1.z());
  EXPECT_EQ(0.0f, aVec1.w());

  NCollection_Vec4<float> aVec2(1.0f, 2.0f, 3.0f, 4.0f);
  EXPECT_EQ(1.0f, aVec2.x());
  EXPECT_EQ(2.0f, aVec2.y());
  EXPECT_EQ(3.0f, aVec2.z());
  EXPECT_EQ(4.0f, aVec2.w());
}

TEST_F(NCollection_Vec4Test, XyzMethod)
{
  NCollection_Vec4<float> aVec(2.0f, 3.0f, 4.0f, 5.0f);
  NCollection_Vec3<float> aVec3 = aVec.xyz();

  EXPECT_EQ(2.0f, aVec3.x());
  EXPECT_EQ(3.0f, aVec3.y());
  EXPECT_EQ(4.0f, aVec3.z());
}

TEST_F(NCollection_Vec4Test, MatrixMultiplicationAndTransformation)
{

  NCollection_Mat4<float> aMatrix;
  aMatrix.Translate(NCollection_Vec3<float>(4.0f, 3.0f, 1.0f));

  NCollection_Vec4<float> aPoints1[8];
  for (int aX = 0; aX < 2; ++aX)
  {
    for (int aY = 0; aY < 2; ++aY)
    {
      for (int aZ = 0; aZ < 2; ++aZ)
      {
        aPoints1[aX * 2 * 2 + aY * 2 + aZ] = NCollection_Vec4<float>(-1.0f + 2.0f * float(aX),
                                                                     -1.0f + 2.0f * float(aY),
                                                                     -1.0f + 2.0f * float(aZ),
                                                                     1.0f);
      }
    }
  }

  NCollection_Vec3<float> aPoints2[8];
  for (int aPntIdx = 0; aPntIdx < 8; ++aPntIdx)
  {
    aPoints1[aPntIdx] = aMatrix * aPoints1[aPntIdx];
    aPoints2[aPntIdx] = aPoints1[aPntIdx].xyz() / aPoints1[aPntIdx].w();
  }

  float aSquareModulus = aPoints2[7].SquareModulus();
  EXPECT_NEAR(45.0f, aSquareModulus, 0.001f);

  float aExpectedSquareMod0 = 3.0f * 3.0f + 2.0f * 2.0f + 0.0f * 0.0f;
  EXPECT_NEAR(aExpectedSquareMod0, aPoints2[0].SquareModulus(), 0.001f);
}

TEST_F(NCollection_Vec4Test, ComponentAccess)
{
  NCollection_Vec4<float> aVec(1.5f, 2.5f, 3.5f, 4.5f);

  EXPECT_EQ(1.5f, aVec.x());
  EXPECT_EQ(2.5f, aVec.y());
  EXPECT_EQ(3.5f, aVec.z());
  EXPECT_EQ(4.5f, aVec.w());

  aVec.x() = 10.0f;
  aVec.y() = 20.0f;
  aVec.z() = 30.0f;
  aVec.w() = 40.0f;

  EXPECT_EQ(10.0f, aVec.x());
  EXPECT_EQ(20.0f, aVec.y());
  EXPECT_EQ(30.0f, aVec.z());
  EXPECT_EQ(40.0f, aVec.w());
}

TEST_F(NCollection_Vec4Test, HomogeneousCoordinateDivision)
{

  NCollection_Vec4<float> aVec(8.0f, 12.0f, 16.0f, 4.0f);
  NCollection_Vec3<float> aResult = aVec.xyz() / aVec.w();

  EXPECT_EQ(2.0f, aResult.x());
  EXPECT_EQ(3.0f, aResult.y());
  EXPECT_EQ(4.0f, aResult.z());
}
