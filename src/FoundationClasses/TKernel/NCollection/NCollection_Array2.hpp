#pragma once

#include <Standard_DimensionMismatch.hpp>
#include <Standard_OutOfMemory.hpp>
#include <NCollection_Allocator.hpp>
#include <Standard_OutOfRange.hpp>
#include <NCollection_Array1.hpp>

#include <NCollection_DefineAlloc.hpp>

template <class TheItemType>
class NCollection_Array2 : public NCollection_Array1<TheItemType>
{
public:
  DEFINE_STANDARD_ALLOC;
  DEFINE_NCOLLECTION_ALLOC;

public:
  typedef NCollection_Allocator<TheItemType> allocator_type;

public:
  using value_type      = typename NCollection_Array1<TheItemType>::value_type;
  using size_type       = typename NCollection_Array1<TheItemType>::size_type;
  using difference_type = typename NCollection_Array1<TheItemType>::difference_type;
  using pointer         = typename NCollection_Array1<TheItemType>::pointer;
  using const_pointer   = typename NCollection_Array1<TheItemType>::const_pointer;
  using reference       = typename NCollection_Array1<TheItemType>::reference;
  using const_reference = typename NCollection_Array1<TheItemType>::const_reference;

  using iterator       = typename NCollection_Array1<TheItemType>::iterator;
  using const_iterator = typename NCollection_Array1<TheItemType>::const_iterator;

  static int BeginPosition(int theRowLower, int, int theColLower, int theColUpper) noexcept
  {

    return theColLower + (theRowLower * (theColUpper - theColLower + 1));
  }

  static int LastPosition(int theRowLower,
                          int theRowUpper,
                          int theColLower,
                          int theColUpper) noexcept
  {
    return ((theRowUpper - theRowLower + 1) * (theColUpper - theColLower + 1)) + theColLower
           + (theRowLower * (theColUpper - theColLower + 1)) - 1;
  }

public:
  NCollection_Array2() noexcept
      : NCollection_Array1<TheItemType>(),
        myLowerRow(1),
        mySizeRow(0),
        myLowerCol(1),
        mySizeCol(0)
  {
  }

  NCollection_Array2(const int theRowLower,
                     const int theRowUpper,
                     const int theColLower,
                     const int theColUpper)
      : NCollection_Array1<TheItemType>(
          BeginPosition(theRowLower, theRowUpper, theColLower, theColUpper),
          LastPosition(theRowLower, theRowUpper, theColLower, theColUpper)),
        myLowerRow(theRowLower),
        mySizeRow(theRowUpper - theRowLower + 1),
        myLowerCol(theColLower),
        mySizeCol(theColUpper - theColLower + 1)
  {
  }

  explicit NCollection_Array2(const allocator_type& theAlloc,
                              const int             theRowLower,
                              const int             theRowUpper,
                              const int             theColLower,
                              const int             theColUpper)
      : NCollection_Array1<TheItemType>(
          theAlloc,
          BeginPosition(theRowLower, theRowUpper, theColLower, theColUpper),
          LastPosition(theRowLower, theRowUpper, theColLower, theColUpper)),
        myLowerRow(theRowLower),
        mySizeRow(theRowUpper - theRowLower + 1),
        myLowerCol(theColLower),
        mySizeCol(theColUpper - theColLower + 1)
  {
  }

  NCollection_Array2(const NCollection_Array2& theOther)
      : NCollection_Array1<TheItemType>(theOther),
        myLowerRow(theOther.LowerRow()),
        mySizeRow(theOther.NbRows()),
        myLowerCol(theOther.LowerCol()),
        mySizeCol(theOther.NbColumns())
  {
  }

  NCollection_Array2(NCollection_Array2&& theOther) noexcept
      : NCollection_Array1<TheItemType>(std::forward<NCollection_Array2>(theOther)),
        myLowerRow(theOther.LowerRow()),
        mySizeRow(theOther.NbRows()),
        myLowerCol(theOther.LowerCol()),
        mySizeCol(theOther.NbColumns())
  {
    theOther.myLowerRow = 1;
    theOther.mySizeRow  = 0;
    theOther.myLowerCol = 1;
    theOther.mySizeCol  = 0;
  }

  explicit NCollection_Array2(const TheItemType& theBegin,
                              const int          theRowLower,
                              const int          theRowUpper,
                              const int          theColLower,
                              const int          theColUpper)
      : NCollection_Array1<TheItemType>(
          theBegin,
          BeginPosition(theRowLower, theRowUpper, theColLower, theColUpper),
          LastPosition(theRowLower, theRowUpper, theColLower, theColUpper)),
        myLowerRow(theRowLower),
        mySizeRow(theRowUpper - theRowLower + 1),
        myLowerCol(theColLower),
        mySizeCol(theColUpper - theColLower + 1)
  {
  }

  int Size() const noexcept { return Length(); }

  int Length() const noexcept { return NbRows() * NbColumns(); }

  int NbRows() const noexcept { return static_cast<int>(mySizeRow); }

  int NbColumns() const noexcept { return static_cast<int>(mySizeCol); }

  int RowLength() const noexcept { return NbColumns(); }

  int ColLength() const noexcept { return NbRows(); }

  int LowerRow() const noexcept { return myLowerRow; }

  int UpperRow() const noexcept { return myLowerRow + static_cast<int>(mySizeRow) - 1; }

  int LowerCol() const noexcept { return myLowerCol; }

  int UpperCol() const noexcept { return myLowerCol + static_cast<int>(mySizeCol) - 1; }

  void UpdateLowerRow(const int theLowerRow) noexcept { myLowerRow = theLowerRow; }

  void UpdateLowerCol(const int theLowerCol) noexcept { myLowerCol = theLowerCol; }

  void UpdateUpperRow(const int theUpperRow) noexcept
  {
    myLowerRow = myLowerRow - UpperRow() + theUpperRow;
  }

  void UpdateUpperCol(const int theUpperCol) noexcept
  {
    myLowerCol = myLowerCol - UpperCol() + theUpperCol;
  }

  NCollection_Array2& Assign(const NCollection_Array2& theOther)
  {
    if (&theOther == this)
    {
      return *this;
    }
    NCollection_Array1<TheItemType>::Assign(theOther);

    return *this;
  }

  NCollection_Array2& Move(NCollection_Array2&& theOther) noexcept
  {
    if (&theOther == this)
    {
      return *this;
    }
    NCollection_Array1<TheItemType>::Move(theOther);
    myLowerRow          = theOther.myLowerRow;
    mySizeRow           = theOther.mySizeRow;
    myLowerCol          = theOther.myLowerCol;
    mySizeCol           = theOther.mySizeCol;
    theOther.myLowerRow = 1;
    theOther.mySizeRow  = 0;
    theOther.myLowerCol = 1;
    theOther.mySizeCol  = 0;
    return *this;
  }

  NCollection_Array2& Move(NCollection_Array2& theOther) noexcept
  {
    return Move(std::move(theOther));
  }

  NCollection_Array2& operator=(const NCollection_Array2& theOther) { return Assign(theOther); }

  NCollection_Array2& operator=(NCollection_Array2&& theOther) noexcept
  {
    return Move(std::forward<NCollection_Array2>(theOther));
  }

  const_reference Value(const int theRow, const int theCol) const
  {
    const size_t aPos = (theRow - myLowerRow) * mySizeCol + (theCol - myLowerCol);
    return NCollection_Array1<TheItemType>::at(aPos);
  }

  const_reference operator()(const int theRow, const int theCol) const
  {
    const size_t aPos = (theRow - myLowerRow) * mySizeCol + (theCol - myLowerCol);
    return NCollection_Array1<TheItemType>::at(aPos);
  }

  reference ChangeValue(const int theRow, const int theCol)
  {
    const size_t aPos = (theRow - myLowerRow) * mySizeCol + (theCol - myLowerCol);
    return NCollection_Array1<TheItemType>::at(aPos);
  }

  reference operator()(const int theRow, const int theCol) { return ChangeValue(theRow, theCol); }

  void SetValue(const int theRow, const int theCol, const TheItemType& theItem)
  {
    const size_t aPos = (theRow - myLowerRow) * mySizeCol + (theCol - myLowerCol);
    NCollection_Array1<TheItemType>::at(aPos) = theItem;
  }

  void SetValue(const int theRow, const int theCol, TheItemType&& theItem)
  {
    const size_t aPos = (theRow - myLowerRow) * mySizeCol + (theCol - myLowerCol);
    NCollection_Array1<TheItemType>::at(aPos) = std::forward<TheItemType>(theItem);
  }

  void Resize(int  theRowLower,
              int  theRowUpper,
              int  theColLower,
              int  theColUpper,
              bool theToCopyData)
  {
    Standard_RangeError_Raise_if(theRowUpper < theRowLower || theColUpper < theColLower,
                                 "NCollection_Array2::Resize");
    if (!theToCopyData)
    {
      NCollection_Array1<TheItemType>::Resize(
        BeginPosition(theRowLower, theRowUpper, theColLower, theColUpper),
        LastPosition(theRowLower, theRowUpper, theColLower, theColUpper),
        false);
      mySizeRow  = theRowUpper - theRowLower + 1;
      mySizeCol  = theColUpper - theColLower + 1;
      myLowerRow = theRowLower;
      myLowerCol = theColLower;
      return;
    }
    const size_t aNewNbRows    = theRowUpper - theRowLower + 1;
    const size_t aNewNbCols    = theColUpper - theColLower + 1;
    const size_t aNbRowsToCopy = (std::min)(mySizeRow, aNewNbRows);
    const size_t aNbColsToCopy = (std::min)(mySizeCol, aNewNbCols);

    NCollection_Array2<TheItemType> aTmpMovedCopy(std::move(*this));
    TheItemType*                    anOldPointer = &aTmpMovedCopy.ChangeFirst();
    NCollection_Array1<TheItemType>::Resize(
      BeginPosition(theRowLower, theRowUpper, theColLower, theColUpper),
      LastPosition(theRowLower, theRowUpper, theColLower, theColUpper),
      false);
    mySizeRow        = aNewNbRows;
    mySizeCol        = aNewNbCols;
    myLowerRow       = theRowLower;
    myLowerCol       = theColLower;
    size_t aOldInter = 0;
    for (size_t aRowIter = 0; aRowIter < aNbRowsToCopy; ++aRowIter)
    {
      for (size_t aColIter = 0; aColIter < aNbColsToCopy; ++aColIter)
      {
        NCollection_Array1<TheItemType>::at(aRowIter * aNewNbCols + aColIter) =
          std::move(anOldPointer[aOldInter++]);
      }
    }
  }

protected:
  int    myLowerRow;
  size_t mySizeRow;
  int    myLowerCol;
  size_t mySizeCol;

  friend iterator;
  friend const_iterator;
};
