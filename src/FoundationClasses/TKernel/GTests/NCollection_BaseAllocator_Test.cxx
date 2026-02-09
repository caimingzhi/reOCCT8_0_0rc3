

#include <NCollection_BaseAllocator.hpp>
#include <NCollection_Vector.hpp>

#include <gtest/gtest.h>

struct TestStruct
{
  int    myValue1;
  double myValue2;
  char   myChar;

  TestStruct(int theVal1 = 0, double theVal2 = 0.0, char theChar = 'A')
      : myValue1(theVal1),
        myValue2(theVal2),
        myChar(theChar)
  {
  }

  bool operator==(const TestStruct& other) const
  {
    return myValue1 == other.myValue1 && fabs(myValue2 - other.myValue2) < 1e-10
           && myChar == other.myChar;
  }
};

TEST(NCollection_BaseAllocatorTest, DefaultInstance)
{

  occ::handle<NCollection_BaseAllocator> aDefaultAlloc =
    NCollection_BaseAllocator::CommonBaseAllocator();

  EXPECT_FALSE(aDefaultAlloc.IsNull());

  occ::handle<NCollection_BaseAllocator> anotherDefaultAlloc =
    NCollection_BaseAllocator::CommonBaseAllocator();
  EXPECT_EQ(aDefaultAlloc, anotherDefaultAlloc);
}

TEST(NCollection_BaseAllocatorTest, Allocate)
{
  occ::handle<NCollection_BaseAllocator> anAlloc = NCollection_BaseAllocator::CommonBaseAllocator();

  void* ptr1 = anAlloc->Allocate(10);
  EXPECT_NE(ptr1, nullptr);

  void* ptr2 = anAlloc->Allocate(100);
  EXPECT_NE(ptr2, nullptr);

  void* ptr3 = anAlloc->Allocate(1000);
  EXPECT_NE(ptr3, nullptr);

  EXPECT_NE(ptr1, ptr2);
  EXPECT_NE(ptr1, ptr3);
  EXPECT_NE(ptr2, ptr3);

  anAlloc->Free(ptr1);
  anAlloc->Free(ptr2);
  anAlloc->Free(ptr3);
}

TEST(NCollection_BaseAllocatorTest, AllocateStruct)
{
  occ::handle<NCollection_BaseAllocator> anAlloc = NCollection_BaseAllocator::CommonBaseAllocator();

  TestStruct* pStruct = static_cast<TestStruct*>(anAlloc->Allocate(sizeof(TestStruct)));
  EXPECT_NE(pStruct, nullptr);

  new (pStruct) TestStruct(42, 3.14159, 'Z');

  EXPECT_EQ(pStruct->myValue1, 42);
  EXPECT_DOUBLE_EQ(pStruct->myValue2, 3.14159);
  EXPECT_EQ(pStruct->myChar, 'Z');

  pStruct->~TestStruct();
  anAlloc->Free(pStruct);
}

TEST(NCollection_BaseAllocatorTest, AllocateArray)
{
  occ::handle<NCollection_BaseAllocator> anAlloc = NCollection_BaseAllocator::CommonBaseAllocator();

  const int arraySize = 5;

  TestStruct* pArray = static_cast<TestStruct*>(anAlloc->Allocate(arraySize * sizeof(TestStruct)));
  EXPECT_NE(pArray, nullptr);

  for (int i = 0; i < arraySize; ++i)
  {
    new (&pArray[i]) TestStruct(i, i * 1.5, static_cast<char>('A' + i));
  }

  for (int i = 0; i < arraySize; ++i)
  {
    EXPECT_EQ(pArray[i].myValue1, i);
    EXPECT_DOUBLE_EQ(pArray[i].myValue2, i * 1.5);
    EXPECT_EQ(pArray[i].myChar, static_cast<char>('A' + i));
  }

  for (int i = 0; i < arraySize; ++i)
  {
    pArray[i].~TestStruct();
  }
  anAlloc->Free(pArray);
}

TEST(NCollection_BaseAllocatorTest, UsageWithVector)
{

  NCollection_Vector<TestStruct> aVector;

  aVector.Append(TestStruct(10, 1.0, 'X'));
  aVector.Append(TestStruct(20, 2.0, 'Y'));
  aVector.Append(TestStruct(30, 3.0, 'Z'));

  EXPECT_EQ(aVector.Length(), 3);
  EXPECT_EQ(aVector(0).myValue1, 10);
  EXPECT_DOUBLE_EQ(aVector(0).myValue2, 1.0);
  EXPECT_EQ(aVector(0).myChar, 'X');

  EXPECT_EQ(aVector(1).myValue1, 20);
  EXPECT_DOUBLE_EQ(aVector(1).myValue2, 2.0);
  EXPECT_EQ(aVector(1).myChar, 'Y');

  EXPECT_EQ(aVector(2).myValue1, 30);
  EXPECT_DOUBLE_EQ(aVector(2).myValue2, 3.0);
  EXPECT_EQ(aVector(2).myChar, 'Z');

  occ::handle<NCollection_BaseAllocator> aCustomAlloc =
    NCollection_BaseAllocator::CommonBaseAllocator();

  NCollection_Vector<TestStruct> aVectorWithCustomAlloc(5, aCustomAlloc);

  aVectorWithCustomAlloc.Append(TestStruct(40, 4.0, 'P'));
  aVectorWithCustomAlloc.Append(TestStruct(50, 5.0, 'Q'));

  EXPECT_EQ(aVectorWithCustomAlloc.Length(), 2);
  EXPECT_EQ(aVectorWithCustomAlloc(0).myValue1, 40);
  EXPECT_DOUBLE_EQ(aVectorWithCustomAlloc(0).myValue2, 4.0);
  EXPECT_EQ(aVectorWithCustomAlloc(0).myChar, 'P');

  EXPECT_EQ(aVectorWithCustomAlloc(1).myValue1, 50);
  EXPECT_DOUBLE_EQ(aVectorWithCustomAlloc(1).myValue2, 5.0);
  EXPECT_EQ(aVectorWithCustomAlloc(1).myChar, 'Q');
}

TEST(NCollection_BaseAllocatorTest, CopyAndMove)
{
  occ::handle<NCollection_BaseAllocator> anAlloc1 =
    NCollection_BaseAllocator::CommonBaseAllocator();

  NCollection_Vector<TestStruct> aVector1(5, anAlloc1);
  aVector1.Append(TestStruct(10, 1.0, 'A'));
  aVector1.Append(TestStruct(20, 2.0, 'B'));

  NCollection_Vector<TestStruct> aVector2(aVector1);
  EXPECT_EQ(aVector2.Length(), 2);
  EXPECT_EQ(aVector2(0), TestStruct(10, 1.0, 'A'));
  EXPECT_EQ(aVector2(1), TestStruct(20, 2.0, 'B'));

  occ::handle<NCollection_BaseAllocator> anAlloc2 =
    NCollection_BaseAllocator::CommonBaseAllocator();
  NCollection_Vector<TestStruct> aVector3(5, anAlloc2);

  aVector3 = aVector1;
  EXPECT_EQ(aVector3.Length(), 2);
  EXPECT_EQ(aVector3(0), TestStruct(10, 1.0, 'A'));
  EXPECT_EQ(aVector3(1), TestStruct(20, 2.0, 'B'));
}

TEST(NCollection_BaseAllocatorTest, BigAllocation)
{
  occ::handle<NCollection_BaseAllocator> anAlloc = NCollection_BaseAllocator::CommonBaseAllocator();

  const size_t largeSize = 1024 * 1024;
  void*        pLarge    = anAlloc->Allocate(largeSize);
  EXPECT_NE(pLarge, nullptr);

  memset(pLarge, 0xAB, largeSize);

  anAlloc->Free(pLarge);
}
