#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_MultipleVarFunctionWithGradient.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <math_Vector.hpp>

//! Function for search of sphere canonic parameters: coordinates of center and radius from set of
//! moints by least square method.
//! //!
//! The class inherits math_MultipleVarFunctionWithGradient and thus is intended
//! for use in math_BFGS algorithm.
//!
//! The criteria is:
//! F(x0, y0, z0, R) = Sum[(x(i) - x0)^2 + (y(i) - y0)^2 + (z(i) - z0)^2 - R^2]^2 => min,
//! x(i), y(i), z(i) - coordinates of sample points, x0, y0, z0, R - coordinates of center and
//! radius of sphere, which must be defined
//!
//! The first derivative are:
//! dF/dx0 : G1(x0, y0, z0, R) = -4*Sum{[...]*(x(i) - x0)}
//! dF/dy0 : G2(x0, y0, z0, R) = -4*Sum{[...]*(y(i) - y0)}
//! dF/dz0 : G3(x0, y0, z0, R) = -4*Sum{[...]*(z(i) - z0)}
//! dF/dR : G4(x0, y0, z0, R) = -4*R*Sum[...]
//! [...] = [(x(i) - x0)^2 + (y(i) - y0)^2 + (z(i) - z0)^2 - R^2]
//!
class GeomConvert_FuncSphereLSDist : public math_MultipleVarFunctionWithGradient
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor.
  Standard_EXPORT GeomConvert_FuncSphereLSDist() = default;

  Standard_EXPORT GeomConvert_FuncSphereLSDist(
    const occ::handle<NCollection_HArray1<gp_XYZ>>& thePoints);

  void SetPoints(const occ::handle<NCollection_HArray1<gp_XYZ>>& thePoints)
  {
    myPoints = thePoints;
  }

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
};
