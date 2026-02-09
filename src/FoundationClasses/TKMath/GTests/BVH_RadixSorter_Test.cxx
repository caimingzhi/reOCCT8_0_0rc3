

#include <gtest/gtest.h>

#include <BVH_RadixSorter.hpp>

TEST(BVH_RadixSorterTest, EncodeMortonCode_Origin)
{
  unsigned int aCode = BVH::EncodeMortonCode(0, 0, 0);
  EXPECT_EQ(aCode, 0u);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_SingleBits)
{

  unsigned int aCodeX = BVH::EncodeMortonCode(1, 0, 0);
  EXPECT_EQ(aCodeX, 1u);

  unsigned int aCodeY = BVH::EncodeMortonCode(0, 1, 0);
  EXPECT_EQ(aCodeY, 2u);

  unsigned int aCodeZ = BVH::EncodeMortonCode(0, 0, 1);
  EXPECT_EQ(aCodeZ, 4u);

  unsigned int aCodeXYZ = BVH::EncodeMortonCode(1, 1, 1);
  EXPECT_EQ(aCodeXYZ, 7u);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_Interleaving)
{

  unsigned int aCode1 = BVH::EncodeMortonCode(2, 0, 0);
  EXPECT_EQ(aCode1, 8u);

  unsigned int aCode2 = BVH::EncodeMortonCode(0, 2, 0);
  EXPECT_EQ(aCode2, 16u);

  unsigned int aCode3 = BVH::EncodeMortonCode(0, 0, 2);
  EXPECT_EQ(aCode3, 32u);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_MaxValues)
{

  unsigned int aCode = BVH::EncodeMortonCode(1023, 1023, 1023);

  EXPECT_EQ(aCode, 0x3FFFFFFFu);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_Symmetry)
{

  unsigned int aCode1 = BVH::EncodeMortonCode(100, 200, 300);
  unsigned int aCode2 = BVH::EncodeMortonCode(200, 100, 300);
  unsigned int aCode3 = BVH::EncodeMortonCode(100, 300, 200);

  EXPECT_NE(aCode1, aCode2);
  EXPECT_NE(aCode1, aCode3);
  EXPECT_NE(aCode2, aCode3);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_Ordering)
{

  unsigned int aCode000    = BVH::EncodeMortonCode(0, 0, 0);
  unsigned int aCode100    = BVH::EncodeMortonCode(1, 0, 0);
  unsigned int aCode001023 = BVH::EncodeMortonCode(0, 0, 1023);

  unsigned int aDiff1 = aCode100 - aCode000;

  unsigned int aDiff2 = aCode001023 - aCode000;

  EXPECT_LT(aDiff1, aDiff2);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_MidValues)
{

  unsigned int aCode = BVH::EncodeMortonCode(512, 512, 512);

  EXPECT_GT(aCode, 0u);
  EXPECT_LE(aCode, 0x3FFFFFFFu);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_PowersOfTwo)
{

  unsigned int aCode4  = BVH::EncodeMortonCode(4, 0, 0);
  unsigned int aCode8  = BVH::EncodeMortonCode(8, 0, 0);
  unsigned int aCode16 = BVH::EncodeMortonCode(16, 0, 0);

  EXPECT_EQ(aCode8, aCode4 * 8);
  EXPECT_EQ(aCode16, aCode8 * 8);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_ConsistentEncoding)
{

  for (int i = 0; i < 100; ++i)
  {
    unsigned int aCode1 = BVH::EncodeMortonCode(100, 200, 300);
    unsigned int aCode2 = BVH::EncodeMortonCode(100, 200, 300);
    EXPECT_EQ(aCode1, aCode2);
  }
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_BoundaryValues)
{

  unsigned int aCode1022 = BVH::EncodeMortonCode(1022, 1022, 1022);
  unsigned int aCode1023 = BVH::EncodeMortonCode(1023, 1023, 1023);

  EXPECT_LT(aCode1022, aCode1023);
  EXPECT_EQ(aCode1023, 0x3FFFFFFFu);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_SmallValues)
{

  unsigned int aCode2 = BVH::EncodeMortonCode(2, 2, 2);
  unsigned int aCode3 = BVH::EncodeMortonCode(3, 3, 3);

  EXPECT_LT(aCode2, 100u);
  EXPECT_LT(aCode3, 100u);
  EXPECT_LT(aCode2, aCode3);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_SingleAxisValues)
{

  unsigned int aCodeX = BVH::EncodeMortonCode(255, 0, 0);
  unsigned int aCodeY = BVH::EncodeMortonCode(0, 255, 0);
  unsigned int aCodeZ = BVH::EncodeMortonCode(0, 0, 255);

  EXPECT_NE(aCodeX, aCodeY);
  EXPECT_NE(aCodeY, aCodeZ);
  EXPECT_NE(aCodeX, aCodeZ);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_SequentialXValues)
{

  unsigned int aPrev = BVH::EncodeMortonCode(0, 500, 500);
  for (unsigned int x = 1; x <= 10; ++x)
  {
    unsigned int aCurr = BVH::EncodeMortonCode(x, 500, 500);
    EXPECT_GT(aCurr, aPrev);
    aPrev = aCurr;
  }
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_SequentialYValues)
{

  unsigned int aPrev = BVH::EncodeMortonCode(500, 0, 500);
  for (unsigned int y = 1; y <= 10; ++y)
  {
    unsigned int aCurr = BVH::EncodeMortonCode(500, y, 500);
    EXPECT_GT(aCurr, aPrev);
    aPrev = aCurr;
  }
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_SequentialZValues)
{

  unsigned int aPrev = BVH::EncodeMortonCode(500, 500, 0);
  for (unsigned int z = 1; z <= 10; ++z)
  {
    unsigned int aCurr = BVH::EncodeMortonCode(500, 500, z);
    EXPECT_GT(aCurr, aPrev);
    aPrev = aCurr;
  }
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_ZeroInDimensions)
{

  unsigned int aCodeXY = BVH::EncodeMortonCode(100, 100, 0);
  unsigned int aCodeXZ = BVH::EncodeMortonCode(100, 0, 100);
  unsigned int aCodeYZ = BVH::EncodeMortonCode(0, 100, 100);

  EXPECT_NE(aCodeXY, aCodeXZ);
  EXPECT_NE(aCodeXY, aCodeYZ);
  EXPECT_NE(aCodeXZ, aCodeYZ);

  EXPECT_GT(aCodeXY, 0u);
  EXPECT_GT(aCodeXZ, 0u);
  EXPECT_GT(aCodeYZ, 0u);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_UpperByteBits)
{

  unsigned int aCode256 = BVH::EncodeMortonCode(256, 0, 0);
  unsigned int aCode512 = BVH::EncodeMortonCode(512, 0, 0);
  unsigned int aCode768 = BVH::EncodeMortonCode(768, 0, 0);

  EXPECT_GT(aCode256, 0u);
  EXPECT_GT(aCode512, aCode256);
  EXPECT_GT(aCode768, aCode512);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_AllOnes)
{

  unsigned int aCode = BVH::EncodeMortonCode(255, 255, 255);

  EXPECT_LT(aCode, 0x3FFFFFFFu);
  EXPECT_GT(aCode, 0u);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_LocalityPreservation)
{

  unsigned int aCenter = BVH::EncodeMortonCode(512, 512, 512);
  unsigned int aNear1  = BVH::EncodeMortonCode(513, 512, 512);
  unsigned int aNear2  = BVH::EncodeMortonCode(512, 513, 512);
  unsigned int aFar    = BVH::EncodeMortonCode(0, 0, 0);

  unsigned int aDiffNear1 = (aNear1 > aCenter) ? (aNear1 - aCenter) : (aCenter - aNear1);
  unsigned int aDiffNear2 = (aNear2 > aCenter) ? (aNear2 - aCenter) : (aCenter - aNear2);
  unsigned int aDiffFar   = (aFar > aCenter) ? (aFar - aCenter) : (aCenter - aFar);

  EXPECT_LT(aDiffNear1, aDiffFar);
  EXPECT_LT(aDiffNear2, aDiffFar);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_BitPattern3)
{

  unsigned int aCode = BVH::EncodeMortonCode(3, 0, 0);
  EXPECT_EQ(aCode, 9u);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_BitPattern7)
{

  unsigned int aCode = BVH::EncodeMortonCode(7, 0, 0);
  EXPECT_EQ(aCode, 73u);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_XYEqual)
{

  unsigned int aCode1 = BVH::EncodeMortonCode(1, 1, 0);
  unsigned int aCode2 = BVH::EncodeMortonCode(2, 2, 0);
  unsigned int aCode3 = BVH::EncodeMortonCode(4, 4, 0);

  EXPECT_EQ(aCode1, 3u);

  EXPECT_EQ(aCode2, 24u);

  EXPECT_EQ(aCode3, 192u);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_AllAxesEqual)
{

  unsigned int aCode1 = BVH::EncodeMortonCode(1, 1, 1);
  unsigned int aCode2 = BVH::EncodeMortonCode(2, 2, 2);

  EXPECT_EQ(aCode1, 7u);

  EXPECT_EQ(aCode2, 56u);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_HalfMax)
{

  unsigned int aCode = BVH::EncodeMortonCode(512, 512, 512);

  EXPECT_GT(aCode, 0x1FFFFFFFu);
  EXPECT_LE(aCode, 0x3FFFFFFFu);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_QuarterMax)
{

  unsigned int aCode = BVH::EncodeMortonCode(256, 256, 256);

  EXPECT_GT(aCode, 0u);
  EXPECT_LT(aCode, 0x3FFFFFFFu);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_DifferentScales)
{

  unsigned int aCode1 = BVH::EncodeMortonCode(100, 100, 100);
  unsigned int aCode2 = BVH::EncodeMortonCode(200, 200, 200);

  EXPECT_GT(aCode2, aCode1);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_AdjacentCells)
{

  unsigned int aCode1 = BVH::EncodeMortonCode(100, 100, 100);
  unsigned int aCode2 = BVH::EncodeMortonCode(101, 100, 100);

  EXPECT_EQ(aCode2 - aCode1, 1u);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_AdjacentCellsY)
{

  unsigned int aCode1 = BVH::EncodeMortonCode(100, 100, 100);
  unsigned int aCode2 = BVH::EncodeMortonCode(100, 101, 100);

  EXPECT_EQ(aCode2 - aCode1, 2u);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_AdjacentCellsZ)
{

  unsigned int aCode1 = BVH::EncodeMortonCode(100, 100, 100);
  unsigned int aCode2 = BVH::EncodeMortonCode(100, 100, 101);

  EXPECT_EQ(aCode2 - aCode1, 4u);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_MonotonicX)
{

  unsigned int aPrev = 0;
  for (unsigned int x = 0; x < 100; ++x)
  {
    unsigned int aCode = BVH::EncodeMortonCode(x, 0, 0);
    EXPECT_GE(aCode, aPrev);
    aPrev = aCode;
  }
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_MonotonicY)
{

  unsigned int aPrev = 0;
  for (unsigned int y = 0; y < 100; ++y)
  {
    unsigned int aCode = BVH::EncodeMortonCode(0, y, 0);
    EXPECT_GE(aCode, aPrev);
    aPrev = aCode;
  }
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_MonotonicZ)
{

  unsigned int aPrev = 0;
  for (unsigned int z = 0; z < 100; ++z)
  {
    unsigned int aCode = BVH::EncodeMortonCode(0, 0, z);
    EXPECT_GE(aCode, aPrev);
    aPrev = aCode;
  }
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_NoOverflow)
{

  unsigned int aCode = BVH::EncodeMortonCode(1023, 1023, 1023);

  EXPECT_EQ(aCode & 0xC0000000u, 0u);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_UniqueForDifferentInputs)
{

  unsigned int aCode1 = BVH::EncodeMortonCode(100, 200, 300);
  unsigned int aCode2 = BVH::EncodeMortonCode(100, 200, 301);
  unsigned int aCode3 = BVH::EncodeMortonCode(100, 201, 300);
  unsigned int aCode4 = BVH::EncodeMortonCode(101, 200, 300);

  EXPECT_NE(aCode1, aCode2);
  EXPECT_NE(aCode1, aCode3);
  EXPECT_NE(aCode1, aCode4);
  EXPECT_NE(aCode2, aCode3);
  EXPECT_NE(aCode2, aCode4);
  EXPECT_NE(aCode3, aCode4);
}

TEST(BVH_RadixSorterTest, EncodeMortonCode_SpecificPattern)
{

  unsigned int aCode = BVH::EncodeMortonCode(5, 3, 6);

  EXPECT_GT(aCode, 0u);
  EXPECT_LE(aCode, 0x3FFFFFFFu);

  unsigned int aCode2 = BVH::EncodeMortonCode(5, 3, 6);
  EXPECT_EQ(aCode, aCode2);
}
