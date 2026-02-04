#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_MultipleVarFunctionWithGradient.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <math_Vector.hpp>
#include <gp_Dir.hpp>

//! Function for search of cylinder canonic parameters: coordinates of center local coordinate
//! system, direction of axis and radius from set of points by least square method.
//!
//! The class inherits math_MultipleVarFunctionWithGradient and thus is intended
//! for use in math_BFGS algorithm.
//!
//! Parametrisation:
//! Cylinder is defined by its axis and radius. Axis is defined by 3 cartesian coordinates at
//! location x0, y0, z0 and direction, which is constant and set by user: dir.x, dir.y, dir.z The
//! criteria is: F(x0, y0, z0, theta, phi, R) = Sum[|(P(i) - Loc)^dir|^2 - R^2]^2 => min P(i) is
//! i-th sample point, Loc, dir - axis location and direction, R - radius
//!
//! The square vector product |(P(i) - Loc)^dir|^2 is:
//!
//! [(y - y0)*dir.z - (z - z0)*dir.y]^2 +
//! [(z - z0)*dir.x - (x - x0)*dir.z]^2 +
//! [(x - x0)*dir.y - (y - y0)*dir.x]^2
//!
//! First derivative of square vector product are:
//! Dx0 =  2*[(z - z0)*dir.x - (x - x0)*dir.z]*dir.z
//!       -2*[(x - x0)*dir.y - (y - y0)*dir.x]*dir.y
//! Dy0 = -2*[(y - y0)*dir.z - (z - z0)*dir.y]*dir.z
//!       +2*[(x - x0)*dir.y - (y - y0)*dir.x]*dir.x
//! Dz0 =  2*[(y - y0)*dir.z - (z - z0)*dir.y]*dir.y
//!       -2*[(z - z0)*dir.x - (x - x0)*dir.z]*dir.x
//!
//! dF/dx0 : G1(...) = 2*Sum{[...]*Dx0}
//! dF/dy0 : G2(...) = 2*Sum{[...]*Dy0}
//! dF/dz0 : G3(...) = 2*Sum{[...]*Dz0}
//! dF/dR : G4(...) = -4*R*Sum[...]
//! [...] = [|(P(i) - Loc)^dir|^2 - R^2]
class GeomConvert_FuncCylinderLSDist : public math_MultipleVarFunctionWithGradient
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor.
  Standard_EXPORT GeomConvert_FuncCylinderLSDist() = default;

  Standard_EXPORT GeomConvert_FuncCylinderLSDist(
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

  //! Gradient.
  Standard_EXPORT bool Gradient(const math_Vector& X, math_Vector& G) override;

  //! Value and gradient.
  Standard_EXPORT bool Values(const math_Vector& X, double& F, math_Vector& G) override;

private:
  occ::handle<NCollection_HArray1<gp_XYZ>> myPoints;
  gp_Dir                                   myDir;
};
