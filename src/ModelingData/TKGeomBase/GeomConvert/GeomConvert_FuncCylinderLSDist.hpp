#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_MultipleVarFunctionWithGradient.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <math_Vector.hpp>
#include <gp_Dir.hpp>

class GeomConvert_FuncCylinderLSDist : public math_MultipleVarFunctionWithGradient
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomConvert_FuncCylinderLSDist() = default;

  Standard_EXPORT GeomConvert_FuncCylinderLSDist(
    const occ::handle<NCollection_HArray1<gp_XYZ>>& thePoints,
    const gp_Dir&                                   theDir);

  void SetPoints(const occ::handle<NCollection_HArray1<gp_XYZ>>& thePoints)
  {
    myPoints = thePoints;
  }

  void SetDir(const gp_Dir& theDir) { myDir = theDir; }

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT bool Value(const math_Vector& X, double& F) override;

  Standard_EXPORT bool Gradient(const math_Vector& X, math_Vector& G) override;

  Standard_EXPORT bool Values(const math_Vector& X, double& F, math_Vector& G) override;

private:
  occ::handle<NCollection_HArray1<gp_XYZ>> myPoints;
  gp_Dir                                   myDir;
};
