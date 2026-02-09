#pragma once

#include <NCollection_Array1.hpp>
#include <gp_XY.hpp>
#include <gp_XYZ.hpp>

#ifdef Opposite
  #undef Opposite
#endif

#include <math_Matrix.hpp>

#include <array>
#include <utility>

template <typename TheItemType>
class math_VectorBase
{
  static const int THE_BUFFER_SIZE = 32;

public:
  DEFINE_STANDARD_ALLOC;
  DEFINE_NCOLLECTION_ALLOC;

public:
  inline math_VectorBase(const int theLower, const int theUpper);

  inline math_VectorBase(const int theLower, const int theUpper, const TheItemType theInitialValue);

  inline math_VectorBase(const TheItemType* theTab, const int theLower, const int theUpper);

  inline math_VectorBase(const gp_XY& Other);

  inline math_VectorBase(const gp_XYZ& Other);

  void Init(const TheItemType theInitialValue);

  inline math_VectorBase(const math_VectorBase& theOther);

  inline math_VectorBase(math_VectorBase&& theOther) noexcept;

  inline int Length() const { return Array.Length(); }

  inline int Lower() const { return Array.Lower(); }

  inline int Upper() const { return Array.Upper(); }

  inline double Norm() const;

  inline double Norm2() const;

  inline int Max() const;

  inline int Min() const;

  inline void Normalize();

  [[nodiscard]] inline math_VectorBase Normalized() const;

  inline void Invert();

  inline math_VectorBase Inverse() const;

  inline void Set(const int theI1, const int theI2, const math_VectorBase& theV);

  inline math_VectorBase Slice(const int theI1, const int theI2) const;

  inline void Multiply(const TheItemType theRight);

  void operator*=(const TheItemType theRight) { Multiply(theRight); }

  [[nodiscard]] inline math_VectorBase Multiplied(const TheItemType theRight) const;

  [[nodiscard]] math_VectorBase operator*(const TheItemType theRight) const
  {
    return Multiplied(theRight);
  }

  [[nodiscard]] inline math_VectorBase TMultiplied(const TheItemType theRight) const;

  friend inline math_VectorBase operator*(const TheItemType      theLeft,
                                          const math_VectorBase& theRight)
  {
    return theRight.Multiplied(theLeft);
  }

  inline void Divide(const TheItemType theRight);

  void operator/=(const TheItemType theRight) { Divide(theRight); }

  [[nodiscard]] inline math_VectorBase Divided(const TheItemType theRight) const;

  [[nodiscard]] math_VectorBase operator/(const TheItemType theRight) const
  {
    return Divided(theRight);
  }

  inline void Add(const math_VectorBase& theRight);

  void operator+=(const math_VectorBase& theRight) { Add(theRight); }

  [[nodiscard]] inline math_VectorBase Added(const math_VectorBase& theRight) const;

  [[nodiscard]] math_VectorBase operator+(const math_VectorBase& theRight) const
  {
    return Added(theRight);
  }

  inline void Multiply(const math_VectorBase& theLeft, const math_Matrix& theRight);

  inline void Multiply(const math_Matrix& theLeft, const math_VectorBase& theRight);

  inline void TMultiply(const math_Matrix& theTLeft, const math_VectorBase& theRight);

  inline void TMultiply(const math_VectorBase& theLeft, const math_Matrix& theTRight);

  inline void Add(const math_VectorBase& theLeft, const math_VectorBase& theRight);

  inline void Subtract(const math_VectorBase& theLeft, const math_VectorBase& theRight);

  const TheItemType& Value(const int theNum) const { return Array(theNum); }

  inline TheItemType& Value(const int theNum) { return Array(theNum); }

  const TheItemType& operator()(const int theNum) const { return Value(theNum); }

  TheItemType& operator()(const int theNum) { return Value(theNum); }

  inline math_VectorBase& Initialized(const math_VectorBase& theOther);

  math_VectorBase& operator=(const math_VectorBase& theOther) { return Initialized(theOther); }

  inline math_VectorBase& operator=(math_VectorBase&& theOther);

  [[nodiscard]] inline TheItemType Multiplied(const math_VectorBase& theRight) const;

  [[nodiscard]] inline TheItemType operator*(const math_VectorBase& theRight) const
  {
    return Multiplied(theRight);
  }

  [[nodiscard]] inline math_VectorBase Multiplied(const math_Matrix& theRight) const;

  [[nodiscard]] math_VectorBase operator*(const math_Matrix& theRight) const
  {
    return Multiplied(theRight);
  }

  inline math_VectorBase Opposite();

  math_VectorBase operator-() { return Opposite(); }

  inline void Subtract(const math_VectorBase& theRight);

  void operator-=(const math_VectorBase& theRight) { Subtract(theRight); }

  [[nodiscard]] inline math_VectorBase Subtracted(const math_VectorBase& theRight) const;

  [[nodiscard]] math_VectorBase operator-(const math_VectorBase& theRight) const
  {
    return Subtracted(theRight);
  }

  inline void Multiply(const TheItemType theLeft, const math_VectorBase& theRight);

  inline void Dump(Standard_OStream& theO) const;

  const NCollection_Array1<TheItemType>& Array1() const { return Array; }

  inline void Resize(const int theSize);

  friend inline Standard_OStream& operator<<(Standard_OStream& theO, const math_VectorBase& theVec)
  {
    theVec.Dump(theO);
    return theO;
  }

  friend class math_Matrix;

protected:
  inline void SetLower(const int theLower);

private:
  std::array<TheItemType, THE_BUFFER_SIZE> myBuffer;
  NCollection_Array1<TheItemType>          Array;
};

#include <Standard_DimensionError.hpp>
#include <Standard_DivideByZero.hpp>
#include <Standard_RangeError.hpp>
#include <Standard_NullValue.hpp>

#include <stdio.h>

template <typename TheItemType>
math_VectorBase<TheItemType>::math_VectorBase(const int theLower, const int theUpper)
    : Array(theUpper - theLower + 1 <= math_VectorBase::THE_BUFFER_SIZE
              ? NCollection_Array1<TheItemType>(*myBuffer.data(), theLower, theUpper)
              : NCollection_Array1<TheItemType>(theLower, theUpper))
{
}

template <typename TheItemType>
math_VectorBase<TheItemType>::math_VectorBase(const int         theLower,
                                              const int         theUpper,
                                              const TheItemType theInitialValue)
    : Array(theUpper - theLower + 1 <= math_VectorBase::THE_BUFFER_SIZE
              ? NCollection_Array1<TheItemType>(*myBuffer.data(), theLower, theUpper)
              : NCollection_Array1<TheItemType>(theLower, theUpper))
{
  Array.Init(theInitialValue);
}

template <typename TheItemType>
math_VectorBase<TheItemType>::math_VectorBase(const TheItemType* theTab,
                                              const int          theLower,
                                              const int          theUpper)
    : Array(*theTab, theLower, theUpper)
{
}

template <typename TheItemType>
math_VectorBase<TheItemType>::math_VectorBase(const gp_XY& theOther)
    : Array(*myBuffer.data(), 1, 2)
{
  Array(1) = static_cast<TheItemType>(theOther.X());
  Array(2) = static_cast<TheItemType>(theOther.Y());
}

template <typename TheItemType>
math_VectorBase<TheItemType>::math_VectorBase(const gp_XYZ& theOther)
    : Array(*myBuffer.data(), 1, 3)
{
  Array(1) = static_cast<TheItemType>(theOther.X());
  Array(2) = static_cast<TheItemType>(theOther.Y());
  Array(3) = static_cast<TheItemType>(theOther.Z());
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::Init(const TheItemType theInitialValue)
{
  Array.Init(theInitialValue);
}

template <typename TheItemType>
math_VectorBase<TheItemType>::math_VectorBase(const math_VectorBase<TheItemType>& theOther)
    : Array(theOther.Array)
{
}

template <typename TheItemType>
math_VectorBase<TheItemType>::math_VectorBase(math_VectorBase<TheItemType>&& theOther) noexcept
    : myBuffer{},
      Array(theOther.Array.IsDeletable()
              ? std::move(theOther.Array)
              : (theOther.Length() <= math_VectorBase::THE_BUFFER_SIZE
                   ? NCollection_Array1<TheItemType>(*myBuffer.data(),
                                                     theOther.Lower(),
                                                     theOther.Upper())
                   : NCollection_Array1<TheItemType>(theOther.Lower(), theOther.Upper())))
{
  if (!theOther.Array.IsEmpty())
  {
    Array.Assign(theOther.Array);
  }
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::SetLower(const int theLower)
{
  Array.UpdateLowerBound(theLower);
}

template <typename TheItemType>
double math_VectorBase<TheItemType>::Norm() const
{
  double Result = 0;
  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    Result = Result + Array(Index) * Array(Index);
  }
  return std::sqrt(Result);
}

template <typename TheItemType>
double math_VectorBase<TheItemType>::Norm2() const
{
  double Result = 0;

  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    Result = Result + Array(Index) * Array(Index);
  }
  return Result;
}

template <typename TheItemType>
int math_VectorBase<TheItemType>::Max() const
{
  int    I = 0;
  double X = RealFirst();

  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    if (Array(Index) > X)
    {
      X = Array(Index);
      I = Index;
    }
  }
  return I;
}

template <typename TheItemType>
int math_VectorBase<TheItemType>::Min() const
{
  int    I = 0;
  double X = RealLast();

  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    if (Array(Index) < X)
    {
      X = Array(Index);
      I = Index;
    }
  }
  return I;
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::Set(const int                           theI1,
                                       const int                           theI2,
                                       const math_VectorBase<TheItemType>& theV)
{
  Standard_RangeError_Raise_if((theI1 < Lower()) || (theI2 > Upper()) || (theI1 > theI2)
                                 || (theI2 - theI1 + 1 != theV.Length()),
                               "math_VectorBase::Set() - invalid indices");
  int I = theV.Lower();
  for (int Index = theI1; Index <= theI2; Index++)
  {
    Array(Index) = theV.Array(I);
    I++;
  }
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::Normalize()
{
  double Result = Norm();
  Standard_NullValue_Raise_if((Result <= RealEpsilon()),
                              "math_VectorBase::Normalize() - vector has zero norm");
  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    Array(Index) = Array(Index) / Result;
  }
}

template <typename TheItemType>
math_VectorBase<TheItemType> math_VectorBase<TheItemType>::Normalized() const
{
  math_VectorBase Result = *this;
  Result.Normalize();
  return Result;
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::Invert()
{
  for (int Index = Lower(); Index <= (Lower() + Length()) >> 1; Index++)
  {
    int         J     = Upper() + Lower() - Index;
    TheItemType aTemp = Array(Index);
    Array(Index)      = Array(J);
    Array(J)          = aTemp;
  }
}

template <typename TheItemType>
math_VectorBase<TheItemType> math_VectorBase<TheItemType>::Inverse() const
{
  math_VectorBase Result = *this;
  Result.Invert();
  return Result;
}

template <typename TheItemType>
math_VectorBase<TheItemType> math_VectorBase<TheItemType>::Multiplied(
  const TheItemType theRight) const
{
  math_VectorBase Result(Lower(), Upper());
  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    Result.Array(Index) = Array(Index) * theRight;
  }
  return Result;
}

template <typename TheItemType>
math_VectorBase<TheItemType> math_VectorBase<TheItemType>::TMultiplied(
  const TheItemType theRight) const
{
  math_VectorBase Result(Lower(), Upper());
  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    Result.Array(Index) = Array(Index) * theRight;
  }
  return Result;
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::Multiply(const TheItemType theRight)
{
  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    Array(Index) = Array(Index) * theRight;
  }
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::Divide(const TheItemType theRight)
{
  Standard_DivideByZero_Raise_if(std::abs(theRight) <= RealEpsilon(),
                                 "math_VectorBase::Divide() - devisor is zero");

  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    Array(Index) = Array(Index) / theRight;
  }
}

template <typename TheItemType>
math_VectorBase<TheItemType> math_VectorBase<TheItemType>::Divided(const TheItemType theRight) const
{
  Standard_DivideByZero_Raise_if(std::abs(theRight) <= RealEpsilon(),
                                 "math_VectorBase::Divided() - devisor is zero");
  math_VectorBase temp = Multiplied(1. / theRight);
  return temp;
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::Add(const math_VectorBase<TheItemType>& theRight)
{
  Standard_DimensionError_Raise_if(Length() != theRight.Length(),
                                   "math_VectorBase::Add() - input vector has wrong dimensions");

  int I = theRight.Lower();
  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    Array(Index) = Array(Index) + theRight.Array(I);
    I++;
  }
}

template <typename TheItemType>
math_VectorBase<TheItemType> math_VectorBase<TheItemType>::Added(
  const math_VectorBase<TheItemType>& theRight) const
{
  Standard_DimensionError_Raise_if(Length() != theRight.Length(),
                                   "math_VectorBase::Added() - input vector has wrong dimensions");

  math_VectorBase Result(Lower(), Upper());

  int I = theRight.Lower();
  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    Result.Array(Index) = Array(Index) + theRight.Array(I);
    I++;
  }
  return Result;
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::Subtract(const math_VectorBase<TheItemType>& theRight)
{
  Standard_DimensionError_Raise_if(
    Length() != theRight.Length(),
    "math_VectorBase::Subtract() - input vector has wrong dimensions");

  int I = theRight.Lower();
  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    Array(Index) = Array(Index) - theRight.Array(I);
    I++;
  }
}

template <typename TheItemType>
math_VectorBase<TheItemType> math_VectorBase<TheItemType>::Subtracted(
  const math_VectorBase<TheItemType>& theRight) const
{
  Standard_DimensionError_Raise_if(
    Length() != theRight.Length(),
    "math_VectorBase::Subtracted() - input vector has wrong dimensions");

  math_VectorBase Result(Lower(), Upper());

  int I = theRight.Lower();
  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    Result.Array(Index) = Array(Index) - theRight.Array(I);
    I++;
  }
  return Result;
}

template <typename TheItemType>
math_VectorBase<TheItemType> math_VectorBase<TheItemType>::Slice(const int theI1,
                                                                 const int theI2) const
{
  Standard_RangeError_Raise_if((theI1 < Lower()) || (theI1 > Upper()) || (theI2 < Lower())
                                 || (theI2 > Upper()),
                               "math_VectorBase::Slice() - invalid indices");

  if (theI2 >= theI1)
  {
    math_VectorBase Result(theI1, theI2);
    for (int Index = theI1; Index <= theI2; Index++)
    {
      Result.Array(Index) = Array(Index);
    }
    return Result;
  }
  else
  {
    math_VectorBase Result(theI2, theI1);
    for (int Index = theI1; Index >= theI2; Index--)
    {
      Result.Array(Index) = Array(Index);
    }
    return Result;
  }
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::Add(const math_VectorBase<TheItemType>& theLeft,
                                       const math_VectorBase<TheItemType>& theRight)
{
  Standard_DimensionError_Raise_if((Length() != theRight.Length())
                                     || (theRight.Length() != theLeft.Length()),
                                   "math_VectorBase::Add() - input vectors have wrong dimensions");

  int I = theLeft.Lower();
  int J = theRight.Lower();
  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    Array(Index) = theLeft.Array(I) + theRight.Array(J);
    I++;
    J++;
  }
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::Subtract(const math_VectorBase<TheItemType>& theLeft,
                                            const math_VectorBase<TheItemType>& theRight)
{
  Standard_DimensionError_Raise_if(
    (Length() != theRight.Length()) || (theRight.Length() != theLeft.Length()),
    "math_VectorBase::Subtract() - input vectors have wrong dimensions");

  int I = theLeft.Lower();
  int J = theRight.Lower();
  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    Array(Index) = theLeft.Array(I) - theRight.Array(J);
    I++;
    J++;
  }
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::Multiply(const math_Matrix&                  theLeft,
                                            const math_VectorBase<TheItemType>& theRight)
{
  Standard_DimensionError_Raise_if(
    (Length() != theLeft.RowNumber()) || (theLeft.ColNumber() != theRight.Length()),
    "math_VectorBase::Multiply() - input matrix and /or vector have wrong dimensions");

  int Index = Lower();
  for (int I = theLeft.LowerRow(); I <= theLeft.UpperRow(); I++)
  {
    Array(Index) = 0.0;
    int K        = theRight.Lower();
    for (int J = theLeft.LowerCol(); J <= theLeft.UpperCol(); J++)
    {
      Array(Index) = Array(Index) + theLeft(I, J) * theRight.Array(K);
      K++;
    }
    Index++;
  }
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::Multiply(const math_VectorBase<TheItemType>& theLeft,
                                            const math_Matrix&                  theRight)
{
  Standard_DimensionError_Raise_if(
    (Length() != theRight.ColNumber()) || (theLeft.Length() != theRight.RowNumber()),
    "math_VectorBase::Multiply() - input matrix and /or vector have wrong dimensions");

  int Index = Lower();
  for (int J = theRight.LowerCol(); J <= theRight.UpperCol(); J++)
  {
    Array(Index) = 0.0;
    int K        = theLeft.Lower();
    for (int I = theRight.LowerRow(); I <= theRight.UpperRow(); I++)
    {
      Array(Index) = Array(Index) + theLeft.Array(K) * theRight(I, J);
      K++;
    }
    Index++;
  }
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::TMultiply(const math_Matrix&                  theTLeft,
                                             const math_VectorBase<TheItemType>& theRight)
{
  Standard_DimensionError_Raise_if(
    (Length() != theTLeft.ColNumber()) || (theTLeft.RowNumber() != theRight.Length()),
    "math_VectorBase::TMultiply() - input matrix and /or vector have wrong dimensions");

  int Index = Lower();
  for (int I = theTLeft.LowerCol(); I <= theTLeft.UpperCol(); I++)
  {
    Array(Index) = 0.0;
    int K        = theRight.Lower();
    for (int J = theTLeft.LowerRow(); J <= theTLeft.UpperRow(); J++)
    {
      Array(Index) = Array(Index) + theTLeft(J, I) * theRight.Array(K);
      K++;
    }
    Index++;
  }
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::TMultiply(const math_VectorBase<TheItemType>& theLeft,
                                             const math_Matrix&                  theTRight)
{
  Standard_DimensionError_Raise_if(
    (Length() != theTRight.RowNumber()) || (theLeft.Length() != theTRight.ColNumber()),
    "math_VectorBase::TMultiply() - input matrix and /or vector have wrong dimensions");

  int Index = Lower();
  for (int J = theTRight.LowerRow(); J <= theTRight.UpperRow(); J++)
  {
    Array(Index) = 0.0;
    int K        = theLeft.Lower();
    for (int I = theTRight.LowerCol(); I <= theTRight.UpperCol(); I++)
    {
      Array(Index) = Array(Index) + theLeft.Array(K) * theTRight(J, I);
      K++;
    }
    Index++;
  }
}

template <typename TheItemType>
TheItemType math_VectorBase<TheItemType>::Multiplied(
  const math_VectorBase<TheItemType>& theRight) const
{
  double Result = 0;

  Standard_DimensionError_Raise_if(
    Length() != theRight.Length(),
    "math_VectorBase::Multiplied() - input vector has wrong dimensions");

  int I = theRight.Lower();
  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    Result = Result + Array(Index) * theRight.Array(I);
    I++;
  }
  return Result;
}

template <typename TheItemType>
math_VectorBase<TheItemType> math_VectorBase<TheItemType>::Opposite()
{
  math_VectorBase Result(Lower(), Upper());
  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    Result.Array(Index) = -Array(Index);
  }
  return Result;
}

template <typename TheItemType>
math_VectorBase<TheItemType> math_VectorBase<TheItemType>::Multiplied(
  const math_Matrix& theRight) const
{
  Standard_DimensionError_Raise_if(
    Length() != theRight.RowNumber(),
    "math_VectorBase::Multiplied() - input matrix has wrong dimensions");

  math_VectorBase Result(theRight.LowerCol(), theRight.UpperCol());
  for (int J2 = theRight.LowerCol(); J2 <= theRight.UpperCol(); J2++)
  {
    Result.Array(J2) = 0.0;
    int theI2        = theRight.LowerRow();
    for (int I = Lower(); I <= Upper(); I++)
    {
      Result.Array(J2) = Result.Array(J2) + Array(I) * theRight(theI2, J2);
      theI2++;
    }
  }
  return Result;
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::Multiply(const TheItemType                   theLeft,
                                            const math_VectorBase<TheItemType>& theRight)
{
  Standard_DimensionError_Raise_if(
    (Length() != theRight.Length()),
    "math_VectorBase::Multiply() - input vector has wrong dimensions");
  for (int I = Lower(); I <= Upper(); I++)
  {
    Array(I) = theLeft * theRight.Array(I);
  }
}

template <typename TheItemType>
math_VectorBase<TheItemType>& math_VectorBase<TheItemType>::Initialized(
  const math_VectorBase<TheItemType>& theOther)
{
  Standard_DimensionError_Raise_if(
    Length() != theOther.Length(),
    "math_VectorBase::Initialized() - input vector has wrong dimensions");
  memmove(&Array.ChangeFirst(), &theOther.Array.First(), sizeof(TheItemType) * Array.Length());
  return *this;
}

template <typename TheItemType>
math_VectorBase<TheItemType>& math_VectorBase<TheItemType>::operator=(
  math_VectorBase<TheItemType>&& theOther)
{
  if (this == &theOther)
  {
    return *this;
  }

  if (Array.IsDeletable() && theOther.Array.IsDeletable() && Lower() == theOther.Lower()
      && Length() == theOther.Length())
  {
    Array.Move(theOther.Array);
  }
  else
  {
    Initialized(theOther);
  }
  return *this;
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::Dump(Standard_OStream& theO) const
{
  theO << "math_Vector of Length = " << Length() << "\n";
  for (int Index = Lower(); Index <= Upper(); Index++)
  {
    theO << "math_Vector(" << Index << ") = " << Array(Index) << "\n";
  }
}

template <typename TheItemType>
void math_VectorBase<TheItemType>::Resize(const int theSize)
{
  const int  theLower      = Array.Lower();
  const int  theUpper      = theLower + theSize - 1;
  const bool aNewFitsStack = theSize <= THE_BUFFER_SIZE;
  const bool aWasOnStack   = !Array.IsDeletable();

  if (aWasOnStack && aNewFitsStack)
  {

    Array = NCollection_Array1<TheItemType>(*myBuffer.data(), theLower, theUpper);
  }
  else if (aNewFitsStack)
  {

    const int aCopyLen = std::min(Array.Length(), theSize);
    for (int i = 0; i < aCopyLen; ++i)
    {
      myBuffer[i] = Array.Value(theLower + i);
    }
    Array = NCollection_Array1<TheItemType>(*myBuffer.data(), theLower, theUpper);
  }
  else
  {

    Array.Resize(theLower, theUpper, true);
  }
}
