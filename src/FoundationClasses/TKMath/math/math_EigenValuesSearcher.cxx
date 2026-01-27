// Created on: 2005-12-15
// Created by: Julia GERASIMOVA
// Copyright (c) 2005-2014 OPEN CASCADE SAS
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

#include <math_EigenValuesSearcher.hxx>

#include <StdFail_NotDone.hxx>
#include <Standard_OutOfRange.hxx>

// Eigen includes
#include <Eigen/Core>
#include <Eigen/Eigenvalues>

//=======================================================================

math_EigenValuesSearcher::math_EigenValuesSearcher(const NCollection_Array1<double>& theDiagonal,
                                                   const NCollection_Array1<double>& theSubdiagonal)
    : myIsDone(Standard_False),
      myN(theDiagonal.Length()),
      myEigenValues(1, theDiagonal.Length()),
      myEigenVectors(1, theDiagonal.Length(), 1, theDiagonal.Length())
{
  if (theSubdiagonal.Length() != myN)
  {
    return;
  }

  if (myN == 0)
  {
    myIsDone = Standard_True;
    return;
  }

  // Handle N=1 case separately
  if (myN == 1)
  {
    myEigenValues(1) = theDiagonal(theDiagonal.Lower());
    myEigenVectors(1, 1) = 1.0;
    myIsDone = Standard_True;
    return;
  }

  // Prepare data for Eigen
  // Eigen expects subdiagonal of size N-1
  // OCCT 'theSubdiagonal' input stores relevant data in indices 2..N (corresponding to connections 1-2, 2-3, etc)
  // which generally corresponds to input indices [Lower+1, Lower+N-1].
  
  Eigen::VectorXd aDiag(myN);
  Eigen::VectorXd aSubDiag(myN - 1);

  const Standard_Integer aDiagLower = theDiagonal.Lower();
  for (Standard_Integer i = 0; i < myN; ++i)
  {
    aDiag[i] = theDiagonal(aDiagLower + i);
  }

  const Standard_Integer aSubDiagLower = theSubdiagonal.Lower();
  for (Standard_Integer i = 0; i < myN - 1; ++i)
  {
    // We skip the first element of the subdiagonal array relative to the loop,
    // matching the original logic where input[Lower] was effectively unused/dummy
    // and input[Lower+1] corresponded to the first subdiagonal element.
    aSubDiag[i] = theSubdiagonal(aSubDiagLower + i + 1);
  }

  // Compute using Eigen
  Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> anEigenSolver;
  anEigenSolver.computeFromTridiagonal(aDiag, aSubDiag, Eigen::ComputeEigenvectors);

  if (anEigenSolver.info() != Eigen::Success)
  {
    myIsDone = Standard_False;
    return;
  }

  // Store results
  // Eigen returns eigenvalues in increasing order
  const Eigen::VectorXd& aResValues = anEigenSolver.eigenvalues();
  const Eigen::MatrixXd& aResVectors = anEigenSolver.eigenvectors();

  for (Standard_Integer i = 0; i < myN; ++i)
  {
    myEigenValues(i + 1) = aResValues[i];
  }

  for (Standard_Integer aRow = 0; aRow < myN; ++aRow)
  {
    for (Standard_Integer aCol = 0; aCol < myN; ++aCol)
    {
      // Eigen vectors are stored as columns
      myEigenVectors(aRow + 1, aCol + 1) = aResVectors(aRow, aCol);
    }
  }

  myIsDone = Standard_True;
}

//=======================================================================

bool math_EigenValuesSearcher::IsDone() const
{
  return myIsDone;
}

//=======================================================================

int math_EigenValuesSearcher::Dimension() const
{
  return myN;
}

//=======================================================================

double math_EigenValuesSearcher::EigenValue(const int theIndex) const
{
  StdFail_NotDone_Raise_if(!myIsDone, "math_EigenValuesSearcher::EigenValue() - computation is not done");
  Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > myN,
                               "math_EigenValuesSearcher::EigenValue() - index out of range");
  return myEigenValues(theIndex);
}

//=======================================================================

math_Vector math_EigenValuesSearcher::EigenVector(const int theIndex) const
{
  StdFail_NotDone_Raise_if(!myIsDone, "math_EigenValuesSearcher::EigenVector() - computation is not done");
  Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > myN,
                               "math_EigenValuesSearcher::EigenVector() - index out of range");
  math_Vector aVector(1, myN);

  for (int anIdx = 1; anIdx <= myN; anIdx++)
    aVector(anIdx) = myEigenVectors(anIdx, theIndex);

  return aVector;
}