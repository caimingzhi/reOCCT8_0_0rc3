

#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>

#include <gtest/gtest.h>

TEST(TopoDS_Iterator_Test, OCC30708_1_InitializeWithNullShape)
{
  TopoDS_Iterator it;
  TopoDS_Shape    empty;

  EXPECT_NO_THROW(it.Initialize(empty));

  EXPECT_FALSE(it.More());
}
