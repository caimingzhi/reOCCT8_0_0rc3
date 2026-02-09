

#include <Standard_Transient.hpp>
#include <Standard_Handle.hpp>

#include <gtest/gtest.h>

TEST(Standard_Handle_Test, OCC24533_IsNullAndPointerChecks)
{
  occ::handle<Standard_Transient> aHandle;

  EXPECT_TRUE(aHandle.IsNull());

  const Standard_Transient* p = aHandle.get();
  EXPECT_FALSE(static_cast<bool>(p));
  EXPECT_EQ(nullptr, p);

  aHandle = new Standard_Transient();

  EXPECT_FALSE(aHandle.IsNull());

  p = aHandle.get();
  EXPECT_TRUE(static_cast<bool>(p));
  EXPECT_NE(nullptr, p);
}
