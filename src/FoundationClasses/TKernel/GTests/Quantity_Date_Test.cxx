

#include <Quantity_Date.hpp>
#include <Quantity_Period.hpp>

#include <gtest/gtest.h>

class Quantity_DateTest : public testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(Quantity_DateTest, BasicConstruction)
{

  Quantity_Date aDate1;
  int           mm, dd, yy, hh, mn, ss, mis, mics;
  aDate1.Values(mm, dd, yy, hh, mn, ss, mis, mics);

  EXPECT_EQ(1, mm);
  EXPECT_EQ(1, dd);
  EXPECT_EQ(1979, yy);
  EXPECT_EQ(0, hh);
  EXPECT_EQ(0, mn);
  EXPECT_EQ(0, ss);

  Quantity_Date aDate2(6, 15, 2025, 14, 30, 45, 123, 456);
  aDate2.Values(mm, dd, yy, hh, mn, ss, mis, mics);

  EXPECT_EQ(6, mm);
  EXPECT_EQ(15, dd);
  EXPECT_EQ(2025, yy);
  EXPECT_EQ(14, hh);
  EXPECT_EQ(30, mn);
  EXPECT_EQ(45, ss);
  EXPECT_EQ(123, mis);
  EXPECT_EQ(456, mics);
}

TEST_F(Quantity_DateTest, ConstexprComparisons)
{
  Quantity_Date aDate1(1, 1, 2020, 0, 0, 0, 0, 0);
  Quantity_Date aDate2(1, 1, 2020, 0, 0, 0, 0, 0);
  Quantity_Date aDate3(1, 2, 2020, 0, 0, 0, 0, 0);

  EXPECT_TRUE(aDate1.IsEqual(aDate2));
  EXPECT_FALSE(aDate1.IsEqual(aDate3));

  EXPECT_TRUE(aDate1.IsEarlier(aDate3));
  EXPECT_FALSE(aDate3.IsEarlier(aDate1));
  EXPECT_FALSE(aDate1.IsEarlier(aDate2));

  EXPECT_TRUE(aDate3.IsLater(aDate1));
  EXPECT_FALSE(aDate1.IsLater(aDate3));
  EXPECT_FALSE(aDate1.IsLater(aDate2));
}

TEST_F(Quantity_DateTest, LeapYearDetection)
{

  EXPECT_TRUE(Quantity_Date::IsLeap(2000));
  EXPECT_TRUE(Quantity_Date::IsLeap(2004));
  EXPECT_TRUE(Quantity_Date::IsLeap(2020));

  EXPECT_FALSE(Quantity_Date::IsLeap(1900));
  EXPECT_FALSE(Quantity_Date::IsLeap(2001));
  EXPECT_FALSE(Quantity_Date::IsLeap(2100));
}

TEST_F(Quantity_DateTest, ValidationWithLeapYear)
{

  EXPECT_TRUE(Quantity_Date::IsValid(2, 29, 2020, 0, 0, 0, 0, 0));

  EXPECT_FALSE(Quantity_Date::IsValid(2, 29, 2019, 0, 0, 0, 0, 0));

  EXPECT_TRUE(Quantity_Date::IsValid(2, 28, 2019, 0, 0, 0, 0, 0));
  EXPECT_TRUE(Quantity_Date::IsValid(2, 28, 2020, 0, 0, 0, 0, 0));
}

TEST_F(Quantity_DateTest, MonthBoundaries)
{

  EXPECT_TRUE(Quantity_Date::IsValid(1, 31, 2020, 0, 0, 0, 0, 0));
  EXPECT_FALSE(Quantity_Date::IsValid(1, 32, 2020, 0, 0, 0, 0, 0));

  EXPECT_TRUE(Quantity_Date::IsValid(4, 30, 2020, 0, 0, 0, 0, 0));
  EXPECT_FALSE(Quantity_Date::IsValid(4, 31, 2020, 0, 0, 0, 0, 0));

  EXPECT_TRUE(Quantity_Date::IsValid(12, 31, 2020, 0, 0, 0, 0, 0));
  EXPECT_FALSE(Quantity_Date::IsValid(12, 32, 2020, 0, 0, 0, 0, 0));
}

TEST_F(Quantity_DateTest, TimeValidation)
{

  EXPECT_TRUE(Quantity_Date::IsValid(1, 1, 2020, 23, 59, 59, 999, 999));
  EXPECT_TRUE(Quantity_Date::IsValid(1, 1, 2020, 0, 0, 0, 0, 0));

  EXPECT_FALSE(Quantity_Date::IsValid(1, 1, 2020, 24, 0, 0, 0, 0));
  EXPECT_FALSE(Quantity_Date::IsValid(1, 1, 2020, -1, 0, 0, 0, 0));

  EXPECT_FALSE(Quantity_Date::IsValid(1, 1, 2020, 0, 60, 0, 0, 0));
  EXPECT_FALSE(Quantity_Date::IsValid(1, 1, 2020, 0, -1, 0, 0, 0));

  EXPECT_FALSE(Quantity_Date::IsValid(1, 1, 2020, 0, 0, 60, 0, 0));
  EXPECT_FALSE(Quantity_Date::IsValid(1, 1, 2020, 0, 0, -1, 0, 0));

  EXPECT_FALSE(Quantity_Date::IsValid(1, 1, 2020, 0, 0, 0, 1000, 0));
  EXPECT_FALSE(Quantity_Date::IsValid(1, 1, 2020, 0, 0, 0, -1, 0));

  EXPECT_FALSE(Quantity_Date::IsValid(1, 1, 2020, 0, 0, 0, 0, 1000));
  EXPECT_FALSE(Quantity_Date::IsValid(1, 1, 2020, 0, 0, 0, 0, -1));
}

TEST_F(Quantity_DateTest, SetValuesRoundTrip)
{
  Quantity_Date aDate;
  aDate.SetValues(3, 15, 2021, 10, 25, 30, 500, 750);

  int mm, dd, yy, hh, mn, ss, mis, mics;
  aDate.Values(mm, dd, yy, hh, mn, ss, mis, mics);

  EXPECT_EQ(3, mm);
  EXPECT_EQ(15, dd);
  EXPECT_EQ(2021, yy);
  EXPECT_EQ(10, hh);
  EXPECT_EQ(25, mn);
  EXPECT_EQ(30, ss);
  EXPECT_EQ(500, mis);
  EXPECT_EQ(750, mics);
}

TEST_F(Quantity_DateTest, IndividualGetters)
{

  Quantity_Date aDate1(1, 2, 1979, 0, 0, 0, 0, 0);
  EXPECT_EQ(1, aDate1.Month());
  EXPECT_EQ(2, aDate1.Day());
  EXPECT_EQ(1979, aDate1.Year());

  Quantity_Date aDate2(7, 20, 2024, 0, 0, 0, 0, 0);
  EXPECT_EQ(7, aDate2.Month());
  EXPECT_EQ(20, aDate2.Day());
  EXPECT_EQ(2024, aDate2.Year());

  Quantity_Date aDate3(7, 20, 2024, 15, 45, 30, 123, 456);
  EXPECT_EQ(7, aDate3.Month());
  EXPECT_EQ(20, aDate3.Day());
  EXPECT_EQ(2024, aDate3.Year());
  EXPECT_EQ(15, aDate3.Hour());
  EXPECT_EQ(45, aDate3.Minute());
  EXPECT_EQ(30, aDate3.Second());
  EXPECT_EQ(123, aDate3.MilliSecond());
  EXPECT_EQ(456, aDate3.MicroSecond());
}

TEST_F(Quantity_DateTest, DateDifference)
{
  Quantity_Date aDate1(1, 1, 2020, 0, 0, 0, 0, 0);
  Quantity_Date aDate2(1, 1, 2020, 1, 0, 0, 0, 0);

  Quantity_Period aPeriod = aDate2.Difference(aDate1);

  int ss, mics;
  aPeriod.Values(ss, mics);

  EXPECT_EQ(3600, ss);
  EXPECT_EQ(0, mics);
}

TEST_F(Quantity_DateTest, AddPeriod)
{
  Quantity_Date   aDate(1, 1, 2020, 0, 0, 0, 0, 0);
  Quantity_Period aPeriod(1, 0, 0, 0, 0, 0);

  Quantity_Date aNewDate = aDate.Add(aPeriod);

  int mm, dd, yy, hh, mn, ss, mis, mics;
  aNewDate.Values(mm, dd, yy, hh, mn, ss, mis, mics);

  EXPECT_EQ(1, mm);
  EXPECT_EQ(2, dd);
  EXPECT_EQ(2020, yy);
}

TEST_F(Quantity_DateTest, SubtractPeriod)
{
  Quantity_Date   aDate(1, 2, 2020, 0, 0, 0, 0, 0);
  Quantity_Period aPeriod(1, 0, 0, 0, 0, 0);

  Quantity_Date aNewDate = aDate.Subtract(aPeriod);

  int mm, dd, yy, hh, mn, ss, mis, mics;
  aNewDate.Values(mm, dd, yy, hh, mn, ss, mis, mics);

  EXPECT_EQ(1, mm);
  EXPECT_EQ(1, dd);
  EXPECT_EQ(2020, yy);
}

TEST_F(Quantity_DateTest, YearBoundary)
{
  Quantity_Date   aDate(12, 31, 2020, 23, 59, 59, 0, 0);
  Quantity_Period aPeriod(0, 0, 0, 1, 0, 0);

  Quantity_Date aNewDate = aDate.Add(aPeriod);

  int mm, dd, yy, hh, mn, ss, mis, mics;
  aNewDate.Values(mm, dd, yy, hh, mn, ss, mis, mics);

  EXPECT_EQ(1, mm);
  EXPECT_EQ(1, dd);
  EXPECT_EQ(2021, yy);
  EXPECT_EQ(0, hh);
  EXPECT_EQ(0, mn);
  EXPECT_EQ(0, ss);
}

TEST_F(Quantity_DateTest, LeapYearBoundary)
{

  Quantity_Date   aDate1(2, 28, 2020, 0, 0, 0, 0, 0);
  Quantity_Period aPeriod1(1, 0, 0, 0, 0, 0);
  Quantity_Date   aNewDate1 = aDate1.Add(aPeriod1);

  int mm, dd, yy, hh, mn, ss, mis, mics;
  aNewDate1.Values(mm, dd, yy, hh, mn, ss, mis, mics);

  EXPECT_EQ(2, mm);
  EXPECT_EQ(29, dd);
  EXPECT_EQ(2020, yy);

  Quantity_Date   aDate2(2, 28, 2021, 0, 0, 0, 0, 0);
  Quantity_Period aPeriod2(1, 0, 0, 0, 0, 0);
  Quantity_Date   aNewDate2 = aDate2.Add(aPeriod2);

  aNewDate2.Values(mm, dd, yy, hh, mn, ss, mis, mics);

  EXPECT_EQ(3, mm);
  EXPECT_EQ(1, dd);
  EXPECT_EQ(2021, yy);
}

TEST_F(Quantity_DateTest, MicrosecondOverflow)
{
  Quantity_Date   aDate(1, 1, 2020, 0, 0, 0, 999, 999);
  Quantity_Period aPeriod(0, 0, 0, 0, 0, 1);

  Quantity_Date aNewDate = aDate.Add(aPeriod);

  int mm, dd, yy, hh, mn, ss, mis, mics;
  aNewDate.Values(mm, dd, yy, hh, mn, ss, mis, mics);

  EXPECT_EQ(1, mm);
  EXPECT_EQ(1, dd);
  EXPECT_EQ(2020, yy);
  EXPECT_EQ(0, hh);
  EXPECT_EQ(0, mn);
  EXPECT_EQ(1, ss);
  EXPECT_EQ(0, mis);
  EXPECT_EQ(0, mics);
}

TEST_F(Quantity_DateTest, SpecificDateCalculations)
{

  Quantity_Date   aDate1(1, 1, 2020, 0, 0, 0, 0, 0);
  Quantity_Period aPeriod24h(0, 24, 0, 0, 0, 0);

  Quantity_Date aDate2 = aDate1.Add(aPeriod24h);

  int mm, dd, yy, hh, mn, ss, mis, mics;
  aDate2.Values(mm, dd, yy, hh, mn, ss, mis, mics);

  EXPECT_EQ(1, mm);
  EXPECT_EQ(2, dd);
  EXPECT_EQ(2020, yy);
  EXPECT_EQ(0, hh);
}

TEST_F(Quantity_DateTest, MinimumDate)
{
  EXPECT_TRUE(Quantity_Date::IsValid(1, 1, 1979, 0, 0, 0, 0, 0));
  EXPECT_FALSE(Quantity_Date::IsValid(12, 31, 1978, 23, 59, 59, 999, 999));
}

TEST_F(Quantity_DateTest, MultipleLeapYearChecks)
{

  for (int year = 2000; year <= 2024; ++year)
  {
    for (int month = 1; month <= 12; ++month)
    {
      int maxDay;
      if (month == 2)
      {
        maxDay = Quantity_Date::IsLeap(year) ? 29 : 28;
      }
      else if (month == 4 || month == 6 || month == 9 || month == 11)
      {
        maxDay = 30;
      }
      else
      {
        maxDay = 31;
      }

      EXPECT_TRUE(Quantity_Date::IsValid(month, maxDay, year, 0, 0, 0, 0, 0));
      EXPECT_FALSE(Quantity_Date::IsValid(month, maxDay + 1, year, 0, 0, 0, 0, 0));
    }
  }
}

TEST_F(Quantity_DateTest, DifferenceFromEpoch)
{
  Quantity_Date aEpoch;
  Quantity_Date aDate(1, 2, 1979, 0, 0, 0, 0, 0);

  Quantity_Period aPeriod = aEpoch.Difference(aDate);

  int ss, mics;
  aPeriod.Values(ss, mics);

  EXPECT_EQ(86400, ss);
  EXPECT_EQ(0, mics);
}

TEST_F(Quantity_DateTest, DifferenceWithMicrosecondUnderflow)
{
  Quantity_Date aDate1(1, 1, 2020, 0, 0, 1, 200, 0);
  Quantity_Date aDate2(1, 1, 2020, 0, 0, 0, 500, 0);

  Quantity_Period aPeriod = aDate1.Difference(aDate2);

  int ss, mics;
  aPeriod.Values(ss, mics);

  EXPECT_EQ(0, ss);
  EXPECT_EQ(700000, mics);
}

TEST_F(Quantity_DateTest, DifferenceReversed)
{
  Quantity_Date aDate1(1, 1, 2020, 1, 0, 0, 0, 0);
  Quantity_Date aDate2(1, 1, 2020, 3, 0, 0, 0, 0);

  Quantity_Period aPeriod = aDate1.Difference(aDate2);

  int ss, mics;
  aPeriod.Values(ss, mics);

  EXPECT_EQ(7200, ss);
  EXPECT_EQ(0, mics);
}
