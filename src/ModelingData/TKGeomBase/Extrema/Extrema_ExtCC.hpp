#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Adaptor3d_Curve.hpp>
#include <Extrema_CurveTool.hpp>
#include <Extrema_ExtPC.hpp>
#include <Extrema_GGenExtCC.hpp>
#include <Extrema_POnCurv.hpp>
#include <gp_Pnt.hpp>

using Extrema_ECC = Extrema_GGenExtCC<Adaptor3d_Curve,
                                      Extrema_CurveTool,
                                      Adaptor3d_Curve,
                                      Extrema_CurveTool,
                                      Extrema_POnCurv,
                                      gp_Pnt,
                                      Extrema_ExtPC>;

#include <Extrema_POnCurv.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt.hpp>

class Adaptor3d_Curve;
class Extrema_POnCurv;
class Extrema_ExtElC;

class Extrema_ExtCC
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_ExtCC(const double TolC1 = 1.0e-10, const double TolC2 = 1.0e-10);

  Standard_EXPORT Extrema_ExtCC(const Adaptor3d_Curve& C1,
                                const Adaptor3d_Curve& C2,
                                const double           TolC1 = 1.0e-10,
                                const double           TolC2 = 1.0e-10);

  Standard_EXPORT Extrema_ExtCC(const Adaptor3d_Curve& C1,
                                const Adaptor3d_Curve& C2,
                                const double           U1,
                                const double           U2,
                                const double           V1,
                                const double           V2,
                                const double           TolC1 = 1.0e-10,
                                const double           TolC2 = 1.0e-10);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& C1,
                                  const Adaptor3d_Curve& C2,
                                  const double           TolC1 = 1.0e-10,
                                  const double           TolC2 = 1.0e-10);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& C1,
                                  const Adaptor3d_Curve& C2,
                                  const double           U1,
                                  const double           U2,
                                  const double           V1,
                                  const double           V2,
                                  const double           TolC1 = 1.0e-10,
                                  const double           TolC2 = 1.0e-10);

  Standard_EXPORT void SetCurve(const int theRank, const Adaptor3d_Curve& C);

  Standard_EXPORT void SetCurve(const int              theRank,
                                const Adaptor3d_Curve& C,
                                const double           Uinf,
                                const double           Usup);

  Standard_EXPORT void SetRange(const int theRank, const double Uinf, const double Usup);

  Standard_EXPORT void SetTolerance(const int theRank, const double Tol);

  Standard_EXPORT void Perform();

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT bool IsParallel() const;

  Standard_EXPORT double SquareDistance(const int N = 1) const;

  Standard_EXPORT void Points(const int N, Extrema_POnCurv& P1, Extrema_POnCurv& P2) const;

  Standard_EXPORT void TrimmedSquareDistances(double& dist11,
                                              double& distP12,
                                              double& distP21,
                                              double& distP22,
                                              gp_Pnt& P11,
                                              gp_Pnt& P12,
                                              gp_Pnt& P21,
                                              gp_Pnt& P22) const;

  Standard_EXPORT void SetSingleSolutionFlag(const bool theSingleSolutionFlag);

  Standard_EXPORT bool GetSingleSolutionFlag() const;

protected:
  Standard_EXPORT void PrepareResults(const Extrema_ExtElC& AlgExt,
                                      const bool            theIsInverse,
                                      const double          Ut11,
                                      const double          Ut12,
                                      const double          Ut21,
                                      const double          Ut22);

  Standard_EXPORT void PrepareResults(const Extrema_ECC& AlgExt,
                                      const double       Ut11,
                                      const double       Ut12,
                                      const double       Ut21,
                                      const double       Ut22);

  Standard_EXPORT void PrepareParallelResult(const double theUt11,
                                             const double theUt12,
                                             const double theUt21,
                                             const double theUt22,
                                             const double theSqDist);

  void ClearSolutions()
  {
    mySqDist.Clear();
    mypoints.Clear();
  }

private:
  Extrema_ExtCC(Extrema_ExtCC&)            = delete;
  Extrema_ExtCC& operator=(Extrema_ExtCC&) = delete;

private:
  bool                                  myIsFindSingleSolution;
  Extrema_ECC                           myECC;
  bool                                  myDone;
  bool                                  myIsParallel;
  NCollection_Sequence<Extrema_POnCurv> mypoints;
  NCollection_Sequence<double>          mySqDist;
  const Adaptor3d_Curve*                myC[2];
  double                                myInf[2];
  double                                mySup[2];
  double                                myTol[2];
  gp_Pnt                                myP1f;
  gp_Pnt                                myP1l;
  gp_Pnt                                myP2f;
  gp_Pnt                                myP2l;
  double                                mydist11;
  double                                mydist12;
  double                                mydist21;
  double                                mydist22;
};
