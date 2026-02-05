#include <FEmTool_ElementaryCriterion.hpp>
#include <math_Matrix.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(FEmTool_ElementaryCriterion, Standard_Transient)

FEmTool_ElementaryCriterion::FEmTool_ElementaryCriterion()
    : myFirst(0.0),
      myLast(0.0)
{
}

void FEmTool_ElementaryCriterion::Set(const occ::handle<NCollection_HArray2<double>>& Coeff)
{
  myCoeff = Coeff;
}

void FEmTool_ElementaryCriterion::Set(const double FirstKnot, const double LastKnot)
{
  myFirst = FirstKnot;
  myLast  = LastKnot;
}
