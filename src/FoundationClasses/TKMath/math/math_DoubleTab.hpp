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
  //! Constructor for ranges [theLowerRow..theUpperRow, theLowerCol..theUpperCol]
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
  //! Constructor from external data array
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

  //! Initialize all elements with theInitValue
  void Init(const double theInitValue) { myArray.Init(theInitValue); }

  //! Copy constructor
  math_DoubleTab(const math_DoubleTab& theOther)
      : myArray(theOther.myArray)
  {
  }

  //! Move constructor
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

  //! Copy data to theOther
  void Copy(math_DoubleTab& theOther) const { theOther.myArray.Assign(myArray); }

  //! Returns true if the internal array is deletable (heap-allocated)
  bool IsDeletable() const { return myArray.IsDeletable(); }

  //! Set lower row index
  void SetLowerRow(const int theLowerRow) { myArray.UpdateLowerRow(theLowerRow); }

  //! Set lower column index
  void SetLowerCol(const int theLowerCol) { myArray.UpdateLowerCol(theLowerCol); }

  //! Get lower row index
  int LowerRow() const noexcept { return myArray.LowerRow(); }

  //! Get upper row index
  int UpperRow() const noexcept { return myArray.UpperRow(); }

  //! Get lower column index
  int LowerCol() const noexcept { return myArray.LowerCol(); }

  //! Get upper column index
  int UpperCol() const noexcept { return myArray.UpperCol(); }

  //! Get number of rows
  int NbRows() const noexcept { return myArray.NbRows(); }

  //! Get number of columns
  int NbColumns() const noexcept { return myArray.NbColumns(); }

  //! Access element at (theRowIndex, theColIndex)
  const double& Value(const int theRowIndex, const int theColIndex) const
  {
    return myArray.Value(theRowIndex, theColIndex);
  }

  //! Change element at (theRowIndex, theColIndex)
  double& Value(const int theRowIndex, const int theColIndex)
  {
    return myArray.ChangeValue(theRowIndex, theColIndex);
  }

  //! Operator() - alias to Value
  const double& operator()(const int theRowIndex, const int theColIndex) const
  {
    return Value(theRowIndex, theColIndex);
  }

  //! Operator() - alias to ChangeValue
  double& operator()(const int theRowIndex, const int theColIndex)
  {
    return Value(theRowIndex, theColIndex);
  }

  //! Assignment operator
  math_DoubleTab& operator=(const math_DoubleTab& theOther)
  {
    if (this != &theOther)
    {
      myArray = theOther.myArray;
    }
    return *this;
  }

  //! Move assignment operator
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

  //! Destructor
  ~math_DoubleTab() = default;

private:
  std::array<double, THE_BUFFER_SIZE> myBuffer;
  NCollection_Array2<double>          myArray;
};

