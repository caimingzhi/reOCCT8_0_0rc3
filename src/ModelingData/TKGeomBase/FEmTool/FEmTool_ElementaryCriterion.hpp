#pragma once


#include <Standard.hpp>

#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <Standard_Real.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <math_Vector.hpp>
class math_Matrix;

//! defined J Criteria to used in minimisation
class FEmTool_ElementaryCriterion : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT FEmTool_ElementaryCriterion();

  //! Set the coefficient of the Element (the Curve)
  Standard_EXPORT void Set(const occ::handle<NCollection_HArray2<double>>& Coeff);

  //! Set the definition interval of the Element
  Standard_EXPORT virtual void Set(const double FirstKnot, const double LastKnot);

  //! To know if two dimension are independent.
  Standard_EXPORT virtual occ::handle<NCollection_HArray2<int>> DependenceTable() const = 0;

  //! To Compute J(E) where E is the current Element
  Standard_EXPORT virtual double Value() = 0;

  //! To Compute J(E) the coefficients of Hessian matrix of
  //! J(E) which are crossed derivatives in dimensions <Dim1>
  //! and <Dim2>.
  //! If DependenceTable(Dimension1,Dimension2) is False
  Standard_EXPORT virtual void Hessian(const int Dim1, const int Dim2, math_Matrix& H) = 0;

  //! To Compute the coefficients in the dimension <dim>
  //! of the J(E)'s Gradient where E is the current Element
  Standard_EXPORT virtual void Gradient(const int Dim, math_Vector& G) = 0;

  DEFINE_STANDARD_RTTIEXT(FEmTool_ElementaryCriterion, Standard_Transient)

protected:
  occ::handle<NCollection_HArray2<double>> myCoeff;
  double                                   myFirst;
  double                                   myLast;
};

