#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <math_Vector.hpp>
class math_Matrix;

class BlendFunc_Tensor
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BlendFunc_Tensor(const int NbRow, const int NbCol, const int NbMat);

  Standard_EXPORT void Init(const double InitialValue);

  const double& Value(const int Row, const int Col, const int Mat) const;

  const double& operator()(const int Row, const int Col, const int Mat) const
  {
    return Value(Row, Col, Mat);
  }

  double& ChangeValue(const int Row, const int Col, const int Mat);

  double& operator()(const int Row, const int Col, const int Mat)
  {
    return ChangeValue(Row, Col, Mat);
  }

  Standard_EXPORT void Multiply(const math_Vector& Right, math_Matrix& Product) const;

private:
  NCollection_Array1<double> Tab;
  int                        nbrow;
  int                        nbcol;
  int                        nbmat;
  int                        nbmtcl;
};

inline const double& BlendFunc_Tensor::Value(const int Row, const int Col, const int Mat) const
{
  return Tab(Mat + nbmat * (Col - 1) + nbmtcl * (Row - 1));
}

inline double& BlendFunc_Tensor::ChangeValue(const int Row, const int Col, const int Mat)
{
  return Tab(Mat + nbmat * (Col - 1) + nbmtcl * (Row - 1));
}
