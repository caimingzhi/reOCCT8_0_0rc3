

#include <BRepLib_MakeWire.hpp>
#include <TopoDS_Wire.hpp>

#include <gtest/gtest.h>

TEST(BRepLib_MakeWire_Test, OCC30708_2_InitializeWithNullWire)
{
  TopoDS_Wire empty;

  EXPECT_NO_THROW(BRepLib_MakeWire aWBuilder(empty));
}
