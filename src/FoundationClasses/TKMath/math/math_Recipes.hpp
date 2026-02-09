#pragma once

#include <Message_ProgressRange.hpp>

#include <NCollection_Allocator.hpp>

template <typename T>
class math_VectorBase;
using math_IntegerVector = math_VectorBase<int>;
using math_Vector        = math_VectorBase<double>;
class math_Matrix;

const int math_Status_UserAborted    = -1;
const int math_Status_OK             = 0;
const int math_Status_SingularMatrix = 1;
const int math_Status_ArgumentError  = 2;
const int math_Status_NoConvergence  = 3;

Standard_EXPORT int LU_Decompose(
  math_Matrix&                 a,
  math_IntegerVector&          indx,
  double&                      d,
  double                       TINY        = 1.0e-20,
  const Message_ProgressRange& theProgress = Message_ProgressRange());

Standard_EXPORT int LU_Decompose(
  math_Matrix&                 a,
  math_IntegerVector&          indx,
  double&                      d,
  math_Vector&                 vv,
  double                       TINY        = 1.0e-30,
  const Message_ProgressRange& theProgress = Message_ProgressRange());

Standard_EXPORT void LU_Solve(const math_Matrix& a, const math_IntegerVector& indx, math_Vector& b);

Standard_EXPORT int LU_Invert(math_Matrix& a);

Standard_EXPORT int SVD_Decompose(math_Matrix& a, math_Vector& w, math_Matrix& v);

Standard_EXPORT int SVD_Decompose(math_Matrix& a, math_Vector& w, math_Matrix& v, math_Vector& rv1);

Standard_EXPORT void SVD_Solve(const math_Matrix& u,
                               const math_Vector& w,
                               const math_Matrix& v,
                               const math_Vector& b,
                               math_Vector&       x);

Standard_EXPORT int DACTCL_Decompose(math_Vector&              a,
                                     const math_IntegerVector& indx,
                                     const double              MinPivot = 1.e-20);

Standard_EXPORT int DACTCL_Solve(const math_Vector&        a,
                                 math_Vector&              b,
                                 const math_IntegerVector& indx,
                                 const double              MinPivot = 1.e-20);

Standard_EXPORT int Jacobi(math_Matrix& a, math_Vector& d, math_Matrix& v, int& nrot);
