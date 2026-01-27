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

#include "math_Crout.hxx"
#include "math_Matrix.hxx"
#include "math_NotSquare.hxx"
#include "math_Vector.hxx"
#include "Standard_DimensionError.hxx"
#include "StdFail_NotDone.hxx"

// Eigen headers
// Suppress C++17 deprecation warnings for std::not1, std::unary_negate, etc.
#define _SILENCE_CXX17_NEGATORS_DEPRECATION_WARNING
#include <Eigen/Dense>
#include <Eigen/Cholesky>

// Helper type for Eigen matrix
using EigenMatrixXd = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
using EigenVectorXd = Eigen::Matrix<double, Eigen::Dynamic, 1>;
using EigenLDLT      = Eigen::LDLT<EigenMatrixXd>;

// Threshold for choosing between hand-written and Eigen implementations
constexpr Standard_Integer THE_EIGEN_THRESHOLD = 0;

//=================================================================================================
// Hand-written Crout implementation for small matrices (<= 10x10)
// Preserved from original implementation for optimal small matrix performance
//=================================================================================================
namespace
{
  void PerformHandWrittenCrout(const math_Matrix& A,
                            math_Matrix&       InvA,
                            Standard_Real&      Det,
                            const Standard_Real MinPivot)
  {
    Standard_Integer i, j, k;
    Standard_Integer Nctl = A.RowNumber();
    Standard_Integer lowr = A.LowerRow(), lowc = A.LowerCol();
    Standard_Real    scale;

    math_Matrix L(1, Nctl, 1, Nctl);
    math_Vector Diag(1, Nctl);

    // L*D*L^T decomposition
    for (i = 1; i <= Nctl; i++)
    {
      for (j = 1; j <= i - 1; j++)
      {
        scale = 0.0;
        for (k = 1; k <= j - 1; k++)
        {
          scale += L(i, k) * L(j, k) * Diag(k);
        }
        L(i, j) = (A(i + lowr - 1, j + lowc - 1) - scale) / Diag(j);
      }
      scale = 0.0;
      for (k = 1; k <= i - 1; k++)
      {
        scale += L(i, k) * L(i, k) * Diag(k);
      }
      Diag(i) = A(i + lowr - 1, i + lowc - 1) - scale;
      Det *= Diag(i);
      if (std::abs(Diag(i)) <= MinPivot)
      {
        throw StdFail_NotDone("Hand-written Crout: Matrix is singular");
      }
      L(i, i) = 1.0;
    }

    // Calculate inverse of L
    L(1, 1) = 1. / L(1, 1);
    for (i = 2; i <= Nctl; i++)
    {
      for (k = 1; k <= i - 1; k++)
      {
        scale = 0.0;
        for (j = k; j <= i - 1; j++)
        {
          scale += L(i, j) * L(j, k);
        }
        L(i, k) = -scale / L(i, i);
      }
      L(i, i) = 1. / L(i, i);
    }

    // Calculate inverse matrix
    for (j = 1; j <= Nctl; j++)
    {
      scale = L(j, j) * L(j, j) / Diag(j);
      for (k = j + 1; k <= Nctl; k++)
      {
        scale += L(k, j) * L(k, j) / Diag(k);
      }
      InvA(j, j) = scale;
      for (i = j + 1; i <= Nctl; i++)
      {
        scale = L(i, j) * L(i, i) / Diag(i);
        for (k = i + 1; k <= Nctl; k++)
        {
          scale += L(k, j) * L(k, i) / Diag(k);
        }
        InvA(i, j) = scale;
      }
    }
  }
} // namespace

//=================================================================================================
// Eigen LDLT implementation for large matrices (> 10x10)
// Uses highly optimized Eigen library for better performance
//=================================================================================================
namespace
{
  void PerformEigenLDLT(const math_Matrix& A,
                       math_Matrix&       InvA,
                       Standard_Real&      Det,
                       void*&              myLDLT,
                       const Standard_Real MinPivot)
  {
    Standard_Integer Nctl = A.RowNumber();
    Standard_Integer lowr = A.LowerRow(), lowc = A.LowerCol();

    // Create Eigen matrix from OCCT matrix (with proper row/col offset handling)
    EigenMatrixXd eigenMat(Nctl, Nctl);

    // Copy data from OCCT matrix to Eigen matrix
    for (Standard_Integer i = 0; i < Nctl; ++i)
    {
      for (Standard_Integer j = 0; j < Nctl; ++j)
      {
        eigenMat(i, j) = A(i + lowr, j + lowc);
      }
    }

    // Make symmetric (average upper and lower triangles)
    // The Crout algorithm assumes symmetric input
    for (Standard_Integer i = 0; i < Nctl; ++i)
    {
      for (Standard_Integer j = i + 1; j < Nctl; ++j)
      {
        double avg = 0.5 * (eigenMat(i, j) + eigenMat(j, i));
        eigenMat(i, j) = avg;
        eigenMat(j, i) = avg;
      }
    }

    // Perform LDLT decomposition using Eigen
    EigenLDLT* ldlt = new EigenLDLT();
    *ldlt      = eigenMat.ldlt();

    // Check if decomposition was successful
    if (ldlt->info() != Eigen::Success)
    {
      // Check if it failed due to pivot threshold
      if (!ldlt->isPositive())
      {
        delete ldlt;
        throw StdFail_NotDone("Eigen LDLT: Matrix is not positive definite");
      }

      // Additional check for minimum pivot
      const Eigen::VectorXd& D = ldlt->vectorD();
      for (int i = 0; i < Nctl; ++i)
      {
        if (std::abs(D(i)) <= MinPivot)
        {
          delete ldlt;
          throw StdFail_NotDone("Eigen LDLT: Pivot below threshold");
        }
      }
    }

    // Store the decomposition
    myLDLT = ldlt;

    // Compute determinant from diagonal elements
    const Eigen::VectorXd& D = ldlt->vectorD();
    Det = 1.0;
    for (int i = 0; i < Nctl; ++i)
    {
      Det *= D(i);
    }

    // Compute and cache the inverse matrix for backward compatibility
    EigenMatrixXd identity = EigenMatrixXd::Identity(Nctl, Nctl);
    EigenMatrixXd eigenInv    = ldlt->solve(identity);

    // Copy back to OCCT matrix
    for (Standard_Integer i = 0; i < Nctl; ++i)
    {
      for (Standard_Integer j = 0; j < Nctl; ++j)
      {
        InvA(i + 1, j + 1) = eigenInv(i, j);
      }
    }
  }
} // namespace

//=================================================================================================

math_Crout::math_Crout(const math_Matrix& A, const double MinPivot)
    : myLDLT(nullptr),
      InvA(1, A.RowNumber(), 1, A.ColNumber()),
      Done(Standard_False),
      Det(0.0),
      myDim(0),
      UseHandCrout(Standard_False)
{
  // Validate input is square
  Standard_Integer Nctl = A.RowNumber();
  math_NotSquare_Raise_if(Nctl != A.ColNumber(), "math_Crout: Matrix is not square");

  myDim = Nctl;

  try
  {
    // Choose implementation based on matrix size
    if (Nctl <= THE_EIGEN_THRESHOLD)
    {
      // Use hand-written Crout for small matrices (better performance)
      UseHandCrout = Standard_True;
      PerformHandWrittenCrout(A, InvA, Det, MinPivot);
    }
    else
    {
      // Use Eigen LDLT for large matrices (better performance)
      UseHandCrout = Standard_False;
      PerformEigenLDLT(A, InvA, Det, myLDLT, MinPivot);
    }
    Done = Standard_True;
  }
  catch (const StdFail_NotDone&)
  {
    Done = Standard_False;
    Det  = 0.0;
  }

}

//=================================================================================================

math_Crout::~math_Crout()
{
  if (myLDLT != nullptr)
  {
    delete static_cast<EigenLDLT*>(myLDLT);
    myLDLT = nullptr;
  }
}

//=================================================================================================
// Hand-written Solve for small matrices
//=================================================================================================
namespace
{
  void SolveHandWritten(const math_Matrix& InvA, const math_Vector& B, math_Vector& X)
  {
    Standard_Integer n    = InvA.RowNumber();
    Standard_Integer lowb = B.Lower();
    Standard_Integer lowx = X.Lower();
    Standard_Integer i, j;

    for (i = 1; i <= n; i++)
    {
      X(i + lowx - 1) = InvA(i, 1) * B(1 + lowb - 1);
      for (j = 2; j <= i; j++)
      {
        X(i + lowx - 1) += InvA(i, j) * B(j + lowb - 1);
      }
      for (j = i + 1; j <= n; j++)
      {
        X(i + lowx - 1) += InvA(j, i) * B(j + lowb - 1);
      }
    }
  }
} // namespace

//=================================================================================================
// Eigen LDLT Solve for large matrices
//=================================================================================================
namespace
{
  void SolveEigen(void* myLDLT, const math_Vector& B, math_Vector& X)
  {
    Standard_Integer n    = X.Length();
    Standard_Integer lowb = B.Lower();
    Standard_Integer lowx = X.Lower();

    // Create Eigen vector from OCCT vector
    EigenVectorXd eigenB(n);
    for (Standard_Integer i = 0; i < n; ++i)
    {
      eigenB(i) = B(i + lowb);
    }

    // Solve using Eigen's LDLT
    EigenLDLT* ldlt    = static_cast<EigenLDLT*>(myLDLT);
    EigenVectorXd eigenX = ldlt->solve(eigenB);

    // Copy result back to OCCT vector
    for (Standard_Integer i = 0; i < n; ++i)
    {
      X(i + lowx) = eigenX(i);
    }
  }
} // namespace

//=================================================================================================

void math_Crout::Solve(const math_Vector& B, math_Vector& X) const
{
  StdFail_NotDone_Raise_if(!Done, "math_Crout::Solve - Decomposition not done");
  Standard_DimensionError_Raise_if((B.Length() != InvA.RowNumber()) || (X.Length() != B.Length()),
                                   "math_Crout::Solve - Dimension error");

  // Choose Solve implementation based on which method was used for decomposition
  if (UseHandCrout)
  {
    SolveHandWritten(InvA, B, X);
  }
  else
  {
    SolveEigen(myLDLT, B, X);
  }
}

//=================================================================================================

void math_Crout::Dump(Standard_OStream& o) const
{
  o << "math_Crout ";
  if (Done)
  {
    o << " Status = Done\n";
    o << " Determinant = " << Det << "\n";
    o << " Dimension = " << myDim << "\n";
    if (UseHandCrout)
    {
      o << " Implementation = Hand-written Crout (small matrix)\n";
    }
    else
    {
      o << " Implementation = Eigen LDLT (large matrix)\n";
    }
  }
  else
  {
    o << " Status = not Done\n";
  }
}
