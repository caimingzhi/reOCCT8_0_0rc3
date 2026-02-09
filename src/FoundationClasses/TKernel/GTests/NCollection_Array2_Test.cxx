

#include <NCollection_Array2.hpp>
#include <Standard_Integer.hpp>

#include <gtest/gtest.h>

TEST(NCollection_Array2Test, DefaultConstructor)
{
  NCollection_Array2<int> anArray;
  EXPECT_EQ(0, anArray.Length());
  EXPECT_EQ(0, anArray.NbRows());
  EXPECT_EQ(0, anArray.NbColumns());
}

TEST(NCollection_Array2Test, ConstructorWithBounds)
{
  NCollection_Array2<int> anArray(1, 5, 1, 10);
  EXPECT_EQ(50, anArray.Length());
  EXPECT_EQ(5, anArray.NbRows());
  EXPECT_EQ(10, anArray.NbColumns());
  EXPECT_EQ(1, anArray.LowerRow());
  EXPECT_EQ(5, anArray.UpperRow());
  EXPECT_EQ(1, anArray.LowerCol());
  EXPECT_EQ(10, anArray.UpperCol());
}

TEST(NCollection_Array2Test, ConstructorWithNegativeBounds)
{
  NCollection_Array2<int> anArray(-2, 2, -5, 5);
  EXPECT_EQ(55, anArray.Length());
  EXPECT_EQ(5, anArray.NbRows());
  EXPECT_EQ(11, anArray.NbColumns());
  EXPECT_EQ(-2, anArray.LowerRow());
  EXPECT_EQ(2, anArray.UpperRow());
  EXPECT_EQ(-5, anArray.LowerCol());
  EXPECT_EQ(5, anArray.UpperCol());
}

TEST(NCollection_Array2Test, ValueAccess)
{
  NCollection_Array2<int> anArray(1, 3, 1, 4);
  for (int aRowIter = anArray.LowerRow(); aRowIter <= anArray.UpperRow(); ++aRowIter)
  {
    for (int aColIter = anArray.LowerCol(); aColIter <= anArray.UpperCol(); ++aColIter)
    {
      anArray.SetValue(aRowIter, aColIter, aRowIter * 100 + aColIter);
    }
  }

  for (int aRowIter = anArray.LowerRow(); aRowIter <= anArray.UpperRow(); ++aRowIter)
  {
    for (int aColIter = anArray.LowerCol(); aColIter <= anArray.UpperCol(); ++aColIter)
    {
      EXPECT_EQ(aRowIter * 100 + aColIter, anArray.Value(aRowIter, aColIter));
      EXPECT_EQ(aRowIter * 100 + aColIter, anArray(aRowIter, aColIter));
    }
  }
}

TEST(NCollection_Array2Test, ChangeValueAccess)
{
  NCollection_Array2<int> anArray(0, 2, 0, 3);
  for (int aRowIter = anArray.LowerRow(); aRowIter <= anArray.UpperRow(); ++aRowIter)
  {
    for (int aColIter = anArray.LowerCol(); aColIter <= anArray.UpperCol(); ++aColIter)
    {
      anArray.ChangeValue(aRowIter, aColIter) = aRowIter * 100 + aColIter;
    }
  }

  EXPECT_EQ(102, anArray(1, 2));

  anArray.ChangeValue(1, 2) = 999;
  EXPECT_EQ(999, anArray(1, 2));
}

TEST(NCollection_Array2Test, Init)
{
  NCollection_Array2<int> anArray(1, 5, 1, 5);
  anArray.Init(42);
  for (int aRowIter = anArray.LowerRow(); aRowIter <= anArray.UpperRow(); ++aRowIter)
  {
    for (int aColIter = anArray.LowerCol(); aColIter <= anArray.UpperCol(); ++aColIter)
    {
      EXPECT_EQ(42, anArray(aRowIter, aColIter));
    }
  }
}

TEST(NCollection_Array2Test, CopyConstructor)
{
  NCollection_Array2<int> anArray1(1, 3, 1, 4);
  anArray1.Init(123);

  NCollection_Array2<int> anArray2(anArray1);

  EXPECT_EQ(anArray1.Length(), anArray2.Length());
  EXPECT_EQ(anArray1.NbRows(), anArray2.NbRows());
  EXPECT_EQ(anArray1.NbColumns(), anArray2.NbColumns());
  EXPECT_EQ(anArray1(2, 3), anArray2(2, 3));

  anArray1.SetValue(2, 3, 999);
  EXPECT_EQ(123, anArray2(2, 3));
  EXPECT_NE(anArray1(2, 3), anArray2(2, 3));
}

TEST(NCollection_Array2Test, AssignmentOperator)
{
  NCollection_Array2<int> anArray1(1, 3, 1, 4);
  anArray1.Init(123);

  NCollection_Array2<int> anArray2(1, 3, 1, 4);
  anArray2.Init(0);

  anArray2 = anArray1;

  EXPECT_EQ(123, anArray2(2, 3));

  anArray1.SetValue(2, 3, 999);
  EXPECT_EQ(123, anArray2(2, 3));
}

TEST(NCollection_Array2Test, MoveConstructor)
{
  NCollection_Array2<int> anArray1(1, 5, 1, 10);
  anArray1.SetValue(3, 7, 123);

  NCollection_Array2<int> anArray2(std::move(anArray1));

  EXPECT_EQ(50, anArray2.Length());
  EXPECT_EQ(5, anArray2.NbRows());
  EXPECT_EQ(10, anArray2.NbColumns());
  EXPECT_EQ(1, anArray2.LowerRow());
  EXPECT_EQ(10, anArray2.UpperCol());
  EXPECT_EQ(123, anArray2(3, 7));

  EXPECT_EQ(0, anArray1.Length());
  EXPECT_EQ(0, anArray1.NbRows());
}

TEST(NCollection_Array2Test, MoveAssignment)
{
  NCollection_Array2<int> anArray1(1, 5, 1, 10);
  anArray1.SetValue(3, 7, 123);

  NCollection_Array2<int> anArray2;
  anArray2 = std::move(anArray1);

  EXPECT_EQ(50, anArray2.Length());
  EXPECT_EQ(5, anArray2.NbRows());
  EXPECT_EQ(123, anArray2(3, 7));

  EXPECT_EQ(0, anArray1.Length());
}

TEST(NCollection_Array2Test, Resize)
{
  NCollection_Array2<int> anArray(1, 4, 1, 5);
  for (int aRowIter = 1; aRowIter <= 4; ++aRowIter)
  {
    for (int aColIter = 1; aColIter <= 5; ++aColIter)
    {
      anArray(aRowIter, aColIter) = aRowIter * 100 + aColIter;
    }
  }

  anArray.Resize(0, 5, 0, 6, true);

  EXPECT_EQ(6, anArray.NbRows());
  EXPECT_EQ(7, anArray.NbColumns());
  EXPECT_EQ(0, anArray.LowerRow());
  EXPECT_EQ(6, anArray.UpperCol());

  for (int aRowIter = 0; aRowIter <= 3; ++aRowIter)
  {
    for (int aColIter = 0; aColIter <= 4; ++aColIter)
    {
      EXPECT_EQ((aRowIter + 1) * 100 + (aColIter + 1), anArray(aRowIter, aColIter));
    }
  }
}

TEST(NCollection_Array2Test, ReIndex_UpdateBounds)
{
  NCollection_Array2<int> anArray(1, 5, 1, 10);

  anArray.UpdateLowerRow(0);
  anArray.UpdateLowerCol(0);
  EXPECT_EQ(0, anArray.LowerRow());
  EXPECT_EQ(4, anArray.UpperRow());
  EXPECT_EQ(0, anArray.LowerCol());
  EXPECT_EQ(9, anArray.UpperCol());
  EXPECT_EQ(5, anArray.NbRows());
  EXPECT_EQ(10, anArray.NbColumns());

  anArray.UpdateUpperRow(10);
  anArray.UpdateUpperCol(20);
  EXPECT_EQ(10, anArray.UpperRow());
  EXPECT_EQ(20, anArray.UpperCol());
  EXPECT_EQ(6, anArray.LowerRow());
  EXPECT_EQ(11, anArray.LowerCol());
  EXPECT_EQ(5, anArray.NbRows());
  EXPECT_EQ(10, anArray.NbColumns());
}

TEST(NCollection_Array2Test, STLIteration)
{
  NCollection_Array2<int> anArray(1, 2, 1, 3);
  for (int aRowIter = 1; aRowIter <= 2; ++aRowIter)
  {
    for (int aColIter = 1; aColIter <= 3; ++aColIter)
    {
      anArray(aRowIter, aColIter) = aRowIter * 10 + aColIter;
    }
  }

  std::vector<int> aExpectedValues = {11, 12, 13, 21, 22, 23};
  int              anIndex         = 0;
  for (const auto& aValue : anArray)
  {
    EXPECT_EQ(aExpectedValues[anIndex++], aValue);
  }
  EXPECT_EQ(6, anIndex);
}

TEST(NCollection_Array2Test, Resize_ChangeShapeSameSize)
{

  NCollection_Array2<int> anArray(1, 4, 1, 6);
  int                     anExpectedValue = 0;
  for (int aRowIter = 1; aRowIter <= 4; ++aRowIter)
  {
    for (int aColIter = 1; aColIter <= 6; ++aColIter)
    {
      anArray(aRowIter, aColIter) = anExpectedValue++;
    }
  }

  anArray.Resize(1, 6, 1, 4, true);

  EXPECT_EQ(6, anArray.NbRows());
  EXPECT_EQ(4, anArray.NbColumns());
  EXPECT_EQ(24, anArray.Length());

  for (int anElemInd = anArray.Lower(); anElemInd < anArray.Lower() + 16; ++anElemInd)
  {
    EXPECT_EQ(anElemInd - anArray.Lower(),
              static_cast<NCollection_Array1<int>&>(anArray).Value(anElemInd));
  }
}

TEST(NCollection_Array2Test, ReIndex_Interference)
{

  NCollection_Array2<int> anArray(1, 10, 1, 1);
  const int               anInitialNbRows = anArray.NbRows();

  anArray.UpdateLowerRow(5);
  EXPECT_EQ(5, anArray.LowerRow());
  EXPECT_EQ(14, anArray.UpperRow());

  anArray.UpdateUpperRow(12);

  EXPECT_EQ(12, anArray.UpperRow());

  EXPECT_EQ(3, anArray.LowerRow());
  EXPECT_NE(5, anArray.LowerRow());

  EXPECT_EQ(anInitialNbRows, anArray.NbRows());
}
