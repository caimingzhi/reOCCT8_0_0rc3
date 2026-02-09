#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Extrema_POnCurv2d.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt2d.hpp>

#include <Extrema_ECC2d.hpp>

class Adaptor2d_Curve2d;
class Extrema_POnCurv2d;
class Extrema_ExtElC2d;

class Extrema_ExtCC2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_ExtCC2d();

  Standard_EXPORT Extrema_ExtCC2d(const Adaptor2d_Curve2d& C1,
                                  const Adaptor2d_Curve2d& C2,
                                  const double             TolC1 = 1.0e-10,
                                  const double             TolC2 = 1.0e-10);

  Standard_EXPORT Extrema_ExtCC2d(const Adaptor2d_Curve2d& C1,
                                  const Adaptor2d_Curve2d& C2,
                                  const double             U1,
                                  const double             U2,
                                  const double             V1,
                                  const double             V2,
                                  const double             TolC1 = 1.0e-10,
                                  const double             TolC2 = 1.0e-10);

  Standard_EXPORT void Initialize(const Adaptor2d_Curve2d& C2,
                                  const double             V1,
                                  const double             V2,
                                  const double             TolC1 = 1.0e-10,
                                  const double             TolC2 = 1.0e-10);

  Standard_EXPORT void Perform(const Adaptor2d_Curve2d& C1, const double U1, const double U2);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT bool IsParallel() const;

  Standard_EXPORT double SquareDistance(const int N = 1) const;

  Standard_EXPORT void Points(const int N, Extrema_POnCurv2d& P1, Extrema_POnCurv2d& P2) const;

  Standard_EXPORT void TrimmedSquareDistances(double&   dist11,
                                              double&   distP12,
                                              double&   distP21,
                                              double&   distP22,
                                              gp_Pnt2d& P11,
                                              gp_Pnt2d& P12,
                                              gp_Pnt2d& P21,
                                              gp_Pnt2d& P22) const;

  Standard_EXPORT void SetSingleSolutionFlag(const bool theSingleSolutionFlag);

  Standard_EXPORT bool GetSingleSolutionFlag() const;

protected:
  Standard_EXPORT void Results(const Extrema_ExtElC2d& AlgExt,
                               const double            Ut11,
                               const double            Ut12,
                               const double            Ut21,
                               const double            Ut22,
                               const double            Period1 = 0.0,
                               const double            Period2 = 0.0);

  Standard_EXPORT void Results(const Extrema_ECC2d& AlgExt,
                               const double         Ut11,
                               const double         Ut12,
                               const double         Ut21,
                               const double         Ut22,
                               const double         Period1 = 0.0,
                               const double         Period2 = 0.0);

private:
  bool                                    myIsFindSingleSolution;
  bool                                    myDone;
  bool                                    myIsPar;
  NCollection_Sequence<Extrema_POnCurv2d> mypoints;
  NCollection_Sequence<double>            mySqDist;
  int                                     mynbext;
  bool                                    inverse;
  const Adaptor2d_Curve2d*                myC;
  double                                  myv1;
  double                                  myv2;
  double                                  mytolc1;
  double                                  mytolc2;
  gp_Pnt2d                                P1f;
  gp_Pnt2d                                P1l;
  gp_Pnt2d                                P2f;
  gp_Pnt2d                                P2l;
  double                                  mydist11;
  double                                  mydist12;
  double                                  mydist21;
  double                                  mydist22;
};
