

#include <gtest/gtest.h>

#include <type_traits>

#include <BRepAlgoAPI_BuilderAlgo.hpp>
#include <BRepAlgoAPI_BooleanOperation.hpp>
#include <BRepAlgoAPI_Cut.hpp>
#include <BRepAlgoAPI_Fuse.hpp>
#include <BRepAlgoAPI_Common.hpp>
#include <BRepAlgoAPI_Section.hpp>
#include <BRepAlgoAPI_Splitter.hpp>

TEST(BRepAlgoAPI_BuilderAlgoTest, NotCopyConstructible)
{
  EXPECT_FALSE(std::is_copy_constructible<BRepAlgoAPI_BuilderAlgo>::value);
}

TEST(BRepAlgoAPI_BuilderAlgoTest, NotCopyAssignable)
{
  EXPECT_FALSE(std::is_copy_assignable<BRepAlgoAPI_BuilderAlgo>::value);
}

TEST(BRepAlgoAPI_BuilderAlgoTest, NotMoveConstructible)
{
  EXPECT_FALSE(std::is_move_constructible<BRepAlgoAPI_BuilderAlgo>::value);
}

TEST(BRepAlgoAPI_BuilderAlgoTest, NotMoveAssignable)
{
  EXPECT_FALSE(std::is_move_assignable<BRepAlgoAPI_BuilderAlgo>::value);
}

TEST(BRepAlgoAPI_BooleanOperationTest, NotCopyConstructible)
{
  EXPECT_FALSE(std::is_copy_constructible<BRepAlgoAPI_BooleanOperation>::value);
}

TEST(BRepAlgoAPI_CutTest, NotCopyConstructible)
{
  EXPECT_FALSE(std::is_copy_constructible<BRepAlgoAPI_Cut>::value);
}

TEST(BRepAlgoAPI_FuseTest, NotCopyConstructible)
{
  EXPECT_FALSE(std::is_copy_constructible<BRepAlgoAPI_Fuse>::value);
}

TEST(BRepAlgoAPI_CommonTest, NotCopyConstructible)
{
  EXPECT_FALSE(std::is_copy_constructible<BRepAlgoAPI_Common>::value);
}

TEST(BRepAlgoAPI_SectionTest, NotCopyConstructible)
{
  EXPECT_FALSE(std::is_copy_constructible<BRepAlgoAPI_Section>::value);
}

TEST(BRepAlgoAPI_SplitterTest, NotCopyConstructible)
{
  EXPECT_FALSE(std::is_copy_constructible<BRepAlgoAPI_Splitter>::value);
}
