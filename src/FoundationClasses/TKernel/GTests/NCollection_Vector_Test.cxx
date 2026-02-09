

#include <NCollection_BaseAllocator.hpp>
#include <NCollection_Vector.hpp>
#include <Standard_Integer.hpp>

#include <gtest/gtest.h>
#include <algorithm>
#include <random>
#include <vector>

TEST(NCollection_VectorTest, DefaultConstructor)
{

  NCollection_Vector<int> aVector;

  EXPECT_EQ(0, aVector.Length());
  EXPECT_TRUE(aVector.IsEmpty());
}

TEST(NCollection_VectorTest, ResizeConstructor)
{

  const int               initialSize  = 10;
  const int               initialValue = 42;
  NCollection_Vector<int> aVector(initialSize);

  for (int i = 0; i < initialSize; i++)
  {
    aVector.SetValue(i, initialValue);
  }

  EXPECT_EQ(initialSize, aVector.Length());
  EXPECT_FALSE(aVector.IsEmpty());

  for (int i = 0; i < initialSize; i++)
  {
    EXPECT_EQ(initialValue, aVector(i));
  }
}

TEST(NCollection_VectorTest, Append)
{
  NCollection_Vector<int> aVector;

  aVector.Append(10);
  aVector.Append(20);
  aVector.Append(30);

  EXPECT_EQ(3, aVector.Length());
  EXPECT_EQ(10, aVector(0));
  EXPECT_EQ(20, aVector(1));
  EXPECT_EQ(30, aVector(2));
}

TEST(NCollection_VectorTest, SetValue)
{
  NCollection_Vector<int> aVector(5, nullptr);

  aVector.SetValue(2, 42);

  EXPECT_EQ(42, aVector(2));
  EXPECT_EQ(0, aVector(0));
  EXPECT_EQ(0, aVector(1));

  aVector(3) = 99;
  EXPECT_EQ(99, aVector(3));
}

TEST(NCollection_VectorTest, Value)
{
  NCollection_Vector<int> aVector;
  aVector.Append(10);
  aVector.Append(20);

  EXPECT_EQ(10, aVector.Value(0));
  EXPECT_EQ(20, aVector.Value(1));

  EXPECT_EQ(aVector.Value(0), aVector(0));
  EXPECT_EQ(aVector.Value(1), aVector(1));
}

TEST(NCollection_VectorTest, ChangeValue)
{
  NCollection_Vector<int> aVector;
  aVector.Append(10);
  aVector.Append(20);

  aVector.ChangeValue(1) = 25;
  EXPECT_EQ(25, aVector(1));

  aVector(0) = 15;
  EXPECT_EQ(15, aVector(0));
}

TEST(NCollection_VectorTest, FirstLast)
{
  NCollection_Vector<int> aVector;
  aVector.Append(10);
  aVector.Append(20);
  aVector.Append(30);

  EXPECT_EQ(10, aVector.First());
  EXPECT_EQ(30, aVector.Last());

  aVector.ChangeFirst() = 15;
  aVector.ChangeLast()  = 35;

  EXPECT_EQ(15, aVector.First());
  EXPECT_EQ(35, aVector.Last());
}

TEST(NCollection_VectorTest, CopyConstructor)
{
  NCollection_Vector<int> aVector1;
  aVector1.Append(10);
  aVector1.Append(20);
  aVector1.Append(30);

  NCollection_Vector<int> aVector2(aVector1);

  EXPECT_EQ(aVector1.Length(), aVector2.Length());

  for (int i = 0; i < aVector1.Length(); i++)
  {
    EXPECT_EQ(aVector1(i), aVector2(i));
  }

  aVector1(1) = 25;
  EXPECT_EQ(20, aVector2(1));
}

TEST(NCollection_VectorTest, AssignmentOperator)
{
  NCollection_Vector<int> aVector1;
  aVector1.Append(10);
  aVector1.Append(20);
  aVector1.Append(30);

  NCollection_Vector<int> aVector2;
  aVector2 = aVector1;

  EXPECT_EQ(aVector1.Length(), aVector2.Length());

  for (int i = 0; i < aVector1.Length(); i++)
  {
    EXPECT_EQ(aVector1(i), aVector2(i));
  }

  aVector1(1) = 25;
  EXPECT_EQ(20, aVector2(1));
}

TEST(NCollection_VectorTest, Clear)
{
  NCollection_Vector<int> aVector;
  aVector.Append(10);
  aVector.Append(20);

  aVector.Clear();

  EXPECT_EQ(0, aVector.Length());
  EXPECT_TRUE(aVector.IsEmpty());
}

TEST(NCollection_VectorTest, Iterator)
{
  NCollection_Vector<int> aVector;
  aVector.Append(10);
  aVector.Append(20);
  aVector.Append(30);

  int sum = 0;
  for (NCollection_Vector<int>::Iterator it(aVector); it.More(); it.Next())
  {
    sum += it.Value();
  }

  EXPECT_EQ(60, sum);

  for (NCollection_Vector<int>::Iterator it(aVector); it.More(); it.Next())
  {
    it.ChangeValue() *= 2;
  }

  EXPECT_EQ(20, aVector(0));
  EXPECT_EQ(40, aVector(1));
  EXPECT_EQ(60, aVector(2));
}

TEST(NCollection_VectorTest, STLIterators)
{
  NCollection_Vector<int> aVector;
  aVector.Append(10);
  aVector.Append(20);
  aVector.Append(30);

  int sum = 0;
  for (const auto& val : aVector)
  {
    sum += val;
  }

  EXPECT_EQ(60, sum);

  sum = 0;
  for (auto& val : aVector)
  {
    val *= 2;
    sum += val;
  }

  EXPECT_EQ(120, sum);

  EXPECT_EQ(20, aVector(0));
  EXPECT_EQ(40, aVector(1));
  EXPECT_EQ(60, aVector(2));
}

TEST(NCollection_VectorTest, Grow)
{
  NCollection_Vector<int> aVector;

  for (int i = 0; i < 1000; i++)
  {
    aVector.Append(i);
  }

  EXPECT_EQ(1000, aVector.Length());

  for (int i = 0; i < 1000; i++)
  {
    EXPECT_EQ(i, aVector(i));
  }
}

TEST(NCollection_VectorTest, Move)
{
  NCollection_Vector<int> aVector1;
  aVector1.Append(10);
  aVector1.Append(20);

  NCollection_Vector<int> aVector2 = std::move(aVector1);

  EXPECT_EQ(0, aVector1.Length());
  EXPECT_EQ(2, aVector2.Length());
  EXPECT_EQ(10, aVector2(0));
  EXPECT_EQ(20, aVector2(1));

  NCollection_Vector<int> aVector3;
  aVector3.Append(30);
  aVector3 = std::move(aVector2);

  EXPECT_EQ(0, aVector2.Length());
  EXPECT_EQ(2, aVector3.Length());
  EXPECT_EQ(10, aVector3(0));
  EXPECT_EQ(20, aVector3(1));
}

TEST(NCollection_VectorTest, EraseLast)
{
  NCollection_Vector<int> aVector;
  aVector.Append(10);
  aVector.Append(20);
  aVector.Append(30);

  EXPECT_EQ(3, aVector.Length());

  aVector.EraseLast();
  EXPECT_EQ(2, aVector.Length());
  EXPECT_EQ(10, aVector(0));
  EXPECT_EQ(20, aVector(1));

  aVector.EraseLast();
  EXPECT_EQ(1, aVector.Length());
  EXPECT_EQ(10, aVector(0));

  aVector.EraseLast();
  EXPECT_EQ(0, aVector.Length());
  EXPECT_TRUE(aVector.IsEmpty());

  aVector.EraseLast();
  EXPECT_EQ(0, aVector.Length());
}

TEST(NCollection_VectorTest, Appended)
{
  NCollection_Vector<int> aVector;

  int& ref1 = aVector.Appended();
  ref1      = 10;

  int& ref2 = aVector.Appended();
  ref2      = 20;

  EXPECT_EQ(2, aVector.Length());
  EXPECT_EQ(10, aVector(0));
  EXPECT_EQ(20, aVector(1));

  ref1 = 15;
  EXPECT_EQ(15, aVector(0));
}

TEST(NCollection_VectorTest, CustomAllocator)
{

  occ::handle<NCollection_BaseAllocator> anAlloc = NCollection_BaseAllocator::CommonBaseAllocator();
  NCollection_Vector<int>                aVector(256, anAlloc);

  aVector.Append(10);
  aVector.Append(20);
  aVector.Append(30);

  EXPECT_EQ(3, aVector.Length());
  EXPECT_EQ(10, aVector(0));
  EXPECT_EQ(20, aVector(1));
  EXPECT_EQ(30, aVector(2));

  aVector.Clear();
  EXPECT_EQ(0, aVector.Length());
}

TEST(NCollection_VectorTest, SetIncrement)
{
  NCollection_Vector<int> aVector;

  aVector.SetIncrement(512);

  for (int i = 0; i < 1000; i++)
  {
    aVector.Append(i);
  }

  EXPECT_EQ(1000, aVector.Length());

  for (int i = 0; i < 1000; i++)
  {
    EXPECT_EQ(i, aVector(i));
  }
}

TEST(NCollection_VectorTest, STLAlgorithmCompatibility_MinMax)
{
  NCollection_Vector<int> aVector;
  std::vector<int>        aStdVector;

  std::mt19937                       aGenerator(1);
  std::uniform_int_distribution<int> aDistribution(0, RAND_MAX);
  for (int anIdx = 0; anIdx < 100; ++anIdx)
  {
    int aVal = aDistribution(aGenerator);
    aVector.Append(aVal);
    aStdVector.push_back(aVal);
  }

  auto aMinOCCT = std::min_element(aVector.begin(), aVector.end());
  auto aMinStd  = std::min_element(aStdVector.begin(), aStdVector.end());

  auto aMaxOCCT = std::max_element(aVector.begin(), aVector.end());
  auto aMaxStd  = std::max_element(aStdVector.begin(), aStdVector.end());

  EXPECT_EQ(*aMinOCCT, *aMinStd);
  EXPECT_EQ(*aMaxOCCT, *aMaxStd);
}

TEST(NCollection_VectorTest, STLAlgorithmCompatibility_Replace)
{
  NCollection_Vector<int> aVector;
  std::vector<int>        aStdVector;

  std::mt19937                       aGenerator(1);
  std::uniform_int_distribution<int> aDistribution(0, RAND_MAX);
  for (int anIdx = 0; anIdx < 100; ++anIdx)
  {
    int aVal = aDistribution(aGenerator);
    aVector.Append(aVal);
    aStdVector.push_back(aVal);
  }

  int aTargetValue = aStdVector.back();
  int aNewValue    = -1;

  std::replace(aVector.begin(), aVector.end(), aTargetValue, aNewValue);
  std::replace(aStdVector.begin(), aStdVector.end(), aTargetValue, aNewValue);

  EXPECT_TRUE(std::equal(aVector.begin(), aVector.end(), aStdVector.begin()));
}

TEST(NCollection_VectorTest, STLAlgorithmCompatibility_Reverse)
{
  NCollection_Vector<int> aVector;
  std::vector<int>        aStdVector;

  for (int anIdx = 0; anIdx < 100; ++anIdx)
  {
    aVector.Append(anIdx);
    aStdVector.push_back(anIdx);
  }

  std::reverse(aVector.begin(), aVector.end());
  std::reverse(aStdVector.begin(), aStdVector.end());

  EXPECT_TRUE(std::equal(aVector.begin(), aVector.end(), aStdVector.begin()));
}

TEST(NCollection_VectorTest, STLAlgorithmCompatibility_Sort)
{
  NCollection_Vector<int> aVector;
  std::vector<int>        aStdVector;

  std::mt19937                       aGenerator(1);
  std::uniform_int_distribution<int> aDistribution(0, RAND_MAX);
  for (int anIdx = 0; anIdx < 100; ++anIdx)
  {
    int aVal = aDistribution(aGenerator);
    aVector.Append(aVal);
    aStdVector.push_back(aVal);
  }

  std::sort(aVector.begin(), aVector.end());
  std::sort(aStdVector.begin(), aStdVector.end());

  EXPECT_TRUE(std::equal(aVector.begin(), aVector.end(), aStdVector.begin()));
}
