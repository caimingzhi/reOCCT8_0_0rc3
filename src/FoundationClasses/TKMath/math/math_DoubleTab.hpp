#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <NCollection_Array2.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>

#include <array>
#include <utility>

class math_DoubleTab
{
  static const int THE_BUFFER_SIZE = 64;

public:
  DEFINE_STANDARD_ALLOC;
  DEFINE_NCOLLECTION_ALLOC;

public:
  math_DoubleTab(const int theLowerRow,
                 const int theUpperRow,
                 const int theLowerCol,
                 const int theUpperCol)
      : myBuffer{},
        myArray((theUpperRow - theLowerRow + 1) * (theUpperCol - theLowerCol + 1) <= THE_BUFFER_SIZE
                  ? NCollection_Array2<double>(*myBuffer.data(),
                                               theLowerRow,
                                               theUpperRow,
                                               theLowerCol,
                                               theUpperCol)
                  : NCollection_Array2<double>(theLowerRow, theUpperRow, theLowerCol, theUpperCol))
  {
  }

public:
  math_DoubleTab(void* const theTab,
                 const int   theLowerRow,
                 const int   theUpperRow,
                 const int   theLowerCol,
                 const int   theUpperCol)
      : myArray(*static_cast<const double*>(theTab),
                theLowerRow,
                theUpperRow,
                theLowerCol,
                theUpperCol)
  {
  }

  void Init(const double theInitValue) { myArray.Init(theInitValue); }

  math_DoubleTab(const math_DoubleTab& theOther)
      : myArray(theOther.myArray)
  {
  }

  math_DoubleTab(math_DoubleTab&& theOther) noexcept
      : myBuffer{},
        myArray(theOther.myArray.IsDeletable()
                  ? std::move(theOther.myArray)
                  : (theOther.NbRows() * theOther.NbColumns() <= THE_BUFFER_SIZE
                       ? NCollection_Array2<double>(*myBuffer.data(),
                                                    theOther.LowerRow(),
                                                    theOther.UpperRow(),
                                                    theOther.LowerCol(),
                                                    theOther.UpperCol())
                       : NCollection_Array2<double>(theOther.LowerRow(),
                                                    theOther.UpperRow(),
                                                    theOther.LowerCol(),
                                                    theOther.UpperCol())))
  {
    if (!theOther.myArray.IsEmpty())
    {
      myArray.Assign(theOther.myArray);
    }
  }

  void Copy(math_DoubleTab& theOther) const { theOther.myArray.Assign(myArray); }

  bool IsDeletable() const { return myArray.IsDeletable(); }

  void SetLowerRow(const int theLowerRow) { myArray.UpdateLowerRow(theLowerRow); }

  void SetLowerCol(const int theLowerCol) { myArray.UpdateLowerCol(theLowerCol); }

  int LowerRow() const noexcept { return myArray.LowerRow(); }

  int UpperRow() const noexcept { return myArray.UpperRow(); }

  int LowerCol() const noexcept { return myArray.LowerCol(); }

  int UpperCol() const noexcept { return myArray.UpperCol(); }

  int NbRows() const noexcept { return myArray.NbRows(); }

  int NbColumns() const noexcept { return myArray.NbColumns(); }

  const double& Value(const int theRowIndex, const int theColIndex) const
  {
    return myArray.Value(theRowIndex, theColIndex);
  }

  double& Value(const int theRowIndex, const int theColIndex)
  {
    return myArray.ChangeValue(theRowIndex, theColIndex);
  }

  const double& operator()(const int theRowIndex, const int theColIndex) const
  {
    return Value(theRowIndex, theColIndex);
  }

  double& operator()(const int theRowIndex, const int theColIndex)
  {
    return Value(theRowIndex, theColIndex);
  }

  math_DoubleTab& operator=(const math_DoubleTab& theOther)
  {
    if (this != &theOther)
    {
      myArray = theOther.myArray;
    }
    return *this;
  }

  math_DoubleTab& operator=(math_DoubleTab&& theOther) noexcept
  {
    if (this == &theOther)
    {
      return *this;
    }

    if (myArray.IsDeletable() && theOther.myArray.IsDeletable()
        && myArray.NbRows() == theOther.myArray.NbRows()
        && myArray.NbColumns() == theOther.myArray.NbColumns()
        && myArray.LowerRow() == theOther.myArray.LowerRow()
        && myArray.LowerCol() == theOther.myArray.LowerCol())
    {
      myArray.Move(theOther.myArray);
    }
    else
    {
      myArray = theOther.myArray;
    }
    return *this;
  }

  ~math_DoubleTab() = default;

private:
  std::array<double, THE_BUFFER_SIZE> myBuffer;
  NCollection_Array2<double>          myArray;
};
