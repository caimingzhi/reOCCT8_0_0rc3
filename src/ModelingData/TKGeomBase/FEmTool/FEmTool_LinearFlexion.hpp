#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <math_Matrix.hpp>
#include <Standard_Integer.hpp>
#include <FEmTool_ElementaryCriterion.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <math_Vector.hpp>

//! Criterium of LinearFlexion To Hermit-Jacobi elements
class FEmTool_LinearFlexion : public FEmTool_ElementaryCriterion
{

public:
  Standard_EXPORT FEmTool_LinearFlexion(const int WorkDegree, const GeomAbs_Shape ConstraintOrder);

  Standard_EXPORT occ::handle<NCollection_HArray2<int>> DependenceTable() const override;

  Standard_EXPORT double Value() override;

  Standard_EXPORT void Hessian(const int Dimension1, const int Dimension2, math_Matrix& H) override;

  Standard_EXPORT void Gradient(const int Dimension, math_Vector& G) override;

  DEFINE_STANDARD_RTTIEXT(FEmTool_LinearFlexion, FEmTool_ElementaryCriterion)

private:
  math_Matrix RefMatrix;
  int         myOrder;
};
