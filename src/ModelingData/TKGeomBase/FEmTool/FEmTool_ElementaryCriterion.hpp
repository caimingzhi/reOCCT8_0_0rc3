#pragma once

#include <Standard.hpp>

#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <Standard_Real.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <math_Vector.hpp>
class math_Matrix;

class FEmTool_ElementaryCriterion : public Standard_Transient
{

public:
  Standard_EXPORT FEmTool_ElementaryCriterion();

  Standard_EXPORT void Set(const occ::handle<NCollection_HArray2<double>>& Coeff);

  Standard_EXPORT virtual void Set(const double FirstKnot, const double LastKnot);

  Standard_EXPORT virtual occ::handle<NCollection_HArray2<int>> DependenceTable() const = 0;

  Standard_EXPORT virtual double Value() = 0;

  Standard_EXPORT virtual void Hessian(const int Dim1, const int Dim2, math_Matrix& H) = 0;

  Standard_EXPORT virtual void Gradient(const int Dim, math_Vector& G) = 0;

  DEFINE_STANDARD_RTTIEXT(FEmTool_ElementaryCriterion, Standard_Transient)

protected:
  occ::handle<NCollection_HArray2<double>> myCoeff;
  double                                   myFirst;
  double                                   myLast;
};
