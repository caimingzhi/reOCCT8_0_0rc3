

#include <Quantity_Period.hpp>

#include <gtest/gtest.h>

class Quantity_PeriodTest : public testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(Quantity_PeriodTest, BasicConstruction)
{

  Quantity_Period aPeriod1(1, 2, 3, 4, 5, 6);

  int dd, hh, mn, ss, mis, mics;
  aPeriod1.Values(dd, hh, mn, ss, mis, mics);

  EXPECT_EQ(1, dd);
  EXPECT_EQ(2, hh);
  EXPECT_EQ(3, mn);
  EXPECT_EQ(4, ss);
  EXPECT_EQ(5, mis);
  EXPECT_EQ(6, mics);

  Quantity_Period aPeriod2(3600, 500000);

  int ss2, mics2;
  aPeriod2.Values(ss2, mics2);

  EXPECT_EQ(3600, ss2);
  EXPECT_EQ(500000, mics2);
}

TEST_F(Quantity_PeriodTest, ConstexprComparisons)
{
  Quantity_Period aPeriod1(0, 0, 0, 100, 0, 0);
  Quantity_Period aPeriod2(0, 0, 0, 100, 0, 0);
  Quantity_Period aPeriod3(0, 0, 0, 200, 0, 0);

  EXPECT_TRUE(aPeriod1.IsEqual(aPeriod2));
  EXPECT_FALSE(aPeriod1.IsEqual(aPeriod3));

  EXPECT_TRUE(aPeriod1.IsShorter(aPeriod3));
  EXPECT_FALSE(aPeriod3.IsShorter(aPeriod1));
  EXPECT_FALSE(aPeriod1.IsShorter(aPeriod2));

  EXPECT_TRUE(aPeriod3.IsLonger(aPeriod1));
  EXPECT_FALSE(aPeriod1.IsLonger(aPeriod3));
  EXPECT_FALSE(aPeriod1.IsLonger(aPeriod2));
}

TEST_F(Quantity_PeriodTest, Validation)
{

  EXPECT_TRUE(Quantity_Period::IsValid(1, 2, 3, 4, 5, 6));
  EXPECT_TRUE(Quantity_Period::IsValid(0, 0, 0, 0, 0, 0));

  EXPECT_FALSE(Quantity_Period::IsValid(-1, 0, 0, 0, 0, 0));
  EXPECT_FALSE(Quantity_Period::IsValid(0, -1, 0, 0, 0, 0));
  EXPECT_FALSE(Quantity_Period::IsValid(0, 0, -1, 0, 0, 0));
  EXPECT_FALSE(Quantity_Period::IsValid(0, 0, 0, -1, 0, 0));
  EXPECT_FALSE(Quantity_Period::IsValid(0, 0, 0, 0, -1, 0));
  EXPECT_FALSE(Quantity_Period::IsValid(0, 0, 0, 0, 0, -1));

  EXPECT_TRUE(Quantity_Period::IsValid(100, 500));
  EXPECT_FALSE(Quantity_Period::IsValid(-1, 500));
  EXPECT_FALSE(Quantity_Period::IsValid(100, -1));
}

TEST_F(Quantity_PeriodTest, SetValuesRoundTrip)
{
  Quantity_Period aPeriod(0, 0);
  aPeriod.SetValues(2, 3, 4, 5, 6, 7);

  int dd, hh, mn, ss, mis, mics;
  aPeriod.Values(dd, hh, mn, ss, mis, mics);

  EXPECT_EQ(2, dd);
  EXPECT_EQ(3, hh);
  EXPECT_EQ(4, mn);
  EXPECT_EQ(5, ss);
  EXPECT_EQ(6, mis);
  EXPECT_EQ(7, mics);
}

TEST_F(Quantity_PeriodTest, FormatConversion)
{

  Quantity_Period aPeriod1(1, 0, 0, 0, 0, 0);

  int ss, mics;
  aPeriod1.Values(ss, mics);

  EXPECT_EQ(86400, ss);

  Quantity_Period aPeriod2(0, 1, 0, 0, 0, 0);
  aPeriod2.Values(ss, mics);

  EXPECT_EQ(3600, ss);

  Quantity_Period aPeriod3(0, 0, 1, 0, 0, 0);
  aPeriod3.Values(ss, mics);

  EXPECT_EQ(60, ss);
}

TEST_F(Quantity_PeriodTest, MillisecondConversion)
{

  Quantity_Period aPeriod(0, 0, 0, 0, 1, 0);

  int ss, mics;
  aPeriod.Values(ss, mics);

  EXPECT_EQ(0, ss);
  EXPECT_EQ(1000, mics);

  Quantity_Period aPeriod2(0, 0, 0, 0, 5, 250);
  aPeriod2.Values(ss, mics);

  EXPECT_EQ(0, ss);
  EXPECT_EQ(5250, mics);
}

TEST_F(Quantity_PeriodTest, MicrosecondOverflow)
{

  Quantity_Period aPeriod(0, 0);
  aPeriod.SetValues(0, 1500000);

  int ss, mics;
  aPeriod.Values(ss, mics);

  EXPECT_EQ(1, ss);
  EXPECT_EQ(500000, mics);
}

TEST_F(Quantity_PeriodTest, AddPeriods)
{
  Quantity_Period aPeriod1(0, 1, 0, 0, 0, 0);
  Quantity_Period aPeriod2(0, 2, 0, 0, 0, 0);

  Quantity_Period aResult = aPeriod1.Add(aPeriod2);

  int ss, mics;
  aResult.Values(ss, mics);

  EXPECT_EQ(10800, ss);
  EXPECT_EQ(0, mics);
}

TEST_F(Quantity_PeriodTest, AddWithMicrosecondOverflow)
{
  Quantity_Period aPeriod1(0, 0, 0, 0, 0, 600000);
  Quantity_Period aPeriod2(0, 0, 0, 0, 0, 600000);

  Quantity_Period aResult = aPeriod1.Add(aPeriod2);

  int ss, mics;
  aResult.Values(ss, mics);

  EXPECT_EQ(1, ss);
  EXPECT_EQ(200000, mics);
}

TEST_F(Quantity_PeriodTest, SubtractPeriods)
{
  Quantity_Period aPeriod1(0, 3, 0, 0, 0, 0);
  Quantity_Period aPeriod2(0, 1, 0, 0, 0, 0);

  Quantity_Period aResult = aPeriod1.Subtract(aPeriod2);

  int ss, mics;
  aResult.Values(ss, mics);

  EXPECT_EQ(7200, ss);
  EXPECT_EQ(0, mics);
}

TEST_F(Quantity_PeriodTest, SubtractWithMicrosecondUnderflow)
{
  Quantity_Period aPeriod1(0, 0, 0, 1, 0, 200000);
  Quantity_Period aPeriod2(0, 0, 0, 0, 0, 500000);

  Quantity_Period aResult = aPeriod1.Subtract(aPeriod2);

  int ss, mics;
  aResult.Values(ss, mics);

  EXPECT_EQ(0, ss);
  EXPECT_EQ(700000, mics);
}

TEST_F(Quantity_PeriodTest, SubtractNegative)
{
  Quantity_Period aPeriod1(0, 1, 0, 0, 0, 0);
  Quantity_Period aPeriod2(0, 3, 0, 0, 0, 0);

  Quantity_Period aResult = aPeriod1.Subtract(aPeriod2);

  int ss, mics;
  aResult.Values(ss, mics);

  EXPECT_EQ(7200, ss);
  EXPECT_EQ(0, mics);
}

TEST_F(Quantity_PeriodTest, ComplexCalculations)
{

  Quantity_Period aPeriod(1, 2, 30, 45, 500, 250);

  int ss, mics;
  aPeriod.Values(ss, mics);

  EXPECT_EQ(95445, ss);

  EXPECT_EQ(500250, mics);
}

TEST_F(Quantity_PeriodTest, ComponentExtraction)
{
  Quantity_Period aPeriod(2, 3, 45, 30, 123, 456);

  int dd, hh, mn, ss, mis, mics;
  aPeriod.Values(dd, hh, mn, ss, mis, mics);

  EXPECT_EQ(2, dd);
  EXPECT_EQ(3, hh);
  EXPECT_EQ(45, mn);
  EXPECT_EQ(30, ss);
  EXPECT_EQ(123, mis);
  EXPECT_EQ(456, mics);
}

TEST_F(Quantity_PeriodTest, ZeroPeriod)
{
  Quantity_Period aPeriod(0, 0, 0, 0, 0, 0);

  int dd, hh, mn, ss, mis, mics;
  aPeriod.Values(dd, hh, mn, ss, mis, mics);

  EXPECT_EQ(0, dd);
  EXPECT_EQ(0, hh);
  EXPECT_EQ(0, mn);
  EXPECT_EQ(0, ss);
  EXPECT_EQ(0, mis);
  EXPECT_EQ(0, mics);

  Quantity_Period aZero2(0, 0, 0, 0, 0, 0);
  EXPECT_TRUE(aPeriod.IsEqual(aZero2));
}

TEST_F(Quantity_PeriodTest, LargeValues)
{

  Quantity_Period aPeriod(100, 0, 0, 0, 0, 0);

  int ss, mics;
  aPeriod.Values(ss, mics);

  EXPECT_EQ(8640000, ss);
  EXPECT_EQ(0, mics);
}

TEST_F(Quantity_PeriodTest, TimeConstantValues)
{

  Quantity_Period aPeriod24h(0, 24, 0, 0, 0, 0);
  Quantity_Period aPeriod1d(1, 0, 0, 0, 0, 0);

  int ss1, mics1, ss2, mics2;
  aPeriod24h.Values(ss1, mics1);
  aPeriod1d.Values(ss2, mics2);

  EXPECT_EQ(ss1, ss2);

  Quantity_Period aPeriod60s(0, 0, 0, 60, 0, 0);
  Quantity_Period aPeriod1m(0, 0, 1, 0, 0, 0);

  aPeriod60s.Values(ss1, mics1);
  aPeriod1m.Values(ss2, mics2);

  EXPECT_EQ(ss1, ss2);

  Quantity_Period aPeriod60m(0, 0, 60, 0, 0, 0);
  Quantity_Period aPeriod1h(0, 1, 0, 0, 0, 0);

  aPeriod60m.Values(ss1, mics1);
  aPeriod1h.Values(ss2, mics2);

  EXPECT_EQ(ss1, ss2);
}

TEST_F(Quantity_PeriodTest, MillisecondToSecondConversion)
{
  Quantity_Period aPeriod(0, 0, 0, 0, 1000, 0);

  int ss, mics;
  aPeriod.Values(ss, mics);

  EXPECT_EQ(1, ss);
  EXPECT_EQ(0, mics);
}

TEST_F(Quantity_PeriodTest, SubtractLargeMicrosecondUnderflow)
{
  Quantity_Period aPeriod1(0, 0, 0, 10, 0, 200000);
  Quantity_Period aPeriod2(0, 0, 0, 0, 0, 2700000);

  Quantity_Period aResult = aPeriod1.Subtract(aPeriod2);

  int ss, mics;
  aResult.Values(ss, mics);

  EXPECT_EQ(7, ss);
  EXPECT_EQ(500000, mics);
}

TEST_F(Quantity_PeriodTest, SubtractNegativeWithMicroseconds)
{
  Quantity_Period aPeriod1(0, 0, 0, 5, 0, 300000);
  Quantity_Period aPeriod2(0, 0, 0, 8, 0, 100000);

  Quantity_Period aResult = aPeriod1.Subtract(aPeriod2);

  int ss, mics;
  aResult.Values(ss, mics);

  EXPECT_EQ(2, ss);
  EXPECT_EQ(800000, mics);
}
