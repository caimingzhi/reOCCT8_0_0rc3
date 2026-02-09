

#include <NCollection_List.hpp>
#include <NCollection_IncAllocator.hpp>
#include <Standard_Integer.hpp>

#include <gtest/gtest.h>
#include <algorithm>
#include <list>
#include <random>

class NCollection_ListTest : public testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(NCollection_ListTest, DefaultConstructor)
{

  NCollection_List<int> aList;
  EXPECT_TRUE(aList.IsEmpty());
  EXPECT_EQ(0, aList.Size());
  EXPECT_EQ(0, aList.Extent());
}

TEST_F(NCollection_ListTest, Append)
{
  NCollection_List<int> aList;

  EXPECT_EQ(10, aList.Append(10));
  EXPECT_EQ(20, aList.Append(20));
  EXPECT_EQ(30, aList.Append(30));

  EXPECT_FALSE(aList.IsEmpty());
  EXPECT_EQ(3, aList.Size());

  EXPECT_EQ(10, aList.First());
  EXPECT_EQ(30, aList.Last());
}

TEST_F(NCollection_ListTest, Prepend)
{
  NCollection_List<int> aList;

  EXPECT_EQ(30, aList.Prepend(30));
  EXPECT_EQ(20, aList.Prepend(20));
  EXPECT_EQ(10, aList.Prepend(10));

  EXPECT_FALSE(aList.IsEmpty());
  EXPECT_EQ(3, aList.Size());

  EXPECT_EQ(10, aList.First());
  EXPECT_EQ(30, aList.Last());
}

TEST_F(NCollection_ListTest, IteratorAccess)
{
  NCollection_List<int> aList;
  aList.Append(10);
  aList.Append(20);
  aList.Append(30);

  NCollection_List<int>::Iterator it(aList);
  int                             expectedValues[] = {10, 20, 30};
  int                             index            = 0;

  for (; it.More(); it.Next(), index++)
  {
    EXPECT_EQ(expectedValues[index], it.Value());
  }
  EXPECT_EQ(3, index);
}

TEST_F(NCollection_ListTest, STLIterators)
{
  NCollection_List<int> aList;
  aList.Append(10);
  aList.Append(20);
  aList.Append(30);

  int expectedValues[] = {10, 20, 30};
  int index            = 0;

  for (auto it = aList.begin(); it != aList.end(); ++it, ++index)
  {
    EXPECT_EQ(expectedValues[index], *it);
  }
  EXPECT_EQ(3, index);

  index = 0;
  for (const auto& value : aList)
  {
    EXPECT_EQ(expectedValues[index++], value);
  }
  EXPECT_EQ(3, index);
}

TEST_F(NCollection_ListTest, RemoveFirst)
{
  NCollection_List<int> aList;
  aList.Append(10);
  aList.Append(20);
  aList.Append(30);

  aList.RemoveFirst();
  EXPECT_EQ(2, aList.Size());
  EXPECT_EQ(20, aList.First());

  aList.RemoveFirst();
  EXPECT_EQ(1, aList.Size());
  EXPECT_EQ(30, aList.First());

  aList.RemoveFirst();
  EXPECT_TRUE(aList.IsEmpty());
}

TEST_F(NCollection_ListTest, Remove)
{
  NCollection_List<int> aList;
  aList.Append(10);
  aList.Append(20);
  aList.Append(30);

  NCollection_List<int>::Iterator it(aList);
  it.Next();
  aList.Remove(it);

  EXPECT_EQ(2, aList.Size());
  EXPECT_EQ(10, aList.First());
  EXPECT_EQ(30, aList.Last());
  EXPECT_EQ(30, it.Value());
}

TEST_F(NCollection_ListTest, RemoveByValue)
{
  NCollection_List<int> aList;
  aList.Append(10);
  aList.Append(20);
  aList.Append(10);
  aList.Append(30);

  bool removed = aList.Remove(10);
  EXPECT_TRUE(removed);
  EXPECT_EQ(3, aList.Size());
  EXPECT_EQ(20, aList.First());

  removed = aList.Remove(50);
  EXPECT_FALSE(removed);
  EXPECT_EQ(3, aList.Size());

  removed = aList.Remove(10);
  EXPECT_TRUE(removed);
  EXPECT_EQ(2, aList.Size());

  NCollection_List<int>::Iterator it(aList);
  EXPECT_EQ(20, it.Value());
  it.Next();
  EXPECT_EQ(30, it.Value());
}

TEST_F(NCollection_ListTest, Clear)
{
  NCollection_List<int> aList;
  aList.Append(10);
  aList.Append(20);
  aList.Append(30);

  aList.Clear();
  EXPECT_TRUE(aList.IsEmpty());
  EXPECT_EQ(0, aList.Size());
}

TEST_F(NCollection_ListTest, Assignment)
{
  NCollection_List<int> aList1;
  aList1.Append(10);
  aList1.Append(20);
  aList1.Append(30);

  NCollection_List<int> aList2;
  aList2 = aList1;

  EXPECT_EQ(aList1.Size(), aList2.Size());

  NCollection_List<int>::Iterator it1(aList1);
  NCollection_List<int>::Iterator it2(aList2);

  for (; it1.More() && it2.More(); it1.Next(), it2.Next())
  {
    EXPECT_EQ(it1.Value(), it2.Value());
  }

  aList1.First() = 100;
  EXPECT_EQ(100, aList1.First());
  EXPECT_EQ(10, aList2.First());
}

TEST_F(NCollection_ListTest, AssignMethod)
{
  NCollection_List<int> aList1;
  aList1.Append(10);
  aList1.Append(20);
  aList1.Append(30);

  NCollection_List<int> aList2;
  aList2.Append(40);
  aList2.Assign(aList1);

  EXPECT_EQ(aList1.Size(), aList2.Size());

  NCollection_List<int>::Iterator it2(aList2);
  EXPECT_EQ(10, it2.Value());
  it2.Next();
  EXPECT_EQ(20, it2.Value());
  it2.Next();
  EXPECT_EQ(30, it2.Value());
}

TEST_F(NCollection_ListTest, AppendList)
{
  NCollection_List<int> aList1;
  aList1.Append(10);
  aList1.Append(20);

  NCollection_List<int> aList2;
  aList2.Append(30);
  aList2.Append(40);

  aList1.Append(aList2);

  EXPECT_EQ(4, aList1.Size());
  EXPECT_TRUE(aList2.IsEmpty());

  NCollection_List<int>::Iterator it(aList1);
  EXPECT_EQ(10, it.Value());
  it.Next();
  EXPECT_EQ(20, it.Value());
  it.Next();
  EXPECT_EQ(30, it.Value());
  it.Next();
  EXPECT_EQ(40, it.Value());
}

TEST_F(NCollection_ListTest, PrependList)
{
  NCollection_List<int> aList1;
  aList1.Append(30);
  aList1.Append(40);

  NCollection_List<int> aList2;
  aList2.Append(10);
  aList2.Append(20);

  aList1.Prepend(aList2);

  EXPECT_EQ(4, aList1.Size());
  EXPECT_TRUE(aList2.IsEmpty());

  NCollection_List<int>::Iterator it(aList1);
  EXPECT_EQ(10, it.Value());
  it.Next();
  EXPECT_EQ(20, it.Value());
  it.Next();
  EXPECT_EQ(30, it.Value());
  it.Next();
  EXPECT_EQ(40, it.Value());
}

TEST_F(NCollection_ListTest, InsertBefore)
{
  NCollection_List<int> aList;
  aList.Append(10);
  aList.Append(30);

  NCollection_List<int>::Iterator it(aList);
  it.Next();

  EXPECT_EQ(20, aList.InsertBefore(20, it));

  EXPECT_EQ(3, aList.Size());

  NCollection_List<int>::Iterator checkIt(aList);
  EXPECT_EQ(10, checkIt.Value());
  checkIt.Next();
  EXPECT_EQ(20, checkIt.Value());
  checkIt.Next();
  EXPECT_EQ(30, checkIt.Value());
}

TEST_F(NCollection_ListTest, InsertAfter)
{
  NCollection_List<int> aList;
  aList.Append(10);
  aList.Append(30);

  NCollection_List<int>::Iterator it(aList);

  EXPECT_EQ(20, aList.InsertAfter(20, it));

  EXPECT_EQ(3, aList.Size());

  NCollection_List<int>::Iterator checkIt(aList);
  EXPECT_EQ(10, checkIt.Value());
  checkIt.Next();
  EXPECT_EQ(20, checkIt.Value());
  checkIt.Next();
  EXPECT_EQ(30, checkIt.Value());
}

TEST_F(NCollection_ListTest, InsertList)
{
  NCollection_List<int> aList1;
  aList1.Append(10);
  aList1.Append(40);

  NCollection_List<int> aList2;
  aList2.Append(20);
  aList2.Append(30);

  NCollection_List<int>::Iterator it(aList1);
  it.Next();

  aList1.InsertBefore(aList2, it);

  EXPECT_EQ(4, aList1.Size());
  EXPECT_TRUE(aList2.IsEmpty());

  NCollection_List<int>::Iterator checkIt(aList1);
  EXPECT_EQ(10, checkIt.Value());
  checkIt.Next();
  EXPECT_EQ(20, checkIt.Value());
  checkIt.Next();
  EXPECT_EQ(30, checkIt.Value());
  checkIt.Next();
  EXPECT_EQ(40, checkIt.Value());
}

TEST_F(NCollection_ListTest, Reverse)
{
  NCollection_List<int> aList;
  aList.Append(10);
  aList.Append(20);
  aList.Append(30);

  aList.Reverse();

  EXPECT_EQ(30, aList.First());
  EXPECT_EQ(10, aList.Last());

  NCollection_List<int>::Iterator it(aList);
  EXPECT_EQ(30, it.Value());
  it.Next();
  EXPECT_EQ(20, it.Value());
  it.Next();
  EXPECT_EQ(10, it.Value());
}

TEST_F(NCollection_ListTest, STLAlgorithmCompatibility_MinMax)
{
  NCollection_List<int> aList;
  std::list<int>        aStdList;

  std::mt19937                       aGenerator(1);
  std::uniform_int_distribution<int> aDistribution(0, RAND_MAX);
  for (int anIdx = 0; anIdx < 100; ++anIdx)
  {
    int aVal = aDistribution(aGenerator);
    aList.Append(aVal);
    aStdList.push_back(aVal);
  }

  auto aMinOCCT = std::min_element(aList.begin(), aList.end());
  auto aMinStd  = std::min_element(aStdList.begin(), aStdList.end());

  auto aMaxOCCT = std::max_element(aList.begin(), aList.end());
  auto aMaxStd  = std::max_element(aStdList.begin(), aStdList.end());

  EXPECT_EQ(*aMinOCCT, *aMinStd);
  EXPECT_EQ(*aMaxOCCT, *aMaxStd);
}

TEST_F(NCollection_ListTest, STLAlgorithmCompatibility_Replace)
{
  NCollection_List<int> aList;
  std::list<int>        aStdList;

  std::mt19937                       aGenerator(1);
  std::uniform_int_distribution<int> aDistribution(0, RAND_MAX);
  for (int anIdx = 0; anIdx < 100; ++anIdx)
  {
    int aVal = aDistribution(aGenerator);
    aList.Append(aVal);
    aStdList.push_back(aVal);
  }

  int aTargetValue = aStdList.back();
  int aNewValue    = -1;

  std::replace(aList.begin(), aList.end(), aTargetValue, aNewValue);
  std::replace(aStdList.begin(), aStdList.end(), aTargetValue, aNewValue);

  EXPECT_TRUE(std::equal(aList.begin(), aList.end(), aStdList.begin()));
}

TEST_F(NCollection_ListTest, OCC25348_AssignDoesNotChangeAllocator)
{

  occ::handle<NCollection_IncAllocator> anAlloc1 = new NCollection_IncAllocator();
  NCollection_List<int>                 aList1(anAlloc1);

  for (int i = 0; i < 10; i++)
  {
    occ::handle<NCollection_IncAllocator> anAlloc2 = new NCollection_IncAllocator();
    NCollection_List<int>                 aList2(anAlloc2);
    aList2.Append(i);

    occ::handle<NCollection_BaseAllocator> anAllocBefore = aList1.Allocator();

    aList1.Assign(aList2);

    occ::handle<NCollection_BaseAllocator> anAllocAfter = aList1.Allocator();
    EXPECT_EQ(anAllocBefore, anAllocAfter) << "Assign() should not change the target's allocator";

    EXPECT_EQ(1, aList1.Size());
    EXPECT_EQ(i, aList1.First());
  }
}
