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

//! An algorithm for constructing a BSpline surface filled
//! from a series of boundaries which serve as path
//! constraints and optionally, as tangency constraints.
//! The algorithm accepts three or four curves as the
//! boundaries of the target surface.
//! The only FillingStyle used is Coons.
//! A ConstrainedFilling object provides a framework for:
//! -   defining the boundaries of the surface
//! -   implementing the construction algorithm
//! -   consulting the result.
//! Warning
//! This surface filling algorithm is specifically designed to
//! be used in connection with fillets. Satisfactory results
//! cannot be guaranteed for other uses.
class GeomFill_ConstrainedFilling
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs an empty framework for filling a surface from boundaries.
  //! The boundaries of the surface will be defined, and the
  //! surface will be built by using the function Init.
  //! The surface will respect the following constraints:
  //! -   its degree will not be greater than MaxDeg
  //! -   the maximum number of segments MaxSeg which
  //! BSpline surfaces can have.
  Standard_EXPORT GeomFill_ConstrainedFilling(const int MaxDeg, const int MaxSeg);

  Standard_EXPORT void Init(const occ::handle<GeomFill_Boundary>& B1,
                            const occ::handle<GeomFill_Boundary>& B2,
                            const occ::handle<GeomFill_Boundary>& B3,
                            const bool                            NoCheck = false);

  //! Constructs a BSpline surface filled from the series of
  //! boundaries B1, B2, B3 and, if need be, B4, which serve:
  //! -   as path constraints
  //! -   and optionally, as tangency constraints if they are
  //! GeomFill_BoundWithSurf curves.
  //! The boundaries may be given in any order: they are
  //! classified and if necessary, reversed and reparameterized.
  //! The surface will also respect the following constraints:
  //! -   its degree will not be greater than the maximum
  //! degree defined at the time of construction of this framework, and
  //! -   the maximum number of segments MaxSeg which BSpline surfaces can have
  Standard_EXPORT void Init(const occ::handle<GeomFill_Boundary>& B1,
                            const occ::handle<GeomFill_Boundary>& B2,
                            const occ::handle<GeomFill_Boundary>& B3,
                            const occ::handle<GeomFill_Boundary>& B4,
                            const bool                            NoCheck = false);

  //! Allows to modify domain on which the blending function
  //! associated to the constrained boundary B will propag
  //! the influence of the field of tangency. Can be
  //! useful to reduce influence of boundaries on which
  //! the Coons compatibility conditions are not respected.
  //! l is a relative value of the parametric range of B.
  //! Default value for l is 1 (used in Init).
  //! Warning: Must be called after Init with a constrained boundary
  //! used in the call to Init.
  Standard_EXPORT void SetDomain(const double l, const occ::handle<GeomFill_BoundWithSurf>& B);

  //! Computes the new poles of the surface using the new
  //! blending functions set by several calls to SetDomain.
  Standard_EXPORT void ReBuild();

  //! Returns the bound of index i after sort.
  Standard_EXPORT occ::handle<GeomFill_Boundary> Boundary(const int I) const;

  //! Returns the BSpline surface after computation of the fill by this framework.
  Standard_EXPORT occ::handle<Geom_BSplineSurface> Surface() const;

  //! Internal use for Advmath approximation call.
  Standard_EXPORT int Eval(const double W, const int Ord, double& Result) const;

  //! Computes the fields of tangents on 30 points along the
  //! bound I, these are not the constraint tangents but
  //! gives an idea of the coonsAlgPatch regularity.
  Standard_EXPORT void CheckCoonsAlgPatch(const int I);

  //! Computes the fields of tangents and normals on 30
  //! points along the bound I, draw them, and computes the
  //! max dot product that must be near than 0.
  Standard_EXPORT void CheckTgteField(const int I);

  //! Computes values and normals along the bound I and
  //! compare them to the approx result curves (bound and
  //! tgte field) , draw the normals and tangents.
  Standard_EXPORT void CheckApprox(const int I);

  //! Computes values and normals along the bound I on both
  //! constraint surface and result surface, draw the
  //! normals, and computes the max distance between values
  //! and the max angle between normals.
  Standard_EXPORT void CheckResult(const int I);

private:
  //! Performs the approximation an compute the poles of the
  //! surface.
  Standard_EXPORT void Build();

  //! Performs the parallel approximation on two oppsite
  //! bounds
  Standard_EXPORT void PerformApprox();

  //! matches the nodal vectors of the blending functions
  //! and the results of the approx to allow the surface
  //! computation.
  Standard_EXPORT void MatchKnots();

  //! performs the poles of the partial construction S0.
  Standard_EXPORT void PerformS0();

  //! performs the poles of the partial construction S1.
  Standard_EXPORT void PerformS1();

  //! performs the poles of the surface using the partial
  //! constructions S0 and S1.
  Standard_EXPORT void PerformSurface();

  //! Checks if the field of tangency doesn t twist along the
  //! boundary.
  Standard_EXPORT bool CheckTgte(const int I);

  //! Evaluates the min magnitude of the field of tangency
  //! along bound I to allow a simple evaluation of the
  //! tolerance needed for the approximation of the field of
  //! tangency.
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
