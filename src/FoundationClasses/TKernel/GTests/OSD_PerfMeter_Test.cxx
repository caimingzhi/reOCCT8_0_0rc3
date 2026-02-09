

#include <gtest/gtest.h>
#include <OSD_PerfMeter.hpp>
#include <TCollection_AsciiString.hpp>

#include <chrono>
#include <thread>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

class OSD_PerfMeterTest : public ::testing::Test
{
protected:
  void SetUp() override { OSD_PerfMeter::ResetALL(); }

  void TearDown() override { OSD_PerfMeter::ResetALL(); }

  static void DoSomeWork(const double theTimeInSec = 0.1)
  {
    OSD_PerfMeter meter("WorkMeter", true);
    while (meter.Elapsed() < theTimeInSec)
    {

      volatile double result = 0.0;
      for (int i = 0; i < 10000; ++i)
      {

        result += std::sin(i * 0.001) * std::cos(i * 0.002);
        result += std::sqrt(i + 1.0);
        result += std::pow(i * 0.1, 1.5);

        TCollection_AsciiString aStr("Test");
        aStr += TCollection_AsciiString(i);
        volatile int len = aStr.Length();
        (void)len;
      }
      (void)result;
    }
    meter.Kill();
  }
};

TEST_F(OSD_PerfMeterTest, BasicCreationWithAutoStart)
{

  OSD_PerfMeter meter("TestMeter", true);

  DoSomeWork();

  meter.Stop();

  double elapsed = meter.Elapsed();
  EXPECT_GT(elapsed, 0.0) << "Elapsed time should be positive";
}

TEST_F(OSD_PerfMeterTest, ManualStartStop)
{

  OSD_PerfMeter meter("ManualMeter", false);

  meter.Start();

  DoSomeWork();

  meter.Stop();

  double elapsed = meter.Elapsed();
  EXPECT_GT(elapsed, 0.0) << "Elapsed time should be positive";
}

TEST_F(OSD_PerfMeterTest, DefaultConstructorAndInit)
{

  OSD_PerfMeter meter;

  meter.Init("InitializedMeter");

  meter.Start();

  DoSomeWork();

  meter.Stop();
  EXPECT_GT(meter.Elapsed(), 0.0) << "Initialized meter should have positive elapsed time";
}

TEST_F(OSD_PerfMeterTest, SharedMetersByName)
{
  const char* meterName = "SharedMeter";

  OSD_PerfMeter meter1(meterName);

  DoSomeWork();

  OSD_PerfMeter meter2;
  meter2.Init(meterName);

  DoSomeWork();

  meter1.Stop();

  double elapsed = meter1.Elapsed();
  EXPECT_GT(elapsed, 0.0) << "Elapsed time should be positive";

  meter2.Stop();
  double elapsed2 = meter2.Elapsed();
  EXPECT_DOUBLE_EQ(elapsed, elapsed2) << "Both meter instances should show same elapsed time";
}

TEST_F(OSD_PerfMeterTest, RestartMeter)
{

  OSD_PerfMeter meter("RestartMeter");

  DoSomeWork(0.1);

  meter.Stop();
  double elapsed1 = meter.Elapsed();
  EXPECT_GT(elapsed1, 0.0) << "First elapsed time should be positive";

  meter.Start();

  DoSomeWork(0.2);

  meter.Stop();
  double elapsed2 = meter.Elapsed();
  EXPECT_GT(elapsed2, 0.0) << "Second elapsed time should be positive";

  EXPECT_NE(elapsed1, elapsed2) << "After restart, elapsed time should be different";
}

TEST_F(OSD_PerfMeterTest, RelativeTimingAccuracy)
{

  OSD_PerfMeter meter1("ShortMeter");
  OSD_PerfMeter meter2("LongMeter");

  DoSomeWork(0.1);
  meter1.Stop();

  DoSomeWork(0.5);
  meter2.Stop();

  double shortElapsed = meter1.Elapsed();
  double longElapsed  = meter2.Elapsed();

  EXPECT_GT(shortElapsed, 0.0) << "Short elapsed time should be positive";
  EXPECT_GT(longElapsed, 0.0) << "Long elapsed time should be positive";
  EXPECT_GT(longElapsed, shortElapsed) << "Long work should take more time than short work";
}

TEST_F(OSD_PerfMeterTest, PrintALL)
{

  OSD_PerfMeter meter1("Meter1");
  DoSomeWork(0.1);
  meter1.Stop();

  OSD_PerfMeter meter2("Meter2");
  DoSomeWork(0.2);
  meter2.Stop();

  OSD_PerfMeter meter3("Meter3");
  DoSomeWork(0.3);
  meter3.Stop();

  std::string output = OSD_PerfMeter::PrintALL().ToCString();

  EXPECT_TRUE(output.find("Meter1") != std::string::npos)
    << "PrintALL output should contain Meter1";
  EXPECT_TRUE(output.find("Meter2") != std::string::npos)
    << "PrintALL output should contain Meter2";
  EXPECT_TRUE(output.find("Meter3") != std::string::npos)
    << "PrintALL output should contain Meter3";
}

TEST_F(OSD_PerfMeterTest, ResetALL)
{

  OSD_PerfMeter meter1("ResetMeter1");
  DoSomeWork(0.1);
  meter1.Stop();

  OSD_PerfMeter meter2("ResetMeter2");
  DoSomeWork(0.2);
  meter2.Stop();

  EXPECT_GT(meter1.Elapsed(), 0.0);
  EXPECT_GT(meter2.Elapsed(), 0.0);

  OSD_PerfMeter::ResetALL();

  EXPECT_EQ(meter1.Elapsed(), 0.0) << "Elapsed time should be zero after ResetALL";
  EXPECT_EQ(meter2.Elapsed(), 0.0) << "Elapsed time should be zero after ResetALL";
}

TEST_F(OSD_PerfMeterTest, UnusedMeter)
{

  OSD_PerfMeter meter("UnusedMeter", false);

  EXPECT_EQ(meter.Elapsed(), 0.0) << "Unused meter should have zero elapsed time, actual";

  meter.Stop();
  EXPECT_EQ(meter.Elapsed(), 0.0) << "Stopping an unused meter should leave elapsed time at zero";
}

TEST_F(OSD_PerfMeterTest, PrintMethod)
{

  const TCollection_AsciiString meterName = "PrintTestMeter";
  OSD_PerfMeter                 meter(meterName);

  DoSomeWork();

  meter.Stop();

  std::string output = meter.Print().ToCString();

  EXPECT_TRUE(output.find(meterName.ToCString()) != std::string::npos)
    << "Print output should contain meter name";

  EXPECT_TRUE(output.find_first_of("0123456789") != std::string::npos)
    << "Print output should contain elapsed time values";

  EXPECT_TRUE(output.find("sec") != std::string::npos)
    << "Print output should contain millisecond units";
}

TEST_F(OSD_PerfMeterTest, KillMethod)
{

  OSD_PerfMeter meter("KillTestMeter");

  DoSomeWork();

  meter.Stop();

  double elapsed = meter.Elapsed();
  EXPECT_GT(elapsed, 0.0) << "Meter should have recorded time before Kill";

  meter.Kill();

  double elapsedAfterKill = meter.Elapsed();
  EXPECT_EQ(elapsedAfterKill, 0.0) << "Elapsed time should be reset after Kill";

  std::string allMeters = OSD_PerfMeter::PrintALL().ToCString();
  EXPECT_TRUE(allMeters.find("KillTestMeter") == std::string::npos)
    << "Killed meter should not appear in PrintALL output";
}

TEST_F(OSD_PerfMeterTest, KillRunningMeter)
{

  OSD_PerfMeter meter("KillRunningMeter");

  meter.Kill();

  double elapsedAfterKill = meter.Elapsed();
  EXPECT_EQ(elapsedAfterKill, 0.0) << "Elapsed time should be reset after Kill";

  meter.Init("KillRunningMeter");
  meter.Start();
  DoSomeWork();
  meter.Stop();

  EXPECT_GT(meter.Elapsed(), 0.0) << "Meter should record time after Kill and restart";
}
