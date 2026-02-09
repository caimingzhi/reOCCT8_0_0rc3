#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <GeomFill_CornerState.hpp>
#include <gp_Vec.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
class GeomFill_CoonsAlgPatch;
class GeomFill_TgtField;
class Geom_BSplineSurface;
class GeomFill_Boundary;
class GeomFill_BoundWithSurf;

class GeomFill_ConstrainedFilling
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_ConstrainedFilling(const int MaxDeg, const int MaxSeg);

  Standard_EXPORT void Init(const occ::handle<GeomFill_Boundary>& B1,
                            const occ::handle<GeomFill_Boundary>& B2,
                            const occ::handle<GeomFill_Boundary>& B3,
                            const bool                            NoCheck = false);

  Standard_EXPORT void Init(const occ::handle<GeomFill_Boundary>& B1,
                            const occ::handle<GeomFill_Boundary>& B2,
                            const occ::handle<GeomFill_Boundary>& B3,
                            const occ::handle<GeomFill_Boundary>& B4,
                            const bool                            NoCheck = false);

  Standard_EXPORT void SetDomain(const double l, const occ::handle<GeomFill_BoundWithSurf>& B);

  Standard_EXPORT void ReBuild();

  Standard_EXPORT occ::handle<GeomFill_Boundary> Boundary(const int I) const;

  Standard_EXPORT occ::handle<Geom_BSplineSurface> Surface() const;

  Standard_EXPORT int Eval(const double W, const int Ord, double& Result) const;

  Standard_EXPORT void CheckCoonsAlgPatch(const int I);

  Standard_EXPORT void CheckTgteField(const int I);

  Standard_EXPORT void CheckApprox(const int I);

  Standard_EXPORT void CheckResult(const int I);

private:
  Standard_EXPORT void Build();

  Standard_EXPORT void PerformApprox();

  Standard_EXPORT void MatchKnots();

  Standard_EXPORT void PerformS0();

  Standard_EXPORT void PerformS1();

  Standard_EXPORT void PerformSurface();

  Standard_EXPORT bool CheckTgte(const int I);

  Standard_EXPORT void MinTgte(const int I);

  int                                      degmax;
  int                                      segmax;
  occ::handle<GeomFill_CoonsAlgPatch>      ptch;
  occ::handle<GeomFill_TgtField>           tgalg[4];
  double                                   mig[4];
  GeomFill_CornerState                     stcor[4];
  gp_Vec                                   v[4];
  bool                                     appdone;
  int                                      degree[2];
  occ::handle<NCollection_HArray1<gp_Pnt>> curvpol[4];
  occ::handle<NCollection_HArray1<gp_Pnt>> tgtepol[4];
  occ::handle<NCollection_HArray1<int>>    mults[2];
  occ::handle<NCollection_HArray1<double>> knots[2];
  occ::handle<NCollection_HArray1<double>> ab[4];
  occ::handle<NCollection_HArray1<double>> pq[4];
  double                                   dom[4];
  occ::handle<NCollection_HArray1<gp_Pnt>> ncpol[4];
  occ::handle<NCollection_HArray1<gp_Pnt>> ntpol[4];
  occ::handle<NCollection_HArray1<int>>    nm[2];
  occ::handle<NCollection_HArray1<double>> nk[2];
  int                                      ibound[2];
  int                                      ctr[2];
  int                                      nbd3;
  occ::handle<NCollection_HArray2<gp_Pnt>> S0;
  occ::handle<NCollection_HArray2<gp_Pnt>> S1;
  occ::handle<Geom_BSplineSurface>         surf;
};
