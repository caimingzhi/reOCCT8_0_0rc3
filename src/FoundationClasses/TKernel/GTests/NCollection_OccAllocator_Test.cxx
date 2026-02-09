

#include <NCollection_OccAllocator.hpp>
#include <NCollection_IncAllocator.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Assert.hpp>

#include <gtest/gtest.h>
#include <list>
#include <vector>

class NCollection_OccAllocatorTest : public testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(NCollection_OccAllocatorTest, AllocatorTypeTraits)
{

  typedef occ::handle<Standard_Transient>      anElemType;
  typedef NCollection_OccAllocator<anElemType> anAllocatorType;

  EXPECT_EQ(sizeof(anAllocatorType::value_type), sizeof(anElemType));
  EXPECT_EQ(sizeof(anAllocatorType::pointer), sizeof(void*));
  EXPECT_EQ(sizeof(anAllocatorType::const_pointer), sizeof(void*));
  EXPECT_EQ(sizeof(anAllocatorType::size_type), sizeof(size_t));
  EXPECT_EQ(sizeof(anAllocatorType::difference_type), sizeof(ptrdiff_t));

  anElemType                       aDummy;
  anAllocatorType::reference       aRef      = aDummy;
  anAllocatorType::const_reference aConstRef = aDummy;

  EXPECT_EQ(&aRef, &aDummy);
  EXPECT_EQ(&aConstRef, &aDummy);

  typedef int                                             anOtherElemType;
  typedef anAllocatorType::rebind<anOtherElemType>::other anOtherAllocatorType;
  EXPECT_EQ(sizeof(anOtherAllocatorType::value_type), sizeof(anOtherElemType));
}

TEST_F(NCollection_OccAllocatorTest, STLContainerIntegration)
{

  occ::handle<NCollection_IncAllocator> anIncAlloc = new NCollection_IncAllocator();

  {

    NCollection_OccAllocator<int>                 anSAlloc(anIncAlloc);
    std::list<int, NCollection_OccAllocator<int>> aList(anSAlloc);

    aList.push_back(2);
    EXPECT_EQ(1, aList.size());
    EXPECT_EQ(2, aList.front());

    NCollection_OccAllocator<char>                  aCAlloc;
    std::vector<int, NCollection_OccAllocator<int>> aVector(aCAlloc);

    aVector.push_back(1);
    EXPECT_EQ(1, aVector.size());
    EXPECT_EQ(1, aVector[0]);

    NCollection_OccAllocator<void*>                 aVAlloc;
    std::vector<int, NCollection_OccAllocator<int>> aVector2(aVAlloc);

    aVector2.resize(10);
    aVector2.push_back(-1);
    EXPECT_EQ(11, aVector2.size());
    EXPECT_EQ(-1, aVector2.back());

    EXPECT_NE(anSAlloc, aCAlloc);

    NCollection_OccAllocator<int> anIAlloc(anIncAlloc);
    EXPECT_EQ(anSAlloc, anIAlloc);
  }
}

TEST_F(NCollection_OccAllocatorTest, DefaultAllocator)
{

  NCollection_OccAllocator<int>                   aDefaultAlloc;
  std::vector<int, NCollection_OccAllocator<int>> aVector(aDefaultAlloc);

  for (int i = 0; i < 100; ++i)
  {
    aVector.push_back(i);
  }

  EXPECT_EQ(100, aVector.size());

  for (size_t i = 0; i < aVector.size(); ++i)
  {
    EXPECT_EQ(static_cast<int>(i), aVector[i]);
  }
}

TEST_F(NCollection_OccAllocatorTest, AllocatorComparison)
{
  occ::handle<NCollection_IncAllocator> anIncAlloc1 = new NCollection_IncAllocator();
  occ::handle<NCollection_IncAllocator> anIncAlloc2 = new NCollection_IncAllocator();

  NCollection_OccAllocator<int> aAlloc1(anIncAlloc1);
  NCollection_OccAllocator<int> aAlloc2(anIncAlloc1);
  NCollection_OccAllocator<int> aAlloc3(anIncAlloc2);
  NCollection_OccAllocator<int> aAlloc4;

  EXPECT_EQ(aAlloc1, aAlloc2);
  EXPECT_NE(aAlloc1, aAlloc3);
  EXPECT_NE(aAlloc1, aAlloc4);

  EXPECT_FALSE(aAlloc1 != aAlloc2);
  EXPECT_TRUE(aAlloc1 != aAlloc3);
}

TEST_F(NCollection_OccAllocatorTest, CrossTypeCompatibility)
{
  occ::handle<NCollection_IncAllocator> anIncAlloc = new NCollection_IncAllocator();

  NCollection_OccAllocator<int>    anIntAlloc(anIncAlloc);
  NCollection_OccAllocator<double> aDoubleAlloc(anIncAlloc);
  NCollection_OccAllocator<char>   aCharAlloc(anIncAlloc);

  EXPECT_EQ(anIntAlloc, NCollection_OccAllocator<int>(anIncAlloc));

  std::vector<int, NCollection_OccAllocator<int>>       anIntVector(anIntAlloc);
  std::vector<double, NCollection_OccAllocator<double>> aDoubleVector(aDoubleAlloc);

  anIntVector.push_back(42);
  aDoubleVector.push_back(3.14);

  EXPECT_EQ(1, anIntVector.size());
  EXPECT_EQ(1, aDoubleVector.size());
  EXPECT_EQ(42, anIntVector[0]);
  EXPECT_DOUBLE_EQ(3.14, aDoubleVector[0]);
}
