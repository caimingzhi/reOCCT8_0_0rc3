#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AdvApprox_ApproxAFunction.hpp>
#include <Standard_Integer.hpp>
class Geom2d_BSplineCurve;
class Geom_BSplineCurve;

class GeomLib_MakeCurvefromApprox
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomLib_MakeCurvefromApprox(const AdvApprox_ApproxAFunction& Approx);

  bool IsDone() const;

  Standard_EXPORT int Nb1DSpaces() const;

  Standard_EXPORT int Nb2DSpaces() const;

  Standard_EXPORT int Nb3DSpaces() const;

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Curve2d(const int Index2d) const;

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Curve2dFromTwo1d(const int Index1d,
                                                                    const int Index2d) const;

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Curve2d(const int Index1d,
                                                           const int Index2d) const;

  Standard_EXPORT occ::handle<Geom_BSplineCurve> Curve(const int Index3d) const;

  Standard_EXPORT occ::handle<Geom_BSplineCurve> Curve(const int Index1D, const int Index3D) const;

private:
  AdvApprox_ApproxAFunction myApprox;
};

inline bool GeomLib_MakeCurvefromApprox::IsDone() const
{
  return myApprox.IsDone();
}
