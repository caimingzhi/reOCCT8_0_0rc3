#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <Standard_OStream.hpp>

//! This class implements the Jacobi method to find the eigenvalues and
//! the eigenvectors of a real symmetric square matrix.
//! A sort of eigenvalues is done.
class math_Jacobi
{
public:
  DEFINE_STANDARD_ALLOC

  //! Given a Real n X n matrix A, this constructor computes all its
  //! eigenvalues and eigenvectors using the Jacobi method.
  //! The exception NotSquare is raised if the matrix is not square.
  //! No verification that the matrix A is really symmetric is done.
  Standard_EXPORT math_Jacobi(const math_Matrix& A);

  //! Returns true if the computations are successful, otherwise returns false.
  bool IsDone() const;

  //! Returns the eigenvalues vector.
  //! Exception NotDone is raised if calculation is not done successfully.
  const math_Vector& Values() const;

  //! returns the eigenvalue number Num.
  //! Eigenvalues are in the range (1..n).
  //! Exception NotDone is raised if calculation is not done successfully.
  double Value(const int Num) const;

  //! returns the eigenvectors matrix.
  //! Exception NotDone is raised if calculation is not done successfully.
  const math_Matrix& Vectors() const;

  //! Returns the eigenvector V of number Num.
  //! Eigenvectors are in the range (1..n).
  //! Exception NotDone is raised if calculation is not done successfully.
  void Vector(const int Num, math_Vector& V) const;

  //! Prints information on the current state of the object.
  //! Is used to redefine the operator <<.
  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  bool        Done;
  math_Matrix AA;
  int         NbRotations;
  math_Vector EigenValues;
  math_Matrix EigenVectors;
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

// math_Jacobi_1.hpp

#include <StdFail_NotDone.hpp>
#include <math_Vector.hpp>
#include <math_Matrix.hpp>

inline bool math_Jacobi::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_Jacobi& J)
{
  J.Dump(o);
  return o;
}

inline const math_Vector& math_Jacobi::Values() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return EigenValues;
}

inline double math_Jacobi::Value(const int Num) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return EigenValues(Num);
}

inline const math_Matrix& math_Jacobi::Vectors() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return EigenVectors;
}

inline void math_Jacobi::Vector(const int Num, math_Vector& V) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  V = EigenVectors.Col(Num);
}


