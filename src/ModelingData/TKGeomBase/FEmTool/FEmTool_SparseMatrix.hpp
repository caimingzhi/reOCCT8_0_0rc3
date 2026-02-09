#pragma once

#include <Standard.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <math_Vector.hpp>

class FEmTool_SparseMatrix : public Standard_Transient
{

public:
  Standard_EXPORT virtual void Init(const double Value) = 0;

  Standard_EXPORT virtual double& ChangeValue(const int I, const int J) = 0;

  Standard_EXPORT virtual bool Decompose() = 0;

  Standard_EXPORT virtual void Solve(const math_Vector& B, math_Vector& X) const = 0;

  Standard_EXPORT virtual bool Prepare() = 0;

  Standard_EXPORT virtual void Solve(const math_Vector& B,
                                     const math_Vector& Init,
                                     math_Vector&       X,
                                     math_Vector&       Residual,
                                     const double       Tolerance    = 1.0e-8,
                                     const int          NbIterations = 50) const = 0;

  Standard_EXPORT virtual void Multiplied(const math_Vector& X, math_Vector& MX) const = 0;

  Standard_EXPORT virtual int RowNumber() const = 0;

  Standard_EXPORT virtual int ColNumber() const = 0;

  DEFINE_STANDARD_RTTIEXT(FEmTool_SparseMatrix, Standard_Transient)
};
