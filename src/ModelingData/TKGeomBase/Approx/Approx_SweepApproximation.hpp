#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AdvApprox_EvaluatorFunction.hpp>
#include <NCollection_Array1.hpp>
#include <gp_GTrsf2d.hpp>
#include <NCollection_HArray1.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <NCollection_Sequence.hpp>
class Approx_SweepFunction;
class AdvApprox_Cutting;

//! Approximation of an Surface S(u,v)
//! (and eventually associate 2d Curves) defined
//! by section's law.
//!
//! This surface is defined by a function F(u, v)
//! where Ft(u) = F(u, t) is a bspline curve.
//! To use this algorithm, you have to implement Ft(u)
//! as a derivative class of Approx_SweepFunction.
//! This algorithm can be used by blending, sweeping...
class Approx_SweepApproximation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Approx_SweepApproximation(const occ::handle<Approx_SweepFunction>& Func);

  //! Perform the Approximation
  //! [First, Last] : Approx_SweepApproximation.cdl
  //! Tol3d : Tolerance to surface approximation
  //! Tol2d : Tolerance used to perform curve approximation
  //! Normally the 2d curve are approximated with a
  //! tolerance given by the resolution on support surfaces,
  //! but if this tolerance is too large Tol2d is used.
  //! TolAngular : Tolerance (in radian) to control the angle
  //! between tangents on the section law and
  //! tangent of iso-v on approximated surface
  //! Continuity : The continuity in v waiting on the surface
  //! Degmax     : The maximum degree in v required on the surface
  //! Segmax     : The maximum number of span in v required on
  //! the surface
  //! Warning : The continuity ci can be obtained only if Ft is Ci
  Standard_EXPORT void Perform(const double        First,
                               const double        Last,
                               const double        Tol3d,
                               const double        BoundTol,
                               const double        Tol2d,
                               const double        TolAngular,
                               const GeomAbs_Shape Continuity = GeomAbs_C0,
                               const int           Degmax     = 11,
                               const int           Segmax     = 50);

  //! The EvaluatorFunction from AdvApprox;
  Standard_EXPORT int Eval(const double Parameter,
                           const int    DerivativeRequest,
                           const double First,
                           const double Last,
                           double&      Result);

  //! returns if we have an result
  bool IsDone() const;

  Standard_EXPORT void SurfShape(int& UDegree,
                                 int& VDegree,
                                 int& NbUPoles,
                                 int& NbVPoles,
                                 int& NbUKnots,
                                 int& NbVKnots) const;

  Standard_EXPORT void Surface(NCollection_Array2<gp_Pnt>& TPoles,
                               NCollection_Array2<double>& TWeights,
                               NCollection_Array1<double>& TUKnots,
                               NCollection_Array1<double>& TVKnots,
                               NCollection_Array1<int>&    TUMults,
                               NCollection_Array1<int>&    TVMults) const;

  int UDegree() const;

  int VDegree() const;

  const NCollection_Array2<gp_Pnt>& SurfPoles() const;

  const NCollection_Array2<double>& SurfWeights() const;

  const NCollection_Array1<double>& SurfUKnots() const;

  const NCollection_Array1<double>& SurfVKnots() const;

  const NCollection_Array1<int>& SurfUMults() const;

  const NCollection_Array1<int>& SurfVMults() const;

  //! returns the maximum error in the surface approximation.
  Standard_EXPORT double MaxErrorOnSurf() const;

  //! returns the average error in the surface approximation.
  Standard_EXPORT double AverageErrorOnSurf() const;

  int NbCurves2d() const;

  Standard_EXPORT void Curves2dShape(int& Degree, int& NbPoles, int& NbKnots) const;

  Standard_EXPORT void Curve2d(const int                     Index,
                               NCollection_Array1<gp_Pnt2d>& TPoles,
                               NCollection_Array1<double>&   TKnots,
                               NCollection_Array1<int>&      TMults) const;

  int Curves2dDegree() const;

  const NCollection_Array1<gp_Pnt2d>& Curve2dPoles(const int Index) const;

  const NCollection_Array1<double>& Curves2dKnots() const;

  const NCollection_Array1<int>& Curves2dMults() const;

  //! returns the maximum error of the <Index>
  //! 2d curve approximation.
  Standard_EXPORT double Max2dError(const int Index) const;

  //! returns the average error of the <Index>
  //! 2d curve approximation.
  Standard_EXPORT double Average2dError(const int Index) const;

  //! returns the maximum 3d error of the <Index>
  //! 2d curve approximation on the Surface.
  Standard_EXPORT double TolCurveOnSurf(const int Index) const;

  //! display information on approximation.
  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  Standard_EXPORT void Approximation(const occ::handle<NCollection_HArray1<double>>& OneDTol,
                                     const occ::handle<NCollection_HArray1<double>>& TwoDTol,
                                     const occ::handle<NCollection_HArray1<double>>& ThreeDTol,
                                     const double                                    BounTol,
                                     const double                                    First,
                                     const double                                    Last,
                                     const GeomAbs_Shape                             Continuity,
                                     const int                                       Degmax,
                                     const int                                       Segmax,
                                     const AdvApprox_EvaluatorFunction& TheApproxFunction,
                                     const AdvApprox_Cutting&           TheCuttingTool);

  Standard_EXPORT bool D0(const double Param,
                          const double First,
                          const double Last,
                          double&      Result);

  Standard_EXPORT bool D1(const double Param,
                          const double First,
                          const double Last,
                          double&      Result);

  Standard_EXPORT bool D2(const double Param,
                          const double First,
                          const double Last,
                          double&      Result);

  occ::handle<Approx_SweepFunction>                                myFunc;
  bool                                                             done;
  int                                                              Num1DSS;
  int                                                              Num2DSS;
  int                                                              Num3DSS;
  int                                                              udeg;
  int                                                              vdeg;
  int                                                              deg2d;
  occ::handle<NCollection_HArray2<gp_Pnt>>                         tabPoles;
  occ::handle<NCollection_HArray2<double>>                         tabWeights;
  occ::handle<NCollection_HArray1<double>>                         tabUKnots;
  occ::handle<NCollection_HArray1<double>>                         tabVKnots;
  occ::handle<NCollection_HArray1<double>>                         tab2dKnots;
  occ::handle<NCollection_HArray1<int>>                            tabUMults;
  occ::handle<NCollection_HArray1<int>>                            tabVMults;
  occ::handle<NCollection_HArray1<int>>                            tab2dMults;
  NCollection_Sequence<occ::handle<NCollection_HArray1<gp_Pnt2d>>> seqPoles2d;
  occ::handle<NCollection_HArray1<double>>                         MError1d;
  occ::handle<NCollection_HArray1<double>>                         tab2dError;
  occ::handle<NCollection_HArray1<double>>                         MError3d;
  occ::handle<NCollection_HArray1<double>>                         AError1d;
  occ::handle<NCollection_HArray1<double>>                         Ave2dError;
  occ::handle<NCollection_HArray1<double>>                         AError3d;
  occ::handle<NCollection_HArray1<gp_GTrsf2d>>                     AAffin;
  occ::handle<NCollection_HArray1<double>>                         COnSurfErr;
  gp_Vec                                                           Translation;
  occ::handle<NCollection_HArray1<gp_Pnt>>                         myPoles;
  occ::handle<NCollection_HArray1<gp_Pnt2d>>                       myPoles2d;
  occ::handle<NCollection_HArray1<double>>                         myWeigths;
  occ::handle<NCollection_HArray1<gp_Vec>>                         myDPoles;
  occ::handle<NCollection_HArray1<gp_Vec>>                         myD2Poles;
  occ::handle<NCollection_HArray1<gp_Vec2d>>                       myDPoles2d;
  occ::handle<NCollection_HArray1<gp_Vec2d>>                       myD2Poles2d;
  occ::handle<NCollection_HArray1<double>>                         myDWeigths;
  occ::handle<NCollection_HArray1<double>>                         myD2Weigths;
  int                                                              myOrder;
  double                                                           myParam;
  double                                                           first;
  double                                                           last;
};

#include <StdFail_NotDone.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Pnt.hpp>

inline bool Approx_SweepApproximation::IsDone() const
{
  return done;
}

inline int Approx_SweepApproximation::UDegree() const
{
  if (!done)
  {
    throw StdFail_NotDone(" Approx_SweepApproximation");
  }
  return udeg;
}

inline int Approx_SweepApproximation::VDegree() const
{
  if (!done)
  {
    throw StdFail_NotDone(" Approx_SweepApproximation");
  }
  return vdeg;
}

inline const NCollection_Array2<gp_Pnt>& Approx_SweepApproximation::SurfPoles() const
{
  if (!done)
  {
    throw StdFail_NotDone(" Approx_SweepApproximation");
  }
  return tabPoles->Array2();
}

inline const NCollection_Array2<double>& Approx_SweepApproximation::SurfWeights() const
{
  if (!done)
  {
    throw StdFail_NotDone(" Approx_SweepApproximation");
  }
  return tabWeights->Array2();
}

inline const NCollection_Array1<double>& Approx_SweepApproximation::SurfUKnots() const
{
  if (!done)
  {
    throw StdFail_NotDone(" Approx_SweepApproximation");
  }
  return tabUKnots->Array1();
}

inline const NCollection_Array1<double>& Approx_SweepApproximation::SurfVKnots() const
{
  if (!done)
  {
    throw StdFail_NotDone(" Approx_SweepApproximation");
  }
  return tabVKnots->Array1();
}

inline const NCollection_Array1<int>& Approx_SweepApproximation::SurfUMults() const
{
  if (!done)
  {
    throw StdFail_NotDone(" Approx_SweepApproximation");
  }
  return tabUMults->Array1();
}

inline const NCollection_Array1<int>& Approx_SweepApproximation::SurfVMults() const
{
  if (!done)
  {
    throw StdFail_NotDone(" Approx_SweepApproximation");
  }
  return tabVMults->Array1();
}

inline int Approx_SweepApproximation::NbCurves2d() const
{
  if (!done)
  {
    throw StdFail_NotDone(" Approx_SweepApproximation");
  }
  return Num2DSS;
}

inline int Approx_SweepApproximation::Curves2dDegree() const
{
  if (!done)
  {
    throw StdFail_NotDone(" Approx_SweepApproximation");
  }
  if (seqPoles2d.Length() == 0)
  {
    throw Standard_DomainError();
  }
  return deg2d;
}

inline const NCollection_Array1<gp_Pnt2d>& Approx_SweepApproximation::Curve2dPoles(
  const int Index) const
{
  if (!done)
  {
    throw StdFail_NotDone(" Approx_SweepApproximation");
  }
  if (seqPoles2d.Length() == 0)
  {
    throw Standard_DomainError();
  }
  return seqPoles2d(Index)->Array1();
}

inline const NCollection_Array1<double>& Approx_SweepApproximation::Curves2dKnots() const
{
  if (!done)
  {
    throw StdFail_NotDone(" Approx_SweepApproximation");
  }
  if (seqPoles2d.Length() == 0)
  {
    throw Standard_DomainError();
  }
  return tab2dKnots->Array1();
}

inline const NCollection_Array1<int>& Approx_SweepApproximation::Curves2dMults() const
{
  if (!done)
  {
    throw StdFail_NotDone(" Approx_SweepApproximation");
  }
  if (seqPoles2d.Length() == 0)
  {
    throw Standard_DomainError();
  }
  return tab2dMults->Array1();
}

/*
inline  void Approx_SweepApproximation::TolReached(double& Tol3d,double& Tol2d) const
{

}*/
