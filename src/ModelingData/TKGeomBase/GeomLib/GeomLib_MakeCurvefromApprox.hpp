#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AdvApprox_ApproxAFunction.hpp>
#include <Standard_Integer.hpp>
class Geom2d_BSplineCurve;
class Geom_BSplineCurve;

//! this class is used to construct the BSpline curve
//! from an Approximation (ApproxAFunction from AdvApprox).
class GeomLib_MakeCurvefromApprox
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomLib_MakeCurvefromApprox(const AdvApprox_ApproxAFunction& Approx);

  bool IsDone() const;

  //! returns the number of 1D spaces of the Approx
  Standard_EXPORT int Nb1DSpaces() const;

  //! returns the number of 3D spaces of the Approx
  Standard_EXPORT int Nb2DSpaces() const;

  //! returns the number of 3D spaces of the Approx
  Standard_EXPORT int Nb3DSpaces() const;

  //! returns a polynomial curve whose poles correspond to
  //! the Index2d 2D space
  //! if Index2d not in the Range [1,Nb2dSpaces]
  //! if the Approx is not Done
  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Curve2d(const int Index2d) const;

  //! returns a 2D curve building it from the 1D curve
  //! in x at Index1d and y at Index2d amongst the
  //! 1D curves
  //! if Index1d not in the Range [1,Nb1dSpaces]
  //! if Index2d not in the Range [1,Nb1dSpaces]
  //! if the Approx is not Done
  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Curve2dFromTwo1d(const int Index1d,
                                                                    const int Index2d) const;

  //! returns a rational curve whose poles correspond to
  //! the index2d of the 2D space and whose weights correspond
  //! to one dimensional space of index 1d
  //! if Index1d not in the Range [1,Nb1dSpaces]
  //! if Index2d not in the Range [1,Nb2dSpaces]
  //! if the Approx is not Done
  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Curve2d(const int Index1d,
                                                           const int Index2d) const;

  //! returns a polynomial curve whose poles correspond to
  //! the Index3D 3D space
  //! if Index3D not in the Range [1,Nb3dSpaces]
  //! if the Approx is not Done
  Standard_EXPORT occ::handle<Geom_BSplineCurve> Curve(const int Index3d) const;

  //! returns a rational curve whose poles correspond to
  //! the index3D of the 3D space and whose weights correspond
  //! to the index1d 1D space.
  //! if Index1D not in the Range [1,Nb1dSpaces]
  //! if Index3D not in the Range [1,Nb3dSpaces]
  //! if the Approx is not Done
  Standard_EXPORT occ::handle<Geom_BSplineCurve> Curve(const int Index1D, const int Index3D) const;

private:
  AdvApprox_ApproxAFunction myApprox;
};

inline bool GeomLib_MakeCurvefromApprox::IsDone() const
{
  return myApprox.IsDone();
}
