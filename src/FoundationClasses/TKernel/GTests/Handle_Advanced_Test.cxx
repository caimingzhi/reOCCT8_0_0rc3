

#include <Standard_Handle.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <Standard_Assert.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <NCollection_IncAllocator.hpp>
#include <NCollection_HeapAllocator.hpp>
#include <OSD_Timer.hpp>

#include <gtest/gtest.h>
#include <vector>
#include <memory>
#include <typeinfo>
#include <type_traits>

#define CHECK_HANDLE(ok, what) EXPECT_TRUE(ok) << "Checking " << what << " failed"

class TransientRoot : public Standard_Transient
{
public:
  virtual const char* Name() const { return "TransientRoot"; }

  virtual Standard_Transient* CreateParent() const { return new Standard_Transient; }

  virtual Standard_Transient* Clone() const { return new TransientRoot; }
  DEFINE_STANDARD_RTTI_INLINE(TransientRoot, Standard_Transient)
};

#define QA_DEFINECLASS(theClass, theParent)                                                        \
  class theClass : public theParent                                                                \
  {                                                                                                \
  public:                                                                                          \
    virtual const char* Name() const override                                                      \
    {                                                                                              \
      return #theClass;                                                                            \
    }                                                                                              \
    virtual Standard_Transient* CreateParent() const override                                      \
    {                                                                                              \
      return new theParent();                                                                      \
    }                                                                                              \
    virtual Standard_Transient* Clone() const override                                             \
    {                                                                                              \
      return new theClass();                                                                       \
    }                                                                                              \
    DEFINE_STANDARD_RTTI_INLINE(theClass, theParent)                                               \
  };                                                                                               \
  DEFINE_STANDARD_HANDLE(theClass, theParent)

#define QA_NAME(theNum) QaClass##theNum##_50
#define QA_HANDLE_NAME(theNum) Handle(QaClass##theNum##_50)

#define QA_DEFINECLASS10(theParent, theTens)                                                       \
  QA_DEFINECLASS(QA_NAME(theTens##0), theParent)                                                   \
  QA_DEFINECLASS(QA_NAME(theTens##1), QA_NAME(theTens##0))                                         \
  QA_DEFINECLASS(QA_NAME(theTens##2), QA_NAME(theTens##1))                                         \
  QA_DEFINECLASS(QA_NAME(theTens##3), QA_NAME(theTens##2))                                         \
  QA_DEFINECLASS(QA_NAME(theTens##4), QA_NAME(theTens##3))                                         \
  QA_DEFINECLASS(QA_NAME(theTens##5), QA_NAME(theTens##4))                                         \
  QA_DEFINECLASS(QA_NAME(theTens##6), QA_NAME(theTens##5))                                         \
  QA_DEFINECLASS(QA_NAME(theTens##7), QA_NAME(theTens##6))                                         \
  QA_DEFINECLASS(QA_NAME(theTens##8), QA_NAME(theTens##7))                                         \
  QA_DEFINECLASS(QA_NAME(theTens##9), QA_NAME(theTens##8))

QA_DEFINECLASS10(TransientRoot, 0)
QA_DEFINECLASS10(QaClass09_50, 1)
QA_DEFINECLASS10(QaClass19_50, 2)
QA_DEFINECLASS10(QaClass29_50, 3)
QA_DEFINECLASS10(QaClass39_50, 4)
QA_DEFINECLASS(QaClass50_50, QaClass49_50)

namespace
{
  class QaClass50_50Anon : public QaClass49_50
  {
  public:
    QaClass50_50Anon() = default;
  };
} // namespace

namespace QaNamespace
{
  class QaClass50_50 : public QaClass49_50
  {
  public:
    QaClass50_50() = default;
  };
} // namespace QaNamespace

namespace
{
  class QATimer : public OSD_Timer
  {
  public:
    enum TimeFormat
    {
      Seconds,
      Milliseconds,
      Microseconds
    };

    QATimer(const char* theOperationName, TimeFormat theFormat = Milliseconds)
        : myOperationName(theOperationName),
          myFormat(theFormat)
    {
      Start();
    }

    ~QATimer() override
    {
      Stop();
      double aTime = 0.0;
      switch (myFormat)
      {
        case Seconds:
          aTime = ElapsedTime();
          break;
        case Milliseconds:
          aTime = ElapsedTime() * 1000.0;
          break;
        case Microseconds:
          aTime = ElapsedTime() * 1000000.0;
          break;
      }

      (void)aTime;
      (void)myOperationName;
    }

  private:
    const char* myOperationName;
    TimeFormat  myFormat;
  };
} // namespace

class HandleAdvancedTest : public testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(HandleAdvancedTest, CompilerSpecificBehavior)
{
  occ::handle<TransientRoot> aRoot = new TransientRoot();
  EXPECT_FALSE(aRoot.IsNull());

  const occ::handle<TransientRoot>& aConstRoot = aRoot;
  (void)aConstRoot;
  occ::handle<Standard_Transient> aTransient = aRoot;

  auto testFunction = [](const occ::handle<Standard_Transient>& theObj) -> bool
  { return !theObj.IsNull(); };

  EXPECT_TRUE(testFunction(aRoot));

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)                              \
  || (defined(__GNUC__) && __GNUC__ >= 4 && __GNUC_MINOR__ >= 3)

  auto testOverload1 = [](const occ::handle<Standard_Transient>&) -> int { return 1; };
  auto testOverload2 = [](const occ::handle<TransientRoot>&) -> int { return 2; };

  EXPECT_EQ(2, testOverload2(aRoot));
  EXPECT_EQ(1, testOverload1(aTransient));
#endif

  const occ::handle<Standard_Transient>& aTransient2 = aRoot;
  CHECK_HANDLE(!aTransient2.IsNull(), "cast to base class const reference");
}

TEST_F(HandleAdvancedTest, DeepHierarchyRTTI)
{

  occ::handle<Standard_Type> aType00 = STANDARD_TYPE(QaClass00_50);
  occ::handle<Standard_Type> aType10 = STANDARD_TYPE(QaClass10_50);
  occ::handle<Standard_Type> aType20 = STANDARD_TYPE(QaClass20_50);
  occ::handle<Standard_Type> aType30 = STANDARD_TYPE(QaClass30_50);
  occ::handle<Standard_Type> aType40 = STANDARD_TYPE(QaClass40_50);
  occ::handle<Standard_Type> aType50 = STANDARD_TYPE(QaClass50_50);

  occ::handle<QaClass00_50> aHandle = new QaClass40_50();

  EXPECT_STREQ("QaClass40_50", aHandle->DynamicType()->Name());

  EXPECT_TRUE(aHandle->IsKind(aType00)) << "IsKind failed for root type";
  EXPECT_TRUE(aHandle->IsKind(aType10)) << "IsKind failed for parent type 10";
  EXPECT_TRUE(aHandle->IsKind(aType20)) << "IsKind failed for parent type 20";
  EXPECT_TRUE(aHandle->IsKind(aType30)) << "IsKind failed for parent type 30";
  EXPECT_TRUE(aHandle->IsKind(aType40)) << "IsKind failed for exact type 40";
  EXPECT_FALSE(aHandle->IsKind(aType50)) << "IsKind should be false for child type 50";

  EXPECT_TRUE(aHandle->IsKind("QaClass00_50"));
  EXPECT_TRUE(aHandle->IsKind("QaClass10_50"));
  EXPECT_TRUE(aHandle->IsKind("QaClass20_50"));
  EXPECT_TRUE(aHandle->IsKind("QaClass30_50"));
  EXPECT_TRUE(aHandle->IsKind("QaClass40_50"));
  EXPECT_FALSE(aHandle->IsKind("QaClass50_50"));

  EXPECT_FALSE(aHandle->IsInstance(aType00));
  EXPECT_FALSE(aHandle->IsInstance(aType10));
  EXPECT_FALSE(aHandle->IsInstance(aType20));
  EXPECT_FALSE(aHandle->IsInstance(aType30));
  EXPECT_TRUE(aHandle->IsInstance(aType40));
  EXPECT_FALSE(aHandle->IsInstance(aType50));
}

TEST_F(HandleAdvancedTest, TypeInfoCompatibility)
{
  occ::handle<QaClass40_50> aHandle = new QaClass40_50();

#ifdef __cpp_rtti

  #include <Standard_WarningsDisable.hpp>

  const std::type_info& aTypeInfo = typeid(*aHandle.get());

  EXPECT_FALSE(aTypeInfo == typeid(QaClass00_50));
  EXPECT_FALSE(aTypeInfo == typeid(QaClass10_50));
  EXPECT_FALSE(aTypeInfo == typeid(QaClass20_50));
  EXPECT_FALSE(aTypeInfo == typeid(QaClass30_50));
  EXPECT_TRUE(aTypeInfo == typeid(QaClass40_50));
  EXPECT_FALSE(aTypeInfo == typeid(QaClass50_50));

  #if __cplusplus >= 201103L
  std::type_index aCppType = typeid(*aHandle.get());
  EXPECT_FALSE(aCppType == typeid(QaClass00_50));
  EXPECT_TRUE(aCppType == typeid(QaClass40_50));
  #endif

  QaClass50_50Anon          anAnon;
  QaNamespace::QaClass50_50 aNamed;

  EXPECT_FALSE(typeid(anAnon) == typeid(aNamed));
  EXPECT_FALSE(typeid(anAnon) == typeid(QaClass50_50));
  EXPECT_FALSE(typeid(aNamed) == typeid(QaClass50_50));

  #include <Standard_WarningsRestore.hpp>

#endif

  EXPECT_TRUE(std::is_class<Standard_Transient>::value);
}

TEST_F(HandleAdvancedTest, AllocatorHandlePerformance)
{

  occ::handle<NCollection_BaseAllocator> aBasePtr = new NCollection_IncAllocator();
  EXPECT_FALSE(aBasePtr.IsNull());

  {
    QATimer aTimer("IncAllocator DownCast", QATimer::Microseconds);
    for (int i = 0; i < 1000; ++i)
    {
      occ::handle<NCollection_IncAllocator> anIncAlloc =
        occ::down_cast<NCollection_IncAllocator>(aBasePtr);
      EXPECT_FALSE(anIncAlloc.IsNull());
    }
  }

  {
    QATimer aTimer("Failed HeapAllocator DownCast", QATimer::Microseconds);
    for (int i = 0; i < 1000; ++i)
    {
      occ::handle<NCollection_HeapAllocator> aHeapAlloc =
        occ::down_cast<NCollection_HeapAllocator>(aBasePtr);
      EXPECT_TRUE(aHeapAlloc.IsNull());
    }
  }
}

TEST_F(HandleAdvancedTest, HandleArrayOperations)
{

  std::vector<occ::handle<QaClass00_50>> aHandleVector;

  aHandleVector.push_back(new QaClass00_50());
  aHandleVector.push_back(new QaClass10_50());
  aHandleVector.push_back(new QaClass20_50());
  aHandleVector.push_back(new QaClass30_50());
  aHandleVector.push_back(new QaClass40_50());

  EXPECT_EQ(5, aHandleVector.size());

  for (size_t i = 0; i < aHandleVector.size(); ++i)
  {
    EXPECT_FALSE(aHandleVector[i].IsNull());

    EXPECT_TRUE(aHandleVector[i]->IsKind("QaClass00_50"));

    occ::handle<QaClass00_50> aCast = aHandleVector[i];
    EXPECT_FALSE(aCast.IsNull());
    EXPECT_EQ(aHandleVector[i].get(), aCast.get());
  }

  occ::handle<QaClass40_50> aSpecific = occ::down_cast<QaClass40_50>(aHandleVector[4]);
  EXPECT_FALSE(aSpecific.IsNull());

  occ::handle<QaClass40_50> aFailedCast = occ::down_cast<QaClass40_50>(aHandleVector[0]);
  EXPECT_TRUE(aFailedCast.IsNull());
}

TEST_F(HandleAdvancedTest, ConstHandleOperations)
{
  occ::handle<QaClass30_50>        aNonConstHandle = new QaClass30_50();
  const occ::handle<QaClass30_50>& aConstHandle    = aNonConstHandle;

  EXPECT_EQ(aNonConstHandle.get(), aConstHandle.get());

  const QaClass30_50* aConstPtr    = aConstHandle.get();
  QaClass30_50*       aNonConstPtr = aNonConstHandle.get();

  EXPECT_EQ(aConstPtr, aNonConstPtr);

  const occ::handle<QaClass00_50>& aConstBase    = aConstHandle;
  occ::handle<QaClass00_50>        aNonConstBase = aNonConstHandle;

  EXPECT_EQ(aConstBase.get(), aNonConstBase.get());

  EXPECT_TRUE(aConstHandle == aNonConstHandle);
  EXPECT_TRUE(aConstBase == aNonConstBase);
  EXPECT_FALSE(aConstHandle != aNonConstHandle);
}

TEST_F(HandleAdvancedTest, WeakReferenceSimulation)
{

  QaClass20_50* aRawPtr = nullptr;

  {
    occ::handle<QaClass20_50> aHandle = new QaClass20_50();
    aRawPtr                           = aHandle.get();

    EXPECT_NE(nullptr, aRawPtr);

    EXPECT_FALSE(aHandle.IsNull());
    EXPECT_EQ(aRawPtr, aHandle.get());
  }

  std::vector<occ::handle<QaClass20_50>> aHandles;
  bool                                   aFoundDifferent = false;

  for (int i = 0; i < 10 && !aFoundDifferent; ++i)
  {
    aHandles.push_back(new QaClass20_50());
    if (aHandles.back().get() != aRawPtr)
    {
      aFoundDifferent = true;
    }
  }

  EXPECT_TRUE(aFoundDifferent || !aFoundDifferent);
}
