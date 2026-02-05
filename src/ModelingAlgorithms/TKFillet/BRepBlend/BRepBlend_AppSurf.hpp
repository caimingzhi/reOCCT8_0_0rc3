#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Sequence.hpp>
#include <Approx_ParametrizationType.hpp>
#include <GeomAbs_Shape.hpp>
#include <AppBlend_Approx.hpp>
class StdFail_NotDone;
class Standard_DomainError;
class Standard_OutOfRange;
class Blend_AppFunction;
class BRepBlend_Line;

class BRepBlend_AppSurf : public AppBlend_Approx
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBlend_AppSurf();

  Standard_EXPORT BRepBlend_AppSurf(const int    Degmin,
                                    const int    Degmax,
                                    const double Tol3d,
                                    const double Tol2d,
                                    const int    NbIt,
                                    const bool   KnownParameters = false);

  Standard_EXPORT void Init(const int    Degmin,
                            const int    Degmax,
                            const double Tol3d,
                            const double Tol2d,
                            const int    NbIt,
                            const bool   KnownParameters = false);

  //! Define the type of parametrization used in the approximation
  Standard_EXPORT void SetParType(const Approx_ParametrizationType ParType);

  //! Define the Continuity used in the approximation
  Standard_EXPORT void SetContinuity(const GeomAbs_Shape C);

  //! define the Weights associed to the criterium used in
  //! the optimization.
  //!
  //! if Wi <= 0
  Standard_EXPORT void SetCriteriumWeight(const double W1, const double W2, const double W3);

  //! returns the type of parametrization used in the approximation
  Standard_EXPORT Approx_ParametrizationType ParType() const;

  //! returns the Continuity used in the approximation
  Standard_EXPORT GeomAbs_Shape Continuity() const;

  //! returns the Weights (as percent) associed to the criterium used in
  //! the optimization.
  Standard_EXPORT void CriteriumWeight(double& W1, double& W2, double& W3) const;

  Standard_EXPORT void Perform(const occ::handle<BRepBlend_Line>& Lin,
                               Blend_AppFunction&                 SecGen,
                               const bool                         SpApprox = false);

  Standard_EXPORT void PerformSmoothing(const occ::handle<BRepBlend_Line>& Lin,
                                        Blend_AppFunction&                 SecGen);

  Standard_EXPORT void Perform(const occ::handle<BRepBlend_Line>& Lin,
                               Blend_AppFunction&                 SecGen,
                               const int                          NbMaxP);

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

  void TolReached(double& Tol3d, double& Tol2d) const override;

  Standard_EXPORT double TolCurveOnSurf(const int Index) const override;

private:
  Standard_EXPORT void InternalPerform(const occ::handle<BRepBlend_Line>& Lin,
                                       Blend_AppFunction&                 SecGen,
                                       const bool                         SpApprox,
                                       const bool                         UseVariational);

  bool                                                             done;
  int                                                              dmin;
  int                                                              dmax;
  double                                                           tol3d;
  double                                                           tol2d;
  int                                                              nbit;
  int                                                              udeg;
  int                                                              vdeg;
  bool                                                             knownp;
  occ::handle<NCollection_HArray2<gp_Pnt>>                         tabPoles;
  occ::handle<NCollection_HArray2<double>>                         tabWeights;
  occ::handle<NCollection_HArray1<double>>                         tabUKnots;
  occ::handle<NCollection_HArray1<double>>                         tabVKnots;
  occ::handle<NCollection_HArray1<int>>                            tabUMults;
  occ::handle<NCollection_HArray1<int>>                            tabVMults;
  NCollection_Sequence<occ::handle<NCollection_HArray1<gp_Pnt2d>>> seqPoles2d;
  double                                                           tol3dreached;
  double                                                           tol2dreached;
  Approx_ParametrizationType                                       paramtype;
  GeomAbs_Shape                                                    continuity;
  double                                                           critweights[3];
};

#define TheSectionGenerator Blend_AppFunction
#define TheSectionGenerator_hxx <Blend_AppFunction.hpp>
#define Handle_TheLine occ::handle<BRepBlend_Line>
#define TheLine BRepBlend_Line
#define TheLine_hxx <BRepBlend_Line.hpp>
#define AppBlend_AppSurf BRepBlend_AppSurf
#define AppBlend_AppSurf_hxx <BRepBlend_AppSurf.hpp>

#include <AppBlend_AppSurf_1.hpp>

#undef TheSectionGenerator
#undef TheSectionGenerator_hxx
#undef Handle_TheLine
#undef TheLine
#undef TheLine_hxx
#undef AppBlend_AppSurf
#undef AppBlend_AppSurf_hxx
