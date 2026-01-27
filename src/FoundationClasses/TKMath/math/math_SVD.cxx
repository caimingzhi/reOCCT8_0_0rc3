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

// #ifndef OCCT_DEBUG
#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError
// #endif

#include <math_SVD.hxx>
#include <math_Matrix.hxx>
#include <Standard_DimensionError.hxx>
#include <Standard_NotImplemented.hxx>
#include <StdFail_NotDone.hxx>

#include <Standard_WarningsDisable.hxx>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <Standard_WarningsRestore.hxx>

#include <algorithm>

math_SVD::math_SVD(const math_Matrix& A)
    : U(1, A.RowNumber(), 1, std::min(A.RowNumber(), A.ColNumber())),
      V(1, A.ColNumber(), 1, std::min(A.RowNumber(), A.ColNumber())),
      Diag(1, std::min(A.RowNumber(), A.ColNumber())),
      RowA(A.RowNumber())
{
    // Use Thin SVD: A = U * S * V^T
    // U is M x K, S is K, V is N x K where K = min(M, N)
    
    const Standard_Integer aRows = A.RowNumber();
    const Standard_Integer aCols = A.ColNumber();

    // Copy input matrix A to Eigen matrix (safe approach, avoids memory layout issues)
    Eigen::Matrix<Standard_Real, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> aMatA(aRows, aCols);
    for (Standard_Integer i = 0; i < aRows; ++i) {
        for (Standard_Integer j = 0; j < aCols; ++j) {
            aMatA(i, j) = A(A.LowerRow() + i, A.LowerCol() + j);
        }
    }

    // Compute SVD
    Eigen::BDCSVD<Eigen::Matrix<Standard_Real, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> 
        aSVD(aMatA, Eigen::ComputeThinU | Eigen::ComputeThinV);

    // Note: BDCSVD always succeeds for real matrices, no need for info() check

    // Store results in member variables
    const auto& aU = aSVD.matrixU();
    const auto& aV = aSVD.matrixV();
    const auto& aS = aSVD.singularValues();

    // Copy U
    for (Standard_Integer i = 0; i < static_cast<Standard_Integer>(aU.rows()); ++i) {
        for (Standard_Integer j = 0; j < static_cast<Standard_Integer>(aU.cols()); ++j) {
            U(i + 1, j + 1) = aU(i, j);
        }
    }

    // Copy V
    for (Standard_Integer i = 0; i < static_cast<Standard_Integer>(aV.rows()); ++i) {
        for (Standard_Integer j = 0; j < static_cast<Standard_Integer>(aV.cols()); ++j) {
            V(i + 1, j + 1) = aV(i, j);
        }
    }

    // Copy Singular Values
    for (Standard_Integer i = 0; i < static_cast<Standard_Integer>(aS.size()); ++i) {
        Diag(i + 1) = aS(i);
    }

    Done = Standard_True;
}

void math_SVD::Solve(const math_Vector& B, math_Vector& X, const double Eps)
{
    StdFail_NotDone_Raise_if(!Done, "math_SVD::Solve");
    Standard_DimensionError_Raise_if((RowA != B.Length()) || (X.Length() != V.RowNumber()), 
        "math_SVD::Solve: dimensions mismatch");

    // Solution X = V * S_inv * U^T * B

    const Standard_Integer nRows = U.RowNumber();
    const Standard_Integer nCols = V.RowNumber();
    const Standard_Integer nRank = Diag.Length();

    // Copy U, V, Diag to Eigen matrices for computation
    Eigen::Matrix<Standard_Real, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> matU(nRows, nRank);
    Eigen::Matrix<Standard_Real, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> matV(nCols, nRank);
    Eigen::VectorXd vecS(nRank);
    Eigen::VectorXd vecB(B.Length());

    for (Standard_Integer i = 0; i < nRows; ++i) {
        for (Standard_Integer j = 0; j < nRank; ++j) {
            matU(i, j) = U(i + 1, j + 1);
        }
    }

    for (Standard_Integer i = 0; i < nCols; ++i) {
        for (Standard_Integer j = 0; j < nRank; ++j) {
            matV(i, j) = V(i + 1, j + 1);
        }
    }

    for (Standard_Integer i = 0; i < nRank; ++i) {
        vecS(i) = Diag(i + 1);
    }

    for (Standard_Integer i = 0; i < B.Length(); ++i) {
        vecB(i) = B(B.Lower() + i);
    }

    // Apply tolerance: set small singular values to zero
    Standard_Real wmin = Eps * vecS.maxCoeff();
    Eigen::VectorXd vecSInv = Eigen::VectorXd::Zero(nRank);
    for (Standard_Integer i = 0; i < nRank; ++i) {
        if (vecS(i) > wmin) {
            vecSInv(i) = 1.0 / vecS(i);
        }
    }

    // Compute X = V * S_inv * U^T * B
    Eigen::VectorXd utb = matU.transpose() * vecB;
    Eigen::VectorXd sutb = vecSInv.asDiagonal() * utb;
    Eigen::VectorXd vecX = matV * sutb;

    // Copy result back to X
    for (Standard_Integer i = 0; i < X.Length(); ++i) {
        X(X.Lower() + i) = vecX(i);
    }
}

void math_SVD::PseudoInverse(math_Matrix& Result, const double Eps)
{
    StdFail_NotDone_Raise_if(!Done, "math_SVD::PseudoInverse");
    Standard_DimensionError_Raise_if(Result.RowNumber() != V.RowNumber() || Result.ColNumber() != U.RowNumber(),
        "math_SVD::PseudoInverse: Result matrix dimensions mismatch");

    const Standard_Integer nRows = U.RowNumber(); // M
    const Standard_Integer nCols = V.RowNumber(); // N
    const Standard_Integer nRank = Diag.Length();

    Eigen::Matrix<Standard_Real, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> matU(nRows, nRank);
    Eigen::Matrix<Standard_Real, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> matV(nCols, nRank);
    Eigen::VectorXd vecS(nRank);

    for (Standard_Integer i = 0; i < nRows; ++i) {
        for (Standard_Integer j = 0; j < nRank; ++j) {
            matU(i, j) = U(i + 1, j + 1);
        }
    }

    for (Standard_Integer i = 0; i < nCols; ++i) {
        for (Standard_Integer j = 0; j < nRank; ++j) {
            matV(i, j) = V(i + 1, j + 1);
        }
    }

    for (Standard_Integer i = 0; i < nRank; ++i) {
        vecS(i) = Diag(i + 1);
    }

    Standard_Real wmin = Eps * vecS.maxCoeff();
    Eigen::VectorXd vecSInv = Eigen::VectorXd::Zero(nRank);
    for (Standard_Integer i = 0; i < nRank; ++i) {
        if (vecS(i) > wmin) {
            vecSInv(i) = 1.0 / vecS(i);
        }
    }

    // PseudoInv = V * S_inv * U^T
    Eigen::Matrix<Standard_Real, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> inv 
        = matV * vecSInv.asDiagonal() * matU.transpose();

    for (Standard_Integer i = 0; i < Result.RowNumber(); ++i) {
        for (Standard_Integer j = 0; j < Result.ColNumber(); ++j) {
            Result(Result.LowerRow() + i, Result.LowerCol() + j) = inv(i, j);
        }
    }
}

void math_SVD::Dump(Standard_OStream& o) const
{
    o << "math_SVD";
    if (Done)
    {
        o << " Status = Done \n";
        o << " Singular values: " << Diag << "\n";
    }
    else
    {
        o << " Status = not Done \n";
    }
}
