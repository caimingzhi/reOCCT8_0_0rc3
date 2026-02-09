

#include <NCollection_Sequence.hpp>
#include <NCollection_IncAllocator.hpp>
#include <NCollection_BaseAllocator.hpp>

#include <gtest/gtest.h>
#include <algorithm>
#include <list>
#include <random>

typedef int ItemType;

class TestClass
{
public:
  TestClass(int id = 0, const char* name = "")
      : myId(id),
        myName(name)
  {
  }

  int GetId() const { return myId; }

  const char* GetName() const { return myName.c_str(); }

  bool operator==(const TestClass& other) const
  {
    return (myId == other.myId && myName == other.myName);
  }

private:
  int         myId;
  std::string myName;
};

TEST(NCollection_SequenceTest, BasicFunctions)
{

  NCollection_Sequence<ItemType> aSeq;
  EXPECT_TRUE(aSeq.IsEmpty());
  EXPECT_EQ(aSeq.Size(), 0);
  EXPECT_EQ(aSeq.Length(), 0);

  aSeq.Append(10);
  aSeq.Append(20);
  aSeq.Append(30);
  EXPECT_EQ(aSeq.Size(), 3);
  EXPECT_FALSE(aSeq.IsEmpty());

  EXPECT_EQ(aSeq(1), 10);
  EXPECT_EQ(aSeq(2), 20);
  EXPECT_EQ(aSeq(3), 30);
  EXPECT_EQ(aSeq.First(), 10);
  EXPECT_EQ(aSeq.Last(), 30);

  EXPECT_EQ(aSeq.Lower(), 1);
  EXPECT_EQ(aSeq.Upper(), 3);
}

TEST(NCollection_SequenceTest, ModifyingOperations)
{
  NCollection_Sequence<ItemType> aSeq;

  aSeq.Prepend(100);
  aSeq.Prepend(200);
  EXPECT_EQ(aSeq.Size(), 2);
  EXPECT_EQ(aSeq.First(), 200);
  EXPECT_EQ(aSeq.Last(), 100);

  aSeq.SetValue(1, 210);
  EXPECT_EQ(aSeq(1), 210);

  aSeq.ChangeValue(2) = 110;
  EXPECT_EQ(aSeq(2), 110);

  aSeq.InsertBefore(1, 300);
  EXPECT_EQ(aSeq.Size(), 3);
  EXPECT_EQ(aSeq(1), 300);
  EXPECT_EQ(aSeq(2), 210);
  EXPECT_EQ(aSeq(3), 110);

  aSeq.InsertAfter(2, 400);
  EXPECT_EQ(aSeq.Size(), 4);
  EXPECT_EQ(aSeq(1), 300);
  EXPECT_EQ(aSeq(2), 210);
  EXPECT_EQ(aSeq(3), 400);
  EXPECT_EQ(aSeq(4), 110);

  aSeq.Remove(3);
  EXPECT_EQ(aSeq.Size(), 3);
  EXPECT_EQ(aSeq(1), 300);
  EXPECT_EQ(aSeq(2), 210);
  EXPECT_EQ(aSeq(3), 110);

  aSeq.Append(500);
  aSeq.Append(600);
  EXPECT_EQ(aSeq.Size(), 5);

  aSeq.Remove(2, 4);
  EXPECT_EQ(aSeq.Size(), 2);
  EXPECT_EQ(aSeq(1), 300);
  EXPECT_EQ(aSeq(2), 600);
}

TEST(NCollection_SequenceTest, IteratorFunctions)
{
  NCollection_Sequence<ItemType> aSeq;
  aSeq.Append(10);
  aSeq.Append(20);
  aSeq.Append(30);

  NCollection_Sequence<ItemType>::Iterator anIt(aSeq);

  EXPECT_TRUE(anIt.More());
  EXPECT_EQ(anIt.Value(), 10);
  anIt.Next();

  EXPECT_TRUE(anIt.More());
  EXPECT_EQ(anIt.Value(), 20);
  anIt.Next();

  EXPECT_TRUE(anIt.More());
  EXPECT_EQ(anIt.Value(), 30);
  anIt.Next();

  EXPECT_FALSE(anIt.More());

  NCollection_Sequence<ItemType>::Iterator aModIt(aSeq);
  aModIt.ChangeValue() = 15;
  aModIt.Next();
  aModIt.ChangeValue() = 25;

  EXPECT_EQ(aSeq(1), 15);
  EXPECT_EQ(aSeq(2), 25);
  EXPECT_EQ(aSeq(3), 30);

  int index            = 0;
  int expectedValues[] = {15, 25, 30};
  for (const auto& item : aSeq)
  {
    EXPECT_EQ(item, expectedValues[index++]);
  }
  EXPECT_EQ(index, 3);
}

TEST(NCollection_SequenceTest, CopyAndAssignment)
{
  NCollection_Sequence<ItemType> aSeq1;
  aSeq1.Append(10);
  aSeq1.Append(20);
  aSeq1.Append(30);

  NCollection_Sequence<ItemType> aSeq2(aSeq1);
  EXPECT_EQ(aSeq2.Size(), 3);
  EXPECT_EQ(aSeq2(1), 10);
  EXPECT_EQ(aSeq2(2), 20);
  EXPECT_EQ(aSeq2(3), 30);

  NCollection_Sequence<ItemType> aSeq3;
  aSeq3 = aSeq1;
  EXPECT_EQ(aSeq3.Size(), 3);
  EXPECT_EQ(aSeq3(1), 10);
  EXPECT_EQ(aSeq3(2), 20);
  EXPECT_EQ(aSeq3(3), 30);

  aSeq1.SetValue(2, 25);
  EXPECT_EQ(aSeq1(2), 25);
  EXPECT_EQ(aSeq2(2), 20);
  EXPECT_EQ(aSeq3(2), 20);
}

TEST(NCollection_SequenceTest, CombiningSequences)
{
  NCollection_Sequence<ItemType> aSeq1;
  aSeq1.Append(10);
  aSeq1.Append(20);

  NCollection_Sequence<ItemType> aSeq2;
  aSeq2.Append(30);
  aSeq2.Append(40);

  NCollection_Sequence<ItemType> aSeq3(aSeq1);
  aSeq3.Append(aSeq2);
  EXPECT_EQ(aSeq3.Size(), 4);
  EXPECT_EQ(aSeq3(1), 10);
  EXPECT_EQ(aSeq3(2), 20);
  EXPECT_EQ(aSeq3(3), 30);
  EXPECT_EQ(aSeq3(4), 40);
  EXPECT_TRUE(aSeq2.IsEmpty());

  aSeq2.Append(50);
  aSeq2.Append(60);

  NCollection_Sequence<ItemType> aSeq4;
  aSeq4.Append(70);
  aSeq4.Prepend(aSeq2);

  EXPECT_EQ(aSeq4.Size(), 3);
  EXPECT_EQ(aSeq4(1), 50);
  EXPECT_EQ(aSeq4(2), 60);
  EXPECT_EQ(aSeq4(3), 70);
  EXPECT_TRUE(aSeq2.IsEmpty());

  aSeq2.Append(80);
  aSeq2.Append(90);

  NCollection_Sequence<ItemType> aSeq5;
  aSeq5.Append(100);
  aSeq5.Append(110);
  aSeq5.InsertAfter(1, aSeq2);

  EXPECT_EQ(aSeq5.Size(), 4);
  EXPECT_EQ(aSeq5(1), 100);
  EXPECT_EQ(aSeq5(2), 80);
  EXPECT_EQ(aSeq5(3), 90);
  EXPECT_EQ(aSeq5(4), 110);
  EXPECT_TRUE(aSeq2.IsEmpty());
}

TEST(NCollection_SequenceTest, AdvancedOperations)
{
  NCollection_Sequence<ItemType> aSeq;
  aSeq.Append(10);
  aSeq.Append(20);
  aSeq.Append(30);
  aSeq.Append(40);
  aSeq.Append(50);

  aSeq.Exchange(2, 4);
  EXPECT_EQ(aSeq(1), 10);
  EXPECT_EQ(aSeq(2), 40);
  EXPECT_EQ(aSeq(3), 30);
  EXPECT_EQ(aSeq(4), 20);
  EXPECT_EQ(aSeq(5), 50);

  aSeq.Reverse();
  EXPECT_EQ(aSeq(1), 50);
  EXPECT_EQ(aSeq(2), 20);
  EXPECT_EQ(aSeq(3), 30);
  EXPECT_EQ(aSeq(4), 40);
  EXPECT_EQ(aSeq(5), 10);

  NCollection_Sequence<ItemType> aSeq2;
  aSeq.Split(2, aSeq2);

  EXPECT_EQ(aSeq.Size(), 1);
  EXPECT_EQ(aSeq(1), 50);

  EXPECT_EQ(aSeq2.Size(), 4);
  EXPECT_EQ(aSeq2(1), 20);
  EXPECT_EQ(aSeq2(2), 30);
  EXPECT_EQ(aSeq2(3), 40);
  EXPECT_EQ(aSeq2(4), 10);

  aSeq.Clear();
  EXPECT_TRUE(aSeq.IsEmpty());
  EXPECT_EQ(aSeq.Size(), 0);
}

TEST(NCollection_SequenceTest, ComplexTypeSequence)
{
  NCollection_Sequence<TestClass> aSeq;

  TestClass a(1, "First");
  TestClass b(2, "Second");
  TestClass c(3, "Third");

  aSeq.Append(a);
  aSeq.Append(b);
  aSeq.Append(c);

  EXPECT_EQ(aSeq.Size(), 3);
  EXPECT_EQ(aSeq(1).GetId(), 1);
  EXPECT_STREQ(aSeq(1).GetName(), "First");
  EXPECT_EQ(aSeq(2).GetId(), 2);
  EXPECT_STREQ(aSeq(2).GetName(), "Second");
  EXPECT_EQ(aSeq(3).GetId(), 3);
  EXPECT_STREQ(aSeq(3).GetName(), "Third");

  aSeq.ChangeValue(2) = TestClass(22, "Modified");
  EXPECT_EQ(aSeq(2).GetId(), 22);
  EXPECT_STREQ(aSeq(2).GetName(), "Modified");

  aSeq.Remove(1);
  EXPECT_EQ(aSeq.Size(), 2);
  EXPECT_EQ(aSeq.First().GetId(), 22);
}

TEST(NCollection_SequenceTest, AllocatorTest)
{

  occ::handle<NCollection_BaseAllocator> aAlloc = new NCollection_IncAllocator();
  NCollection_Sequence<ItemType>         aSeq(aAlloc);

  aSeq.Append(10);
  aSeq.Append(20);
  aSeq.Append(30);

  EXPECT_EQ(aSeq.Size(), 3);
  EXPECT_EQ(aSeq(1), 10);
  EXPECT_EQ(aSeq(2), 20);
  EXPECT_EQ(aSeq(3), 30);

  occ::handle<NCollection_BaseAllocator> aAlloc2 = new NCollection_IncAllocator();
  aSeq.Clear(aAlloc2);
  EXPECT_TRUE(aSeq.IsEmpty());

  aSeq.Append(40);
  EXPECT_EQ(aSeq(1), 40);
}

TEST(NCollection_SequenceTest, MoveOperations)
{

  NCollection_Sequence<ItemType> aSeq1;
  aSeq1.Append(10);
  aSeq1.Append(20);
  aSeq1.Append(30);

  NCollection_Sequence<ItemType> aSeq2(std::move(aSeq1));
  EXPECT_TRUE(aSeq1.IsEmpty());
  EXPECT_EQ(aSeq2.Size(), 3);
  EXPECT_EQ(aSeq2(1), 10);
  EXPECT_EQ(aSeq2(2), 20);
  EXPECT_EQ(aSeq2(3), 30);

  NCollection_Sequence<ItemType> aSeq3;
  aSeq3.Append(40);

  NCollection_Sequence<ItemType> aSeq4;
  aSeq4 = std::move(aSeq3);
  EXPECT_TRUE(aSeq3.IsEmpty());
  EXPECT_EQ(aSeq4.Size(), 1);
  EXPECT_EQ(aSeq4(1), 40);
}

TEST(NCollection_SequenceTest, STLAlgorithmCompatibility_MinMax)
{
  NCollection_Sequence<int> aSequence;
  std::list<int>            aStdList;

  std::mt19937                       aGenerator(1);
  std::uniform_int_distribution<int> aDistribution(0, RAND_MAX);
  for (int anIdx = 0; anIdx < 100; ++anIdx)
  {
    int aVal = aDistribution(aGenerator);
    aSequence.Append(aVal);
    aStdList.push_back(aVal);
  }

  auto aMinOCCT = std::min_element(aSequence.begin(), aSequence.end());
  auto aMinStd  = std::min_element(aStdList.begin(), aStdList.end());

  auto aMaxOCCT = std::max_element(aSequence.begin(), aSequence.end());
  auto aMaxStd  = std::max_element(aStdList.begin(), aStdList.end());

  EXPECT_EQ(*aMinOCCT, *aMinStd);
  EXPECT_EQ(*aMaxOCCT, *aMaxStd);
}

TEST(NCollection_SequenceTest, STLAlgorithmCompatibility_Replace)
{
  NCollection_Sequence<int> aSequence;
  std::list<int>            aStdList;

  std::mt19937                       aGenerator(1);
  std::uniform_int_distribution<int> aDistribution(0, RAND_MAX);
  for (int anIdx = 0; anIdx < 100; ++anIdx)
  {
    int aVal = aDistribution(aGenerator);
    aSequence.Append(aVal);
    aStdList.push_back(aVal);
  }

  int aTargetValue = aStdList.back();
  int aNewValue    = -1;

  std::replace(aSequence.begin(), aSequence.end(), aTargetValue, aNewValue);
  std::replace(aStdList.begin(), aStdList.end(), aTargetValue, aNewValue);

  EXPECT_TRUE(std::equal(aSequence.begin(), aSequence.end(), aStdList.begin()));
}

TEST(NCollection_SequenceTest, STLAlgorithmCompatibility_Reverse)
{
  NCollection_Sequence<int> aSequence;
  std::list<int>            aStdList;

  for (int anIdx = 0; anIdx < 100; ++anIdx)
  {
    aSequence.Append(anIdx);
    aStdList.push_back(anIdx);
  }

  std::reverse(aSequence.begin(), aSequence.end());
  std::reverse(aStdList.begin(), aStdList.end());

  EXPECT_TRUE(std::equal(aSequence.begin(), aSequence.end(), aStdList.begin()));
}

TEST(NCollection_SequenceTest, OCC26448_PrependEmptySequence)
{

  NCollection_Sequence<double> aNSeq1, aNSeq2;
  aNSeq1.Append(11.);
  aNSeq1.Prepend(aNSeq2);
  EXPECT_EQ(aNSeq1.Size(), 1);
  EXPECT_DOUBLE_EQ(aNSeq1.First(), 11.0);

  NCollection_Sequence<double> aTSeq1, aTSeq2;
  aTSeq1.Append(11.);
  aTSeq1.Prepend(aTSeq2);
  EXPECT_EQ(aTSeq1.Size(), 1);
  EXPECT_DOUBLE_EQ(aTSeq1.First(), 11.0);
}
