#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_MultipleVarFunctionWithGradient.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <math_Vector.hpp>

class GeomConvert_FuncSphereLSDist : public math_MultipleVarFunctionWithGradient
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomConvert_FuncSphereLSDist() = default;

  Standard_EXPORT GeomConvert_FuncSphereLSDist(
    const occ::handle<NCollection_HArray1<gp_XYZ>>& thePoints);

  void SetPoints(const occ::handle<NCollection_HArray1<gp_XYZ>>& thePoints)
  {
    myPoints = thePoints;
  }

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT bool Value(const math_Vector& X, double& F) override;

  Standard_EXPORT bool Gradient(const math_Vector& X, math_Vector& G) override;

  Standard_EXPORT bool Values(const math_Vector& X, double& F, math_Vector& G) override;

private:
  occ::handle<NCollection_HArray1<gp_XYZ>> myPoints;
};
