#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <math_FunctionSet.hpp>
#include <math_Vector.hpp>
#include <PLib_HermitJacobi.hpp>

class FEmTool_ElementsOfRefMatrix : public math_FunctionSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT FEmTool_ElementsOfRefMatrix(const PLib_HermitJacobi& TheBase, const int DerOrder);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

private:
  PLib_HermitJacobi myBase;
  int               myDerOrder;
  int               myNbEquations;
};
