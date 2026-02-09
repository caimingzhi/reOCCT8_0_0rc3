

#include <UnitsAPI.hpp>

#include <gtest/gtest.h>

TEST(UnitsAPI_Test, BUC60727_AnyToLS_Conversion)
{

  UnitsAPI::SetLocalSystem(UnitsAPI_MDTV);

  double aResult = UnitsAPI::AnyToLS(3.0, "mm");
  EXPECT_DOUBLE_EQ(3.0, aResult);
}
