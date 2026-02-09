

#include <OSD_Parallel.hpp>
#include <Standard_Boolean.hpp>

#include <atomic>
#include <gtest/gtest.h>

namespace
{
  class IncrementerDecrementer
  {
  public:
    IncrementerDecrementer(std::atomic<int>* theVal, bool thePositive)
        : myVal(theVal),
          myPositive(thePositive)
    {
    }

    void operator()(const size_t) const
    {
      if (myPositive)
        ++(*myVal);
      else
        --(*myVal);
    }

  private:
    std::atomic<int>* myVal;
    bool              myPositive;
  };
} // namespace

TEST(Standard_AtomicTest, OCC22980_AtomicOperations)
{
  std::atomic<int> aSum(0);

  EXPECT_EQ(-1, aSum.fetch_sub(1) - 1);
  EXPECT_EQ(0, aSum.fetch_add(1) + 1);
  EXPECT_EQ(1, aSum.fetch_add(1) + 1);
  EXPECT_EQ(2, aSum.fetch_add(1) + 1);

  aSum        = 0;
  const int N = 1 << 24;

  OSD_Parallel::For(0, N, IncrementerDecrementer(&aSum, true));
  EXPECT_EQ(N, aSum);

  OSD_Parallel::For(0, N, IncrementerDecrementer(&aSum, false));
  EXPECT_EQ(0, aSum);
}
