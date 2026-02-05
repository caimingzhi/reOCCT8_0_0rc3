#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_MultipleVarFunction.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <math_Vector.hpp>
#include <gp_Dir.hpp>

//! Function for search of Cone canonic parameters: coordinates of center local coordinate system,
//! direction of axis, radius and semi-angle from set of points
//! by least square method.
class GeomConvert_FuncConeLSDist : public math_MultipleVarFunction
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor.
  Standard_EXPORT GeomConvert_FuncConeLSDist() = default;

  Standard_EXPORT GeomConvert_FuncConeLSDist(
    const occ::handle<NCollection_HArray1<gp_XYZ>>& thePoints,
    const gp_Dir&                                   theDir);

  void SetPoints(const occ::handle<NCollection_HArray1<gp_XYZ>>& thePoints)
  {
    myPoints = thePoints;
  }

  void SetDir(const gp_Dir& theDir) { myDir = theDir; }

  //! Number of variables.
  Standard_EXPORT int NbVariables() const override;

  //! Value.
  Standard_EXPORT bool Value(const math_Vector& X, double& F) override;

private:
  occ::handle<NCollection_HArray1<gp_XYZ>> myPoints;
  gp_Dir                                   myDir;
};
