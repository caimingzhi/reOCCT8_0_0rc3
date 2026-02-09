

#include <Standard_Handle.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <NCollection_IncAllocator.hpp>
#include <NCollection_HeapAllocator.hpp>

#include <gtest/gtest.h>

class TestBase : public Standard_Transient
{
public:
  TestBase() = default;

  ~TestBase() override = default;
  DEFINE_STANDARD_RTTI_INLINE(TestBase, Standard_Transient)
};

class TestDerived : public TestBase
{
public:
  TestDerived() = default;

  ~TestDerived() override = default;
  DEFINE_STANDARD_RTTI_INLINE(TestDerived, TestBase)
};

class TestOther : public Standard_Transient
{
public:
  TestOther() = default;

  ~TestOther() override = default;
  DEFINE_STANDARD_RTTI_INLINE(TestOther, Standard_Transient)
};

class HandleOperationsTest : public testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(HandleOperationsTest, BasicHandleOperations)
{

  occ::handle<TestDerived> aDerived = new TestDerived();
  EXPECT_FALSE(aDerived.IsNull());

  const occ::handle<TestDerived>& aConstDerived = aDerived;
  const occ::handle<TestBase>&    aConstBase    = aDerived;
  (void)aConstBase;

  TestDerived*       aDerivedPtr      = aDerived.get();
  const TestDerived* aConstDerivedPtr = aDerived.get();
  EXPECT_NE(nullptr, aDerivedPtr);
  EXPECT_NE(nullptr, aConstDerivedPtr);
  EXPECT_EQ(aDerivedPtr, aConstDerivedPtr);

  TestDerived&       aDerivedRef      = *aDerived;
  const TestDerived& aConstDerivedRef = *aConstDerived;
  EXPECT_EQ(&aDerivedRef, aDerivedPtr);
  EXPECT_EQ(&aConstDerivedRef, aConstDerivedPtr);

  occ::handle<TestBase> aBase = aDerived;
  EXPECT_FALSE(aBase.IsNull());
  EXPECT_EQ(aBase.get(), aDerived.get());
}

TEST_F(HandleOperationsTest, HandleDownCast)
{

  occ::handle<TestDerived> aDerived = new TestDerived();
  occ::handle<TestBase>    aBase    = aDerived;

  occ::handle<TestDerived> aDownCastDerived = occ::down_cast<TestDerived>(aBase);
  EXPECT_FALSE(aDownCastDerived.IsNull());
  EXPECT_EQ(aDownCastDerived.get(), aDerived.get());

  occ::handle<TestOther>          anOther         = new TestOther();
  occ::handle<Standard_Transient> aTransient      = anOther;
  occ::handle<TestDerived>        aFailedDownCast = occ::down_cast<TestDerived>(aTransient);
  EXPECT_TRUE(aFailedDownCast.IsNull());
}

TEST_F(HandleOperationsTest, HandleComparisons)
{
  occ::handle<TestDerived> aDerived  = new TestDerived();
  occ::handle<TestDerived> aDerived2 = aDerived;
  occ::handle<TestDerived> aDerived3 = new TestDerived();
  occ::handle<TestBase>    aBase     = aDerived;

  EXPECT_TRUE(aDerived == aDerived);
  EXPECT_TRUE(aDerived == aDerived2);
  EXPECT_TRUE(aDerived == aBase);
  EXPECT_FALSE(aDerived == aDerived3);

  TestDerived*       aDerivedPtr      = aDerived.get();
  const TestDerived* aConstDerivedPtr = aDerived.get();
  EXPECT_TRUE(aDerived == aDerivedPtr);
  EXPECT_TRUE(aDerivedPtr == aDerived);
  EXPECT_TRUE(aDerived == aConstDerivedPtr);
  EXPECT_TRUE(aConstDerivedPtr == aDerived);

  EXPECT_FALSE(aDerived != aDerived2);
  EXPECT_TRUE(aDerived != aDerived3);

  EXPECT_TRUE(static_cast<bool>(aDerived));
  occ::handle<TestDerived> aNullDerived;
  EXPECT_FALSE(static_cast<bool>(aNullDerived));
}

TEST_F(HandleOperationsTest, AllocatorHandleCasting)
{

  occ::handle<NCollection_BaseAllocator> aBasePtr = new NCollection_IncAllocator();
  EXPECT_FALSE(aBasePtr.IsNull());

  occ::handle<NCollection_IncAllocator> anIncAlloc =
    occ::down_cast<NCollection_IncAllocator>(aBasePtr);
  EXPECT_FALSE(anIncAlloc.IsNull());

  occ::handle<NCollection_BaseAllocator> aBaseAlloc = anIncAlloc;
  EXPECT_FALSE(aBaseAlloc.IsNull());
  EXPECT_EQ(aBaseAlloc.get(), aBasePtr.get());

  occ::handle<NCollection_HeapAllocator> aHeapAlloc =
    occ::down_cast<NCollection_HeapAllocator>(aBasePtr);
  EXPECT_TRUE(aHeapAlloc.IsNull());
}

TEST_F(HandleOperationsTest, HandleCopyAndAssignment)
{
  occ::handle<TestDerived> aDerived1 = new TestDerived();

  occ::handle<TestDerived> aDerived2(aDerived1);
  EXPECT_FALSE(aDerived2.IsNull());
  EXPECT_EQ(aDerived1.get(), aDerived2.get());

  occ::handle<TestDerived> aDerived3;
  EXPECT_TRUE(aDerived3.IsNull());

  aDerived3 = aDerived1;
  EXPECT_FALSE(aDerived3.IsNull());
  EXPECT_EQ(aDerived1.get(), aDerived3.get());

#include <Standard_WarningsDisable.hpp>
  aDerived1 = aDerived1;
#include <Standard_WarningsRestore.hpp>
  EXPECT_FALSE(aDerived1.IsNull());

  aDerived3 = occ::handle<TestDerived>();
  EXPECT_TRUE(aDerived3.IsNull());
}

TEST_F(HandleOperationsTest, HandleWithDifferentTypes)
{
  occ::handle<TestDerived> aDerived = new TestDerived();
  occ::handle<TestOther>   anOther  = new TestOther();

  occ::handle<Standard_Transient> aDerivedTransient = aDerived;
  occ::handle<Standard_Transient> anOtherTransient  = anOther;

  EXPECT_FALSE(aDerivedTransient == anOtherTransient);
  EXPECT_TRUE(aDerivedTransient != anOtherTransient);

  EXPECT_TRUE(aDerivedTransient == aDerived);
  EXPECT_TRUE(anOtherTransient == anOther);

  EXPECT_EQ(aDerivedTransient.get(), aDerived.get());
  EXPECT_EQ(anOtherTransient.get(), anOther.get());
}

TEST_F(HandleOperationsTest, HandleNullOperations)
{
  occ::handle<TestDerived> aNullHandle;
  occ::handle<TestDerived> anotherNullHandle;
  occ::handle<TestDerived> aValidHandle = new TestDerived();

  EXPECT_TRUE(aNullHandle.IsNull());
  EXPECT_EQ(nullptr, aNullHandle.get());

  EXPECT_TRUE(aNullHandle == anotherNullHandle);
  EXPECT_FALSE(aNullHandle == aValidHandle);
  EXPECT_FALSE(aValidHandle == aNullHandle);

  EXPECT_FALSE(aNullHandle != anotherNullHandle);
  EXPECT_TRUE(aNullHandle != aValidHandle);
  EXPECT_TRUE(aValidHandle != aNullHandle);

  EXPECT_FALSE(static_cast<bool>(aNullHandle));
  EXPECT_TRUE(static_cast<bool>(aValidHandle));
}
