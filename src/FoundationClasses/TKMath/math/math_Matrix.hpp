#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <NCollection_Allocator.hpp>

#include <math_DoubleTab.hpp>
#include <Standard_OStream.hpp>

// resolve name collisions with X11 headers
#ifdef Opposite
  #undef Opposite
#endif

template <typename T = double>
class math_VectorBase;

//! This class implements the real matrix abstract data type.
//! Matrixes can have an arbitrary range which must be defined
//! at the declaration and cannot be changed after this declaration
//! math_Matrix(-3,5,2,4); //a vector with range [-3..5, 2..4]
//! Matrix values may be initialized and
//! retrieved using indexes which must lie within the range
//! of definition of the matrix.
//! Matrix objects follow "value semantics", that is, they
//! cannot be shared and are copied through assignment
//! Matrices are copied through assignment:
//! @code
//! math_Matrix M2(1, 9, 1, 3);
//! ...
//! M2 = M1;
//! M1(1) = 2.0;//the matrix M2 will not be modified.
//! @endcode
//! The exception RangeError is raised when trying to access
//! outside the range of a matrix :
//! @code
//! M1(11, 1)=0.0// --> will raise RangeError.
//! @endcode
//!
//! The exception DimensionError is raised when the dimensions of
//! two matrices or vectors are not compatible.
//! @code
//! math_Matrix M3(1, 2, 1, 2);
//! M3 = M1;   // will raise DimensionError
//! M1.Add(M3) // --> will raise DimensionError.
//! @endcode
//! A Matrix can be constructed with a pointer to "c array".
//! It allows to carry the bounds inside the matrix.
//! Example :
//! @code
//! double tab1[10][20];
//! double tab2[200];
//!
//! math_Matrix A (tab1[0][0], 1, 10, 1, 20);
//! math_Matrix B (tab2[0],    1, 10, 1, 20);
//! @endcode
class math_Matrix
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a non-initialized matrix of range [LowerRow..UpperRow,
  //! LowerCol..UpperCol]
  //! For the constructed matrix:
  //! -   LowerRow and UpperRow are the indexes of the
  //! lower and upper bounds of a row, and
  //! -   LowerCol and UpperCol are the indexes of the
  //! lower and upper bounds of a column.
  inline math_Matrix(const int LowerRow,
                     const int UpperRow,
                     const int LowerCol,
                     const int UpperCol);

  //! constructs a non-initialized matrix of range [LowerRow..UpperRow,
  //! LowerCol..UpperCol]
  //! whose values are all initialized with the value InitialValue.
  inline math_Matrix(const int    LowerRow,
                     const int    UpperRow,
                     const int    LowerCol,
                     const int    UpperCol,
                     const double InitialValue);

  //! constructs a matrix of range [LowerRow..UpperRow,
  //! LowerCol..UpperCol]
  //! Sharing data with a "C array" pointed by Tab.
  inline math_Matrix(void* const Tab,
                     const int   LowerRow,
                     const int   UpperRow,
                     const int   LowerCol,
                     const int   UpperCol);

  //! constructs a matrix for copy in initialization.
  //! An exception is raised if the matrixes have not the same dimensions.
  inline math_Matrix(const math_Matrix& Other);

  //! Move constructor
  inline math_Matrix(math_Matrix&& Other) noexcept;

  //! Initialize all the elements of a matrix to InitialValue.
  inline void Init(const double InitialValue) noexcept;

  //! Returns the number of rows of this matrix.
  //! Note that for a matrix A you always have the following relations:
  //! - A.RowNumber() = A.UpperRow() -   A.LowerRow() + 1
  //! - A.ColNumber() = A.UpperCol() -   A.LowerCol() + 1
  //! - the length of a row of A is equal to the number of columns of A,
  //! - the length of a column of A is equal to the number of
  //! rows of A.returns the row range of a matrix.
  int RowNumber() const noexcept;

  //! Returns the number of rows of this matrix.
  //! Note that for a matrix A you always have the following relations:
  //! - A.RowNumber() = A.UpperRow() -   A.LowerRow() + 1
  //! - A.ColNumber() = A.UpperCol() -   A.LowerCol() + 1
  //! - the length of a row of A is equal to the number of columns of A,
  //! - the length of a column of A is equal to the number of
  //! rows of A.returns the row range of a matrix.
  int ColNumber() const noexcept;

  //! Returns the value of the Lower index of the row
  //! range of a matrix.
  int LowerRow() const noexcept;

  //! Returns the Upper index of the row range
  //! of a matrix.
  int UpperRow() const noexcept;

  //! Returns the value of the Lower index of the
  //! column range of a matrix.
  int LowerCol() const noexcept;

  //! Returns the value of the upper index of the
  //! column range of a matrix.
  int UpperCol() const noexcept;

  //! Computes the determinant of a matrix.
  //! An exception is raised if the matrix is not a square matrix.
  Standard_EXPORT double Determinant() const;

  //! Transposes a given matrix.
  //! An exception is raised if the matrix is not a square matrix.
  inline void Transpose();

  //! Inverts a matrix using Gauss algorithm.
  //! Exception NotSquare is raised if the matrix is not square.
  //! Exception SingularMatrix is raised if the matrix is singular.
  Standard_EXPORT void Invert();

  //! Sets this matrix to the product of the matrix Left, and the matrix Right.
  //! Example
  //! math_Matrix A (1, 3, 1, 3);
  //! math_Matrix B (1, 3, 1, 3);
  //! // A = ... , B = ...
  //! math_Matrix C (1, 3, 1, 3);
  //! C.Multiply(A, B);
  //! Exceptions
  //! Standard_DimensionError if matrices are of incompatible dimensions, i.e. if:
  //! -   the number of columns of matrix Left, or the number of
  //! rows of matrix TLeft is not equal to the number of rows
  //! of matrix Right, or
  //! -   the number of rows of matrix Left, or the number of
  //! columns of matrix TLeft is not equal to the number of
  //! rows of this matrix, or
  //! -   the number of columns of matrix Right is not equal to
  //! the number of columns of this matrix.
  inline void Multiply(const double Right) noexcept;

  void operator*=(const double Right) noexcept { Multiply(Right); }

  //! multiplies all the elements of a matrix by the
  //! value <Right>.
  [[nodiscard]] inline math_Matrix Multiplied(const double Right) const noexcept;

  [[nodiscard]] math_Matrix operator*(const double Right) const noexcept
  {
    return Multiplied(Right);
  }

  //! Sets this matrix to the product of the
  //! transposed matrix TLeft, and the matrix Right.
  //! Example
  //! math_Matrix A (1, 3, 1, 3);
  //! math_Matrix B (1, 3, 1, 3);
  //! // A = ... , B = ...
  //! math_Matrix C (1, 3, 1, 3);
  //! C.Multiply(A, B);
  //! Exceptions
  //! Standard_DimensionError if matrices are of incompatible dimensions, i.e. if:
  //! -   the number of columns of matrix Left, or the number of
  //! rows of matrix TLeft is not equal to the number of rows
  //! of matrix Right, or
  //! -   the number of rows of matrix Left, or the number of
  //! columns of matrix TLeft is not equal to the number of
  //! rows of this matrix, or
  //! -   the number of columns of matrix Right is not equal to
  //! the number of columns of this matrix.
  [[nodiscard]] inline math_Matrix TMultiplied(const double Right) const noexcept;
  friend math_Matrix               operator*(const double Left, const math_Matrix& Right);

  //! divides all the elements of a matrix by the value <Right>.
  //! An exception is raised if <Right> = 0.
  inline void Divide(const double Right);

  void operator/=(const double Right) { Divide(Right); }

  //! divides all the elements of a matrix by the value <Right>.
  //! An exception is raised if <Right> = 0.
  [[nodiscard]] inline math_Matrix Divided(const double Right) const;

  [[nodiscard]] math_Matrix operator/(const double Right) const { return Divided(Right); }

  //! adds the matrix <Right> to a matrix.
  //! An exception is raised if the dimensions are different.
  //! Warning
  //! In order to save time when copying matrices, it is
  //! preferable to use operator += or the function Add
  //! whenever possible.
  inline void Add(const math_Matrix& Right);

  void operator+=(const math_Matrix& Right) { Add(Right); }

  //! adds the matrix <Right> to a matrix.
  //! An exception is raised if the dimensions are different.
  [[nodiscard]] inline math_Matrix Added(const math_Matrix& Right) const;

  [[nodiscard]] math_Matrix operator+(const math_Matrix& Right) const { return Added(Right); }

  //! sets a matrix to the addition of <Left> and <Right>.
  //! An exception is raised if the dimensions are different.
  inline void Add(const math_Matrix& Left, const math_Matrix& Right);

  //! Subtracts the matrix <Right> from <me>.
  //! An exception is raised if the dimensions are different.
  //! Warning
  //! In order to avoid time-consuming copying of matrices, it
  //! is preferable to use operator -= or the function
  //! Subtract whenever possible.
  inline void Subtract(const math_Matrix& Right);

  void operator-=(const math_Matrix& Right) { Subtract(Right); }

  //! Returns the result of the subtraction of <Right> from <me>.
  //! An exception is raised if the dimensions are different.
  [[nodiscard]] inline math_Matrix Subtracted(const math_Matrix& Right) const;

  [[nodiscard]] math_Matrix operator-(const math_Matrix& Right) const { return Subtracted(Right); }

  //! Sets the values of this matrix,
  //! -   from index I1 to index I2 on the row dimension, and
  //! -   from index J1 to index J2 on the column dimension,
  //! to those of matrix M.
  //! Exceptions
  //! Standard_DimensionError if:
  //! -   I1 is less than the index of the lower row bound of this matrix, or
  //! -   I2 is greater than the index of the upper row bound of this matrix, or
  //! -   J1 is less than the index of the lower column bound of this matrix, or
  //! -   J2 is greater than the index of the upper column bound of this matrix, or
  //! -   I2 - I1 + 1 is not equal to the number of rows of matrix M, or
  //! -   J2 - J1 + 1 is not equal to the number of columns of matrix M.
  inline void Set(const int I1, const int I2, const int J1, const int J2, const math_Matrix& M);

  //! Sets the row of index Row of a matrix to the vector <V>.
  //! An exception is raised if the dimensions are different.
  //! An exception is raises if <Row> is inferior to the lower
  //! row of the matrix or <Row> is superior to the upper row.
  Standard_EXPORT void SetRow(const int Row, const math_VectorBase<>& V);

  //! Sets the column of index Col of a matrix to the vector <V>.
  //! An exception is raised if the dimensions are different.
  //! An exception is raises if <Col> is inferior to the lower
  //! column of the matrix or <Col> is superior to the upper
  //! column.
  Standard_EXPORT void SetCol(const int Col, const math_VectorBase<>& V);

  //! Sets the diagonal of a matrix to the value <Value>.
  //! An exception is raised if the matrix is not square.
  inline void SetDiag(const double Value);

  //! Returns the row of index Row of a matrix.
  Standard_EXPORT math_VectorBase<> Row(const int Row) const;

  //! Returns the column of index <Col> of a matrix.
  Standard_EXPORT math_VectorBase<> Col(const int Col) const;

  //! Swaps the rows of index Row1 and Row2.
  //! An exception is raised if <Row1> or <Row2> is out of range.
  Standard_EXPORT void SwapRow(const int Row1, const int Row2);

  //! Swaps the columns of index <Col1> and <Col2>.
  //! An exception is raised if <Col1> or <Col2> is out of range.
  Standard_EXPORT void SwapCol(const int Col1, const int Col2);

  //! Teturns the transposed of a matrix.
  //! An exception is raised if the matrix is not a square matrix.
  [[nodiscard]] inline math_Matrix Transposed() const;

  //! Returns the inverse of a matrix.
  //! Exception NotSquare is raised if the matrix is not square.
  //! Exception SingularMatrix is raised if the matrix is singular.
  Standard_EXPORT math_Matrix Inverse() const;

  //! Returns the product of the transpose of a matrix with
  //! the matrix <Right>.
  //! An exception is raised if the dimensions are different.
  inline math_Matrix TMultiply(const math_Matrix& Right) const;

  //! Computes a matrix as the product of 2 vectors.
  //! An exception is raised if the dimensions are different.
  //! <me> = <Left> * <Right>.
  Standard_EXPORT void Multiply(const math_VectorBase<>& Left, const math_VectorBase<>& Right);

  //! Computes a matrix as the product of 2 matrixes.
  //! An exception is raised if the dimensions are different.
  inline void Multiply(const math_Matrix& Left, const math_Matrix& Right);

  //! Computes a matrix to the product of the transpose of
  //! the matrix <TLeft> with the matrix <Right>.
  //! An exception is raised if the dimensions are different.
  inline void TMultiply(const math_Matrix& TLeft, const math_Matrix& Right);

  //! Sets a matrix to the Subtraction of the matrix <Right>
  //! from the matrix <Left>.
  //! An exception is raised if the dimensions are different.
  inline void Subtract(const math_Matrix& Left, const math_Matrix& Right);

  //! Accesses the value of index <Row>
  //! and <Col> of a matrix.
  //! An exception is raised if <Row> and <Col> are not
  //! in the correct range.
  const double& Value(const int Row, const int Col) const;

  //! Accesses (in read or write mode) the value of index <Row>
  //! and <Col> of a matrix.
  //! An exception is raised if <Row> and <Col> are not
  //! in the correct range.
  double& Value(const int Row, const int Col);

  const double& operator()(const int Row, const int Col) const { return Value(Row, Col); }

  double& operator()(const int Row, const int Col) { return Value(Row, Col); }

  //! Matrixes are copied through assignment.
  //! An exception is raised if the dimensions are different.
  inline math_Matrix& Initialized(const math_Matrix& Other);

  math_Matrix& operator=(const math_Matrix& Other) { return Initialized(Other); }

  //! Move assignment operator
  inline math_Matrix& operator=(math_Matrix&& Other);

  //! Returns the product of 2 matrices.
  //! An exception is raised if the dimensions are different.
  inline void Multiply(const math_Matrix& Right);

  void operator*=(const math_Matrix& Right) { Multiply(Right); }

  //! Returns the product of 2 matrices.
  //! An exception is raised if the dimensions are different.
  [[nodiscard]] inline math_Matrix Multiplied(const math_Matrix& Right) const;

  [[nodiscard]] math_Matrix operator*(const math_Matrix& Right) const { return Multiplied(Right); }

  //! Returns the product of a matrix by a vector.
  //! An exception is raised if the dimensions are different.
  [[nodiscard]] Standard_EXPORT math_VectorBase<> Multiplied(const math_VectorBase<>& Right) const;
  [[nodiscard]] Standard_EXPORT math_VectorBase<> operator*(const math_VectorBase<>& Right) const;

  //! Returns the opposite of a matrix.
  //! An exception is raised if the dimensions are different.
  inline math_Matrix Opposite() const;

  math_Matrix operator-() const { return Opposite(); }

  //! Prints information on the current state of the object.
  //! Is used to redefine the operator <<.
  inline void Dump(Standard_OStream& o) const;

protected:
  //! The new lower row of the matrix is set to <LowerRow>
  inline void SetLowerRow(const int LowerRow) noexcept;

  //! The new lower column of the matrix is set to the column
  //! of range <LowerCol>.
  inline void SetLowerCol(const int LowerCol) noexcept;

  //! The new lower row of the matrix is set to <LowerRow>
  //! and the new lower column of the matrix is set to the column
  //! of range <LowerCol>.
  void SetLower(const int LowerRow, const int LowerCol) noexcept;

private:
  math_DoubleTab Array;
};
// Copyright (c) 1997-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <math_NotSquare.hpp>
#include <Standard_DimensionError.hpp>
#include <Standard_DivideByZero.hpp>

//==================================================================================================

inline Standard_OStream& operator<<(Standard_OStream& o, const math_Matrix& mat)
{
  mat.Dump(o);
  return o;
}

//==================================================================================================

inline math_Matrix operator*(const double Left, const math_Matrix& Right)
{
  return Right.Multiplied(Left);
}

//==================================================================================================

inline const double& math_Matrix::Value(const int Row, const int Col) const
{
  return Array.Value(Row, Col);
}

//==================================================================================================

inline double& math_Matrix::Value(const int Row, const int Col)
{
  return Array.Value(Row, Col);
}

//==================================================================================================

inline int math_Matrix::RowNumber() const noexcept
{
  return Array.NbRows();
}

//==================================================================================================

inline int math_Matrix::ColNumber() const noexcept
{
  return Array.NbColumns();
}

//==================================================================================================

inline int math_Matrix::LowerRow() const noexcept
{
  return Array.LowerRow();
}

//==================================================================================================

inline int math_Matrix::UpperRow() const noexcept
{
  return Array.UpperRow();
}

//==================================================================================================

inline int math_Matrix::LowerCol() const noexcept
{
  return Array.LowerCol();
}

//==================================================================================================

inline int math_Matrix::UpperCol() const noexcept
{
  return Array.UpperCol();
}

//==================================================================================================

inline void math_Matrix::SetLower(const int LowerRow, const int LowerCol) noexcept
{
  SetLowerRow(LowerRow);
  SetLowerCol(LowerCol);
}

//==================================================================================================

inline math_Matrix::math_Matrix(const int LowerRow,
                                const int UpperRow,
                                const int LowerCol,
                                const int UpperCol)
    : Array(LowerRow, UpperRow, LowerCol, UpperCol)
{
}

//==================================================================================================

inline math_Matrix::math_Matrix(const int    LowerRow,
                                const int    UpperRow,
                                const int    LowerCol,
                                const int    UpperCol,
                                const double InitialValue)
    : Array(LowerRow, UpperRow, LowerCol, UpperCol)
{
  Array.Init(InitialValue);
}

//==================================================================================================

inline math_Matrix::math_Matrix(void* const Tab,
                                const int   LowerRow,
                                const int   UpperRow,
                                const int   LowerCol,
                                const int   UpperCol)
    : Array(Tab, LowerRow, UpperRow, LowerCol, UpperCol)
{
}

//==================================================================================================

inline math_Matrix::math_Matrix(const math_Matrix& Other)

  = default;

//==================================================================================================

inline math_Matrix::math_Matrix(math_Matrix&& Other) noexcept
    : Array(std::move(Other.Array))
{
}

//==================================================================================================

inline void math_Matrix::Init(const double InitialValue) noexcept
{
  Array.Init(InitialValue);
}

//==================================================================================================

inline void math_Matrix::SetLowerRow(const int LowerRow) noexcept
{
  Array.SetLowerRow(LowerRow);
}

//==================================================================================================

inline void math_Matrix::SetLowerCol(const int LowerCol) noexcept
{
  Array.SetLowerCol(LowerCol);
}

//==================================================================================================

inline void math_Matrix::Multiply(const double Right) noexcept
{
  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    for (int J = aLowerCol; J <= anUpperCol; J++)
    {
      Array(I, J) = Array(I, J) * Right;
    }
  }
}

//==================================================================================================

inline math_Matrix math_Matrix::Multiplied(const double Right) const noexcept
{
  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  math_Matrix Result(aLowerRow, anUpperRow, aLowerCol, anUpperCol);
  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    for (int J = aLowerCol; J <= anUpperCol; J++)
    {
      Result.Array(I, J) = Array(I, J) * Right;
    }
  }
  return Result;
}

//==================================================================================================

inline math_Matrix math_Matrix::TMultiplied(const double Right) const noexcept
{
  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  math_Matrix Result(aLowerRow, anUpperRow, aLowerCol, anUpperCol);
  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    for (int J = aLowerCol; J <= anUpperCol; J++)
    {
      Result.Array(I, J) = Array(I, J) * Right;
    }
  }
  return Result;
}

//==================================================================================================

inline void math_Matrix::Divide(const double Right)
{
  Standard_DivideByZero_Raise_if(std::abs(Right) <= RealEpsilon(),
                                 "math_Matrix::Divide() - zero divisor");

  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    for (int J = aLowerCol; J <= anUpperCol; J++)
    {
      Array(I, J) = Array(I, J) / Right;
    }
  }
}

//==================================================================================================

inline math_Matrix math_Matrix::Divided(const double Right) const
{
  Standard_DivideByZero_Raise_if(std::abs(Right) <= RealEpsilon(),
                                 "math_Matrix::Divided() - zero divisor");
  math_Matrix temp = Multiplied(1. / Right);
  return temp;
}

//==================================================================================================

inline void math_Matrix::Add(const math_Matrix& Right)
{
  Standard_DimensionError_Raise_if((RowNumber() != Right.RowNumber())
                                     || (ColNumber() != Right.ColNumber()),
                                   "math_Matrix::Add() - input matrix has different dimensions");

  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  int I2 = Right.LowerRow();
  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    int J2 = Right.LowerCol();
    for (int J = aLowerCol; J <= anUpperCol; J++)
    {
      Array(I, J) = Array(I, J) + Right.Array(I2, J2);
      J2++;
    }
    I2++;
  }
}

//==================================================================================================

inline math_Matrix math_Matrix::Added(const math_Matrix& Right) const
{
  Standard_DimensionError_Raise_if((RowNumber() != Right.RowNumber())
                                     || (ColNumber() != Right.ColNumber()),
                                   "math_Matrix::Added() - input matrix has different dimensions");

  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  math_Matrix Result(aLowerRow, anUpperRow, aLowerCol, anUpperCol);

  int I2 = Right.LowerRow();
  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    int J2 = Right.LowerCol();
    for (int J = aLowerCol; J <= anUpperCol; J++)
    {
      Result.Array(I, J) = Array(I, J) + Right.Array(I2, J2);
      J2++;
    }
    I2++;
  }
  return Result;
}

//==================================================================================================

inline void math_Matrix::Add(const math_Matrix& Left, const math_Matrix& Right)
{
  Standard_DimensionError_Raise_if(
    (RowNumber() != Right.RowNumber()) || (ColNumber() != Right.ColNumber())
      || (Right.RowNumber() != Left.RowNumber()) || (Right.ColNumber() != Left.ColNumber()),
    "math_Matrix::Add() - matrices have incompatible dimensions");

  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  int I1 = Left.LowerRow();
  int I2 = Right.LowerRow();
  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    int J1 = Left.LowerCol();
    int J2 = Right.LowerCol();
    for (int J = aLowerCol; J <= anUpperCol; J++)
    {
      Array(I, J) = Left.Array(I1, J1) + Right.Array(I2, J2);
      J1++;
      J2++;
    }
    I1++;
    I2++;
  }
}

//==================================================================================================

inline void math_Matrix::Subtract(const math_Matrix& Right)
{
  Standard_DimensionError_Raise_if(
    (RowNumber() != Right.RowNumber()) || (ColNumber() != Right.ColNumber()),
    "math_Matrix::Subtract() - input matrix has different dimensions");

  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  int I2 = Right.LowerRow();
  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    int J2 = Right.LowerCol();
    for (int J = aLowerCol; J <= anUpperCol; J++)
    {
      Array(I, J) = Array(I, J) - Right.Array(I2, J2);
      J2++;
    }
    I2++;
  }
}

//==================================================================================================

inline math_Matrix math_Matrix::Subtracted(const math_Matrix& Right) const
{
  Standard_DimensionError_Raise_if(
    (RowNumber() != Right.RowNumber()) || (ColNumber() != Right.ColNumber()),
    "math_Matrix::Subtracted() - input matrix has different dimensions");

  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  math_Matrix Result(aLowerRow, anUpperRow, aLowerCol, anUpperCol);

  int I2 = Right.LowerRow();
  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    int J2 = Right.LowerCol();
    for (int J = aLowerCol; J <= anUpperCol; J++)
    {
      Result.Array(I, J) = Array(I, J) - Right.Array(I2, J2);
      J2++;
    }
    I2++;
  }
  return Result;
}

//==================================================================================================

inline void math_Matrix::Subtract(const math_Matrix& Left, const math_Matrix& Right)
{
  Standard_DimensionError_Raise_if(
    (RowNumber() != Right.RowNumber()) || (ColNumber() != Right.ColNumber())
      || (Right.RowNumber() != Left.RowNumber()) || (Right.ColNumber() != Left.ColNumber()),
    "math_Matrix::Subtract() - matrices have incompatible dimensions");

  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  int I1 = Left.LowerRow();
  int I2 = Right.LowerRow();
  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    int J1 = Left.LowerCol();
    int J2 = Right.LowerCol();
    for (int J = aLowerCol; J <= anUpperCol; J++)
    {
      Array(I, J) = Left.Array(I1, J1) - Right.Array(I2, J2);
      J1++;
      J2++;
    }
    I1++;
    I2++;
  }
}

//==================================================================================================

inline math_Matrix math_Matrix::Opposite() const
{
  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  math_Matrix Result(aLowerRow, anUpperRow, aLowerCol, anUpperCol);

  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    for (int J = aLowerCol; J <= anUpperCol; J++)
    {
      Result.Array(I, J) = -Array(I, J);
    }
  }
  return Result;
}

//==================================================================================================

inline void math_Matrix::Set(const int          I1,
                             const int          I2,
                             const int          J1,
                             const int          J2,
                             const math_Matrix& M)
{
  Standard_DimensionError_Raise_if((I1 > I2) || (J1 > J2) || (I2 - I1 + 1 != M.RowNumber())
                                     || (J2 - J1 + 1 != M.ColNumber()),
                                   "math_Matrix::Set() - invalid indices");

  int II = M.LowerRow();
  for (int I = I1; I <= I2; I++)
  {
    int JJ = M.LowerCol();
    for (int J = J1; J <= J2; J++)
    {
      Array(I, J) = M.Array(II, JJ);
      JJ++;
    }
    II++;
  }
}

//==================================================================================================

inline void math_Matrix::SetDiag(const double Value)
{
  math_NotSquare_Raise_if(RowNumber() != ColNumber(),
                          "math_Matrix::SetDiag() - matrix is not square");

  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();

  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    Array(I, I) = Value;
  }
}

//==================================================================================================

inline math_Matrix math_Matrix::Transposed() const
{
  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  math_Matrix Result(aLowerCol, anUpperCol, aLowerRow, anUpperRow);

  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    for (int J = aLowerCol; J <= anUpperCol; J++)
    {
      Result.Array(J, I) = Array(I, J);
    }
  }
  return Result;
}

//==================================================================================================

inline void math_Matrix::Multiply(const math_Matrix& Left, const math_Matrix& Right)
{
  Standard_DimensionError_Raise_if(
    (Left.ColNumber() != Right.RowNumber()) || (RowNumber() != Left.RowNumber())
      || (ColNumber() != Right.ColNumber()),
    "math_Matrix::Multiply() - matrices have incompatible dimensions");

  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  double Som;
  int    I1 = Left.LowerRow();
  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    int J2 = Right.LowerCol();
    for (int J = aLowerCol; J <= anUpperCol; J++)
    {
      Som    = 0.0;
      int J1 = Left.LowerCol();
      int I2 = Right.LowerRow();
      for (int K = Left.LowerCol(); K <= Left.UpperCol(); K++)
      {
        Som = Som + Left.Array(I1, J1) * Right.Array(I2, J2);
        J1++;
        I2++;
      }
      Array(I, J) = Som;
      J2++;
    }
    I1++;
  }
}

//==================================================================================================

inline void math_Matrix::Multiply(const math_Matrix& Right)
{
  Standard_DimensionError_Raise_if(
    ColNumber() != Right.RowNumber(),
    "math_Matrix::Multiply() - input matrix has incompatible dimensions");

  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  // Create a temporary copy to avoid corrupting our own data during calculation
  math_Matrix aTemp = *this;
  if (this == &Right)
  {
    Multiply(aTemp, aTemp);
    return;
  }

  double Som;
  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    for (int J2 = Right.LowerCol(); J2 <= Right.UpperCol(); J2++)
    {
      Som    = 0.0;
      int I2 = Right.LowerRow();
      for (int J = aLowerCol; J <= anUpperCol; J++)
      {
        Som += aTemp.Array(I, J) * Right.Array(I2, J2);
        I2++;
      }
      Array(I, J2) = Som;
    }
  }
}

//==================================================================================================

inline math_Matrix math_Matrix::Multiplied(const math_Matrix& Right) const
{
  Standard_DimensionError_Raise_if(
    ColNumber() != Right.RowNumber(),
    "math_Matrix::Multiplied() - matrices have incompatible dimensions");

  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  math_Matrix Result(aLowerRow, anUpperRow, Right.LowerCol(), Right.UpperCol());

  double Som;
  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    for (int J2 = Right.LowerCol(); J2 <= Right.UpperCol(); J2++)
    {
      Som    = 0.0;
      int I2 = Right.LowerRow();
      for (int J = aLowerCol; J <= anUpperCol; J++)
      {
        Som = Som + Array(I, J) * Right.Array(I2, J2);
        I2++;
      }
      Result.Array(I, J2) = Som;
    }
  }
  return Result;
}

//==================================================================================================

inline math_Matrix math_Matrix::TMultiply(const math_Matrix& Right) const
{
  Standard_DimensionError_Raise_if(
    RowNumber() != Right.RowNumber(),
    "math_Matrix::TMultiply() - matrices have incompatible dimensions");

  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  math_Matrix Result(aLowerCol, anUpperCol, Right.LowerCol(), Right.UpperCol());

  double Som;
  for (int I = aLowerCol; I <= anUpperCol; I++)
  {
    for (int J2 = Right.LowerCol(); J2 <= Right.UpperCol(); J2++)
    {
      Som    = 0.0;
      int I2 = Right.LowerRow();
      for (int J = aLowerRow; J <= anUpperRow; J++)
      {
        Som = Som + Array(J, I) * Right.Array(I2, J2);
        I2++;
      }
      Result.Array(I, J2) = Som;
    }
  }
  return Result;
}

//==================================================================================================

inline void math_Matrix::TMultiply(const math_Matrix& TLeft, const math_Matrix& Right)
{
  Standard_DimensionError_Raise_if(
    (TLeft.RowNumber() != Right.RowNumber()) || (RowNumber() != TLeft.ColNumber())
      || (ColNumber() != Right.ColNumber()),
    "math_Matrix::TMultiply() - matrices have incompatible dimensions");

  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  double Som;
  int    I1 = TLeft.LowerCol();
  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    int J2 = Right.LowerCol();
    for (int J = aLowerCol; J <= anUpperCol; J++)
    {
      Som    = 0.0;
      int J1 = TLeft.LowerRow();
      int I2 = Right.LowerRow();
      for (int K = TLeft.LowerRow(); K <= TLeft.UpperRow(); K++)
      {
        Som = Som + TLeft.Array(J1, I1) * Right.Array(I2, J2);
        J1++;
        I2++;
      }
      Array(I, J) = Som;
      J2++;
    }
    I1++;
  }
}

//==================================================================================================

inline math_Matrix& math_Matrix::Initialized(const math_Matrix& Other)
{
  Standard_DimensionError_Raise_if(
    (RowNumber() != Other.RowNumber()) || (ColNumber() != Other.ColNumber()),
    "math_Matrix::Initialized() - input matrix has different dimensions");

  (Other.Array).Copy(Array);
  return *this;
}

//==================================================================================================

inline math_Matrix& math_Matrix::operator=(math_Matrix&& Other)
{
  if (this == &Other)
  {
    return *this;
  }

  if (Array.IsDeletable() && Other.Array.IsDeletable() && RowNumber() == Other.RowNumber()
      && ColNumber() == Other.ColNumber() && LowerRow() == Other.LowerRow()
      && LowerCol() == Other.LowerCol())
  {
    Array = std::move(Other.Array);
  }
  else
  {
    Initialized(Other);
  }
  return *this;
}

//==================================================================================================

inline void math_Matrix::Transpose()
{
  math_NotSquare_Raise_if(RowNumber() != ColNumber(),
                          "math_Matrix::Transpose() - matrix is not square");

  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  int Row = aLowerRow;
  int Col = aLowerCol;
  SetLowerCol(aLowerRow);
  double Temp;
  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    for (int J = I; J <= anUpperCol; J++)
    {
      Temp        = Array(I, J);
      Array(I, J) = Array(J, I);
      Array(J, I) = Temp;
    }
  }
  SetLowerRow(Col);
  SetLowerCol(Row);
}

//==================================================================================================

inline void math_Matrix::Dump(Standard_OStream& o) const
{
  const int aLowerRow  = Array.LowerRow();
  const int anUpperRow = Array.UpperRow();
  const int aLowerCol  = Array.LowerCol();
  const int anUpperCol = Array.UpperCol();

  o << "math_Matrix of RowNumber = " << RowNumber();
  o << " and ColNumber = " << ColNumber() << "\n";

  for (int I = aLowerRow; I <= anUpperRow; I++)
  {
    for (int J = aLowerCol; J <= anUpperCol; J++)
    {
      o << "math_Matrix ( " << I << ", " << J << " ) = ";
      o << Array(I, J) << "\n";
    }
  }
}


