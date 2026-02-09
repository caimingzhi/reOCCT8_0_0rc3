#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <FEmTool_SparseMatrix.hpp>
#include <Standard_Real.hpp>
#include <math_Vector.hpp>

class FEmTool_ProfileMatrix : public FEmTool_SparseMatrix
{

public:
  Standard_EXPORT FEmTool_ProfileMatrix(const NCollection_Array1<int>& FirstIndexes);

  Standard_EXPORT void Init(const double Value) override;

  Standard_EXPORT double& ChangeValue(const int I, const int J) override;

  Standard_EXPORT bool Decompose() override;

  Standard_EXPORT void Solve(const math_Vector& B, math_Vector& X) const override;

  Standard_EXPORT bool Prepare() override;

  Standard_EXPORT void Solve(const math_Vector& B,
                             const math_Vector& Init,
                             math_Vector&       X,
                             math_Vector&       Residual,
                             const double       Tolerance    = 1.0e-8,
                             const int          NbIterations = 50) const override;

  Standard_EXPORT void Multiplied(const math_Vector& X, math_Vector& MX) const override;

  Standard_EXPORT int RowNumber() const override;

  Standard_EXPORT int ColNumber() const override;

  Standard_EXPORT bool IsInProfile(const int i, const int j) const;

  Standard_EXPORT void OutM() const;

  Standard_EXPORT void OutS() const;

  DEFINE_STANDARD_RTTIEXT(FEmTool_ProfileMatrix, FEmTool_SparseMatrix)

private:
  NCollection_Array2<int>                  profile;
  occ::handle<NCollection_HArray1<double>> ProfileMatrix;
  occ::handle<NCollection_HArray1<double>> SMatrix;
  occ::handle<NCollection_HArray1<int>>    NextCoeff;
  bool                                     IsDecomp;
};
