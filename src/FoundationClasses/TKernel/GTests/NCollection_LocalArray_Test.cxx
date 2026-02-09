

#include <NCollection_LocalArray.hpp>

#include <gtest/gtest.h>

TEST(NCollection_LocalArrayTest, DefaultConstructor)
{
  NCollection_LocalArray<int> array;
  EXPECT_EQ(0, array.Size());
}

TEST(NCollection_LocalArrayTest, ConstructorWithSize)
{
  const size_t                size = 100;
  NCollection_LocalArray<int> array(size);
  EXPECT_EQ(size, array.Size());
}

TEST(NCollection_LocalArrayTest, SmallSizeAllocation)
{
  const size_t                      size = 10;
  NCollection_LocalArray<int, 1024> array(size);
  EXPECT_EQ(size, array.Size());

  for (size_t i = 0; i < size; ++i)
  {
    array[i] = static_cast<int>(i * 10);
  }

  for (size_t i = 0; i < size; ++i)
  {
    EXPECT_EQ(static_cast<int>(i * 10), array[i]);
  }
}

TEST(NCollection_LocalArrayTest, LargeSizeAllocation)
{
  const size_t                size = 2000;
  NCollection_LocalArray<int> array(size);
  EXPECT_EQ(size, array.Size());

  for (size_t i = 0; i < size; ++i)
  {
    array[i] = static_cast<int>(i * 10);
  }

  for (size_t i = 0; i < size; ++i)
  {
    EXPECT_EQ(static_cast<int>(i * 10), array[i]);
  }
}

TEST(NCollection_LocalArrayTest, Reallocation)
{
  NCollection_LocalArray<int> array(10);
  EXPECT_EQ(10, array.Size());

  for (size_t i = 0; i < 10; ++i)
  {
    array[i] = static_cast<int>(i);
  }

  array.Allocate(50);
  EXPECT_EQ(50, array.Size());

  for (size_t i = 0; i < 50; ++i)
  {
    array[i] = static_cast<int>(i * 2);
  }

  for (size_t i = 0; i < 50; ++i)
  {
    EXPECT_EQ(static_cast<int>(i * 2), array[i]);
  }

  array.Allocate(5);
  EXPECT_EQ(5, array.Size());

  for (size_t i = 0; i < 5; ++i)
  {
    EXPECT_EQ(static_cast<int>(i * 2), array[i]);
  }
}

TEST(NCollection_LocalArrayTest, CustomMaxArraySize)
{
  const size_t customMaxSize = 50;

  NCollection_LocalArray<int, customMaxSize> smallArray(20);
  EXPECT_EQ(20, smallArray.Size());

  NCollection_LocalArray<int, customMaxSize> largeArray(100);
  EXPECT_EQ(100, largeArray.Size());
}

struct NCollection_LocalArray_TestStruct
{
  int    a;
  double b;

  bool operator==(const NCollection_LocalArray_TestStruct& other) const
  {
    return a == other.a && b == other.b;
  }
};

TEST(NCollection_LocalArrayTest, CustomType)
{
  NCollection_LocalArray<NCollection_LocalArray_TestStruct> array(5);
  EXPECT_EQ(5, array.Size());

  NCollection_LocalArray_TestStruct ts{10, 3.14};

  array[0] = ts;
  EXPECT_TRUE(ts == array[0]);
}

TEST(NCollection_LocalArrayTest, TransitionStackToHeap)
{
  const int                            maxSize = 10;
  NCollection_LocalArray<int, maxSize> array;

  array.Allocate(5);
  for (size_t i = 0; i < 5; ++i)
  {
    array[i] = static_cast<int>(i);
  }

  for (size_t i = 0; i < 5; ++i)
  {
    EXPECT_EQ(static_cast<int>(i), array[i]);
  }

  array.Allocate(maxSize + 10);
  for (size_t i = 0; i < maxSize + 10; ++i)
  {
    array[i] = static_cast<int>(i * 3);
  }

  for (size_t i = 0; i < maxSize + 10; ++i)
  {
    EXPECT_EQ(static_cast<int>(i * 3), array[i]);
  }

  array.Allocate(maxSize - 5);
  for (size_t i = 0; i < maxSize - 5; ++i)
  {
    array[i] = static_cast<int>(i * 5);
  }

  for (size_t i = 0; i < maxSize - 5; ++i)
  {
    EXPECT_EQ(static_cast<int>(i * 5), array[i]);
  }
}
