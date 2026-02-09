

#include <Standard_OutOfRange.hpp>

#include <gtest/gtest.h>

#include <sstream>

TEST(Standard_Failure_Test, OCC670_ExceptionWithoutMessage)
{

  bool aCaught = false;
  try
  {
    throw Standard_OutOfRange("test");
  }
  catch (Standard_Failure const& anException)
  {
    aCaught = true;

    std::ostringstream aStream;
    EXPECT_NO_THROW(aStream << anException);

    std::string aMessage = aStream.str();
    EXPECT_FALSE(aMessage.empty()) << "Exception message should not be empty";
  }

  EXPECT_TRUE(aCaught) << "Exception should have been caught";
}
