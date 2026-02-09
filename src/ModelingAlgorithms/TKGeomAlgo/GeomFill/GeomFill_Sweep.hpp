#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2d_Curve.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <GeomFill_ApproxStyle.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
class GeomFill_LocationLaw;
class GeomFill_SectionLaw;
class Geom_Surface;
class Geom2d_Curve;

class GeomFill_Sweep
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_Sweep(const occ::handle<GeomFill_LocationLaw>& Location,
                                 const bool                               WithKpart = true);

  Standard_EXPORT void SetDomain(const double First,
                                 const double Last,
                                 const double SectionFirst,
                                 const double SectionLast);

  Standard_EXPORT void SetTolerance(const double Tol3d,
                                    const double BoundTol   = 1.0,
                                    const double Tol2d      = 1.0e-5,
                                    const double TolAngular = 1.0);

  Standard_EXPORT void SetForceApproxC1(const bool ForceApproxC1);

  Standard_EXPORT bool ExchangeUV() const;

  Standard_EXPORT bool UReversed() const;

  Standard_EXPORT bool VReversed() const;

  Standard_EXPORT void Build(const occ::handle<GeomFill_SectionLaw>& Section,
                             const GeomFill_ApproxStyle              Methode    = GeomFill_Location,
                             const GeomAbs_Shape                     Continuity = GeomAbs_C2,
                             const int                               Degmax     = 10,
                             const int                               Segmax     = 30);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT double ErrorOnSurface() const;

  Standard_EXPORT void ErrorOnRestriction(const bool IsFirst, double& UError, double& VError) const;

  Standard_EXPORT void ErrorOnTrace(const int IndexOfTrace, double& UError, double& VError) const;

  Standard_EXPORT occ::handle<Geom_Surface> Surface() const;

  Standard_EXPORT occ::handle<Geom2d_Curve> Restriction(const bool IsFirst) const;

  Standard_EXPORT int NumberOfTrace() const;

  Standard_EXPORT occ::handle<Geom2d_Curve> Trace(const int IndexOfTrace) const;

private:
  Standard_EXPORT bool Build2d(const GeomAbs_Shape Continuity, const int Degmax, const int Segmax);

  Standard_EXPORT bool BuildAll(const GeomAbs_Shape Continuity, const int Degmax, const int Segmax);

  Standard_EXPORT bool BuildProduct(const GeomAbs_Shape Continuity,
                                    const int           Degmax,
                                    const int           Segmax);

  Standard_EXPORT bool BuildKPart();

  double                                                      First;
  double                                                      Last;
  double                                                      SFirst;
  double                                                      SLast;
  double                                                      Tol3d;
  double                                                      BoundTol;
  double                                                      Tol2d;
  double                                                      TolAngular;
  double                                                      SError;
  bool                                                        myForceApproxC1;
  occ::handle<GeomFill_LocationLaw>                           myLoc;
  occ::handle<GeomFill_SectionLaw>                            mySec;
  occ::handle<Geom_Surface>                                   mySurface;
  occ::handle<NCollection_HArray1<occ::handle<Geom2d_Curve>>> myCurve2d;
  occ::handle<NCollection_HArray2<double>>                    CError;
  bool                                                        done;
  bool                                                        myExchUV;
  bool                                                        isUReversed;
  bool                                                        isVReversed;
  bool                                                        myKPart;
};
