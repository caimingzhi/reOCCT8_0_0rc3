#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Approx_SweepApproximation.hpp>
#include <AppBlend_Approx.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_OStream.hpp>
class Approx_SweepFunction;

//! Used to Approximate the blending surfaces.
class BRepBlend_AppSurface : public AppBlend_Approx
{
public:
  DEFINE_STANDARD_ALLOC

  //! Approximation of the new Surface (and
  //! eventually the 2d Curves on the support
  //! surfaces).
  //! Normally the 2d curve are
  //! approximated with a tolerance given by the
  //! resolution on support surfaces, but if this
  //! tolerance is too large Tol2d is used.
  Standard_EXPORT BRepBlend_AppSurface(const occ::handle<Approx_SweepFunction>& Funct,
                                       const double                             First,
                                       const double                             Last,
                                       const double                             Tol3d,
                                       const double                             Tol2d,
                                       const double                             TolAngular,
                                       const GeomAbs_Shape Continuity = GeomAbs_C0,
                                       const int           Degmax     = 11,
                                       const int           Segmax     = 50);

  bool IsDone() const override;

  Standard_EXPORT void SurfShape(int& UDegree,
                                 int& VDegree,
                                 int& NbUPoles,
                                 int& NbVPoles,
                                 int& NbUKnots,
                                 int& NbVKnots) const override;

  Standard_EXPORT void Surface(NCollection_Array2<gp_Pnt>& TPoles,
                               NCollection_Array2<double>& TWeights,
                               NCollection_Array1<double>& TUKnots,
                               NCollection_Array1<double>& TVKnots,
                               NCollection_Array1<int>&    TUMults,
                               NCollection_Array1<int>&    TVMults) const override;

  int UDegree() const override;

  int VDegree() const override;

  const NCollection_Array2<gp_Pnt>& SurfPoles() const override;

  const NCollection_Array2<double>& SurfWeights() const override;

  const NCollection_Array1<double>& SurfUKnots() const override;

  const NCollection_Array1<double>& SurfVKnots() const override;

  const NCollection_Array1<int>& SurfUMults() const override;

  const NCollection_Array1<int>& SurfVMults() const override;

  //! returns the maximum error in the surface approximation.
  Standard_EXPORT double MaxErrorOnSurf() const;

  int NbCurves2d() const override;

  Standard_EXPORT void Curves2dShape(int& Degree, int& NbPoles, int& NbKnots) const override;

  Standard_EXPORT void Curve2d(const int                     Index,
                               NCollection_Array1<gp_Pnt2d>& TPoles,
                               NCollection_Array1<double>&   TKnots,
                               NCollection_Array1<int>&      TMults) const override;

  int Curves2dDegree() const override;

  const NCollection_Array1<gp_Pnt2d>& Curve2dPoles(const int Index) const override;

  const NCollection_Array1<double>& Curves2dKnots() const override;

  const NCollection_Array1<int>& Curves2dMults() const override;

  Standard_EXPORT void TolReached(double& Tol3d, double& Tol2d) const override;

  //! returns the maximum error in the <Index> 2d curve approximation.
  Standard_EXPORT double Max2dError(const int Index) const;

  Standard_EXPORT double TolCurveOnSurf(const int Index) const override;

  //! display information on approximation.
  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  Approx_SweepApproximation approx;
};

#include <StdFail_NotDone.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

inline bool BRepBlend_AppSurface::IsDone() const
{
  return approx.IsDone();
}

inline int BRepBlend_AppSurface::UDegree() const
{
  return approx.UDegree();
}

inline int BRepBlend_AppSurface::VDegree() const
{
  return approx.VDegree();
}

inline const NCollection_Array2<gp_Pnt>& BRepBlend_AppSurface::SurfPoles() const
{
  return approx.SurfPoles();
}

inline const NCollection_Array2<double>& BRepBlend_AppSurface::SurfWeights() const
{
  return approx.SurfWeights();
}

inline const NCollection_Array1<double>& BRepBlend_AppSurface::SurfUKnots() const
{
  return approx.SurfUKnots();
}

inline const NCollection_Array1<double>& BRepBlend_AppSurface::SurfVKnots() const
{
  return approx.SurfVKnots();
}

inline const NCollection_Array1<int>& BRepBlend_AppSurface::SurfUMults() const
{
  return approx.SurfUMults();
}

inline const NCollection_Array1<int>& BRepBlend_AppSurface::SurfVMults() const
{
  return approx.SurfVMults();
}

inline int BRepBlend_AppSurface::NbCurves2d() const
{
  return approx.NbCurves2d();
}

inline int BRepBlend_AppSurface::Curves2dDegree() const
{
  return approx.Curves2dDegree();
}

inline const NCollection_Array1<gp_Pnt2d>& BRepBlend_AppSurface::Curve2dPoles(const int Index) const
{
  return approx.Curve2dPoles(Index);
}

inline const NCollection_Array1<double>& BRepBlend_AppSurface::Curves2dKnots() const
{
  return approx.Curves2dKnots();
}

inline const NCollection_Array1<int>& BRepBlend_AppSurface::Curves2dMults() const
{
  return approx.Curves2dMults();
}
