#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Real.hpp>
#include <math_Vector.hpp>
#include <NCollection_Array2.hpp>

//! This class finds eigenvalues and eigenvectors of real symmetric tridiagonal matrices.
//!
//! The implementation uses the QR algorithm with implicit shifts for numerical stability.
//! All computed eigenvalues are real (since the matrix is symmetric), and eigenvectors
//! are orthonormal. The class handles the complete eigendecomposition:
//! A * V = V * D, where A is the input matrix, V contains eigenvectors as columns,
//! and D is diagonal with eigenvalues.
//!
//! Key features:
//! - Robust QR algorithm implementation
//! - Numerical stability through implicit shifts
//! - Complete eigenvalue/eigenvector computation
//! - Proper handling of degenerate cases
class math_EigenValuesSearcher
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_EigenValuesSearcher(const NCollection_Array1<double>& theDiagonal,
                                           const NCollection_Array1<double>& theSubdiagonal);

  //! Returns true if computation is performed successfully.
  //! Computation may fail due to numerical issues or invalid input.
  Standard_EXPORT bool IsDone() const;

  //! Returns the dimension of the tridiagonal matrix.
  Standard_EXPORT int Dimension() const;

  //! Returns the specified eigenvalue.
  //! Eigenvalues are returned in the order they were computed by the algorithm,
  //! which may not be sorted. Use sorting if ordered eigenvalues are needed.
  //!
  //! @param theIndex index of the desired eigenvalue (1-based indexing)
  //! @return the eigenvalue at the specified index
  Standard_EXPORT double EigenValue(const int theIndex) const;

  //! Returns the specified eigenvector.
  //! The returned eigenvector is normalized and orthogonal to all other eigenvectors.
  //! The eigenvector satisfies: A * v = lambda * v, where A is the original matrix,
  //! v is the eigenvector, and lambda is the corresponding eigenvalue.
  //!
  //! @param theIndex index of the desired eigenvector (1-based indexing)
  //! @return the normalized eigenvector corresponding to EigenValue(theIndex)
  Standard_EXPORT math_Vector EigenVector(const int theIndex) const;

private:
  NCollection_Array1<double> myDiagonal;     //!< Copy of input diagonal elements
  NCollection_Array1<double> mySubdiagonal;  //!< Copy of input subdiagonal elements
  bool                       myIsDone;       //!< Computation success flag
  int                        myN;            //!< Matrix dimension
  NCollection_Array1<double> myEigenValues;  //!< Computed eigenvalues
  NCollection_Array2<double> myEigenVectors; //!< Computed eigenvectors stored column-wise
};

