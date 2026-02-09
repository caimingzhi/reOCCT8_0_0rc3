#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AppDef_MultiLine.hpp>
#include <Standard_Integer.hpp>
#include <AppParCurves_ConstraintCouple.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <GeomAbs_Shape.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>
#include <Standard_OStream.hpp>
#include <math_Vector.hpp>
#include <AppParCurves_Constraint.hpp>
#include <PLib_HermitJacobi.hpp>
class AppDef_SmoothCriterion;
class math_Matrix;
class FEmTool_Curve;
class FEmTool_Assembly;

class AppDef_Variational
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AppDef_Variational(
    const AppDef_MultiLine&                                                SSP,
    const int                                                              FirstPoint,
    const int                                                              LastPoint,
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints,
    const int                                                              MaxDegree   = 14,
    const int                                                              MaxSegment  = 100,
    const GeomAbs_Shape                                                    Continuity  = GeomAbs_C2,
    const bool                                                             WithMinMax  = false,
    const bool                                                             WithCutting = true,
    const double                                                           Tolerance   = 1.0,
    const int                                                              NbIterations = 2);

  Standard_EXPORT void Approximate();

  Standard_EXPORT bool IsCreated() const;

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool IsOverConstrained() const;

  Standard_EXPORT AppParCurves_MultiBSpCurve Value() const;

  Standard_EXPORT double MaxError() const;

  Standard_EXPORT int MaxErrorIndex() const;

  Standard_EXPORT double QuadraticError() const;

  Standard_EXPORT void Distance(math_Matrix& mat);

  Standard_EXPORT double AverageError() const;

  Standard_EXPORT const occ::handle<NCollection_HArray1<double>>& Parameters() const;

  Standard_EXPORT const occ::handle<NCollection_HArray1<double>>& Knots() const;

  Standard_EXPORT void Criterium(double& VFirstOrder,
                                 double& VSecondOrder,
                                 double& VThirdOrder) const;

  Standard_EXPORT void CriteriumWeight(double& Percent1, double& Percent2, double& Percent3) const;

  Standard_EXPORT int MaxDegree() const;

  Standard_EXPORT int MaxSegment() const;

  Standard_EXPORT GeomAbs_Shape Continuity() const;

  Standard_EXPORT bool WithMinMax() const;

  Standard_EXPORT bool WithCutting() const;

  Standard_EXPORT double Tolerance() const;

  Standard_EXPORT int NbIterations() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

  Standard_EXPORT bool SetConstraints(
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& aConstrainst);

  Standard_EXPORT void SetParameters(const occ::handle<NCollection_HArray1<double>>& param);

  Standard_EXPORT bool SetKnots(const occ::handle<NCollection_HArray1<double>>& knots);

  Standard_EXPORT bool SetMaxDegree(const int Degree);

  Standard_EXPORT bool SetMaxSegment(const int NbSegment);

  Standard_EXPORT bool SetContinuity(const GeomAbs_Shape C);

  Standard_EXPORT void SetWithMinMax(const bool MinMax);

  Standard_EXPORT bool SetWithCutting(const bool Cutting);

  Standard_EXPORT void SetCriteriumWeight(const double Percent1,
                                          const double Percent2,
                                          const double Percent3);

  Standard_EXPORT void SetCriteriumWeight(const int Order, const double Percent);

  Standard_EXPORT void SetTolerance(const double Tol);

  Standard_EXPORT void SetNbIterations(const int Iter);

private:
  Standard_EXPORT void TheMotor(occ::handle<AppDef_SmoothCriterion>& J,
                                const double                         WQuadratic,
                                const double                         WQuality,
                                occ::handle<FEmTool_Curve>&          TheCurve,
                                NCollection_Array1<double>&          Ecarts);

  Standard_EXPORT void Adjusting(occ::handle<AppDef_SmoothCriterion>& J,
                                 double&                              WQuadratic,
                                 double&                              WQuality,
                                 occ::handle<FEmTool_Curve>&          TheCurve,
                                 NCollection_Array1<double>&          Ecarts);

  Standard_EXPORT void Optimization(occ::handle<AppDef_SmoothCriterion>& J,
                                    FEmTool_Assembly&                    A,
                                    const bool                           ToAssemble,
                                    const double                         EpsDeg,
                                    occ::handle<FEmTool_Curve>&          Curve,
                                    const NCollection_Array1<double>&    Parameters) const;

  Standard_EXPORT void Project(const occ::handle<FEmTool_Curve>& C,
                               const NCollection_Array1<double>& Ti,
                               NCollection_Array1<double>&       ProjTi,
                               NCollection_Array1<double>&       Distance,
                               int&                              NumPoints,
                               double&                           MaxErr,
                               double&                           QuaErr,
                               double&                           AveErr,
                               const int                         NbIterations = 2) const;

  Standard_EXPORT void ACR(occ::handle<FEmTool_Curve>& Curve,
                           NCollection_Array1<double>& Ti,
                           const int                   Decima) const;

  Standard_EXPORT void SplitCurve(const occ::handle<FEmTool_Curve>& InCurve,
                                  const NCollection_Array1<double>& Ti,
                                  const double                      CurveTol,
                                  occ::handle<FEmTool_Curve>&       OutCurve,
                                  bool&                             iscut) const;

  Standard_EXPORT void Init();

  Standard_EXPORT void InitSmoothCriterion();

  Standard_EXPORT void InitParameters(double& Length);

  Standard_EXPORT void InitCriterionEstimations(const double Length,
                                                double&      J1,
                                                double&      J2,
                                                double&      J3) const;

  Standard_EXPORT void EstTangent(const int ipnt, math_Vector& VTang) const;

  Standard_EXPORT void EstSecnd(const int          ipnt,
                                const math_Vector& VTang1,
                                const math_Vector& VTang2,
                                const double       Length,
                                math_Vector&       VScnd) const;

  Standard_EXPORT void InitCutting(const PLib_HermitJacobi&    aBase,
                                   const double                CurvTol,
                                   occ::handle<FEmTool_Curve>& aCurve) const;

  Standard_EXPORT void AssemblingConstraints(const occ::handle<FEmTool_Curve>& Curve,
                                             const NCollection_Array1<double>& Parameters,
                                             const double                      CBLONG,
                                             FEmTool_Assembly&                 A) const;

  Standard_EXPORT bool InitTthetaF(const int                     ndimen,
                                   const AppParCurves_Constraint typcon,
                                   const int                     begin,
                                   const int                     jndex);

  AppDef_MultiLine                                                mySSP;
  int                                                             myNbP3d;
  int                                                             myNbP2d;
  int                                                             myDimension;
  int                                                             myFirstPoint;
  int                                                             myLastPoint;
  int                                                             myNbPoints;
  occ::handle<NCollection_HArray1<double>>                        myTabPoints;
  occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>> myConstraints;
  int                                                             myNbConstraints;
  occ::handle<NCollection_HArray1<double>>                        myTabConstraints;
  int                                                             myNbPassPoints;
  int                                                             myNbTangPoints;
  int                                                             myNbCurvPoints;
  occ::handle<NCollection_HArray1<int>>                           myTypConstraints;
  occ::handle<NCollection_HArray1<double>>                        myTtheta;
  occ::handle<NCollection_HArray1<double>>                        myTfthet;
  int                                                             myMaxDegree;
  int                                                             myMaxSegment;
  int                                                             myNbIterations;
  double                                                          myTolerance;
  GeomAbs_Shape                                                   myContinuity;
  int                                                             myNivCont;
  bool                                                            myWithMinMax;
  bool                                                            myWithCutting;
  double                                                          myPercent[3];
  double                                                          myCriterium[4];
  occ::handle<AppDef_SmoothCriterion>                             mySmoothCriterion;
  occ::handle<NCollection_HArray1<double>>                        myParameters;
  occ::handle<NCollection_HArray1<double>>                        myKnots;
  AppParCurves_MultiBSpCurve                                      myMBSpCurve;
  double                                                          myMaxError;
  int                                                             myMaxErrorIndex;
  double                                                          myAverageError;
  bool                                                            myIsCreated;
  bool                                                            myIsDone;
  bool                                                            myIsOverConstr;
};
