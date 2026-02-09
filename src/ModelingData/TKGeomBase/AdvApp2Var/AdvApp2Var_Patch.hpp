#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <AdvApp2Var_EvaluatorFunc2Var.hpp>
#include <gp_Pnt.hpp>
class AdvApp2Var_Context;
class AdvApp2Var_Framework;
class AdvApp2Var_Criterion;

class AdvApp2Var_Patch : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(AdvApp2Var_Patch, Standard_Transient)
public:
  Standard_EXPORT AdvApp2Var_Patch();

  Standard_EXPORT AdvApp2Var_Patch(const double U0,
                                   const double U1,
                                   const double V0,
                                   const double V1,
                                   const int    iu,
                                   const int    iv);

  Standard_EXPORT bool IsDiscretised() const;

  Standard_EXPORT void Discretise(const AdvApp2Var_Context&           Conditions,
                                  const AdvApp2Var_Framework&         Constraints,
                                  const AdvApp2Var_EvaluatorFunc2Var& func);

  Standard_EXPORT bool IsApproximated() const;

  Standard_EXPORT bool HasResult() const;

  Standard_EXPORT void MakeApprox(const AdvApp2Var_Context&   Conditions,
                                  const AdvApp2Var_Framework& Constraints,
                                  const int                   NumDec);

  Standard_EXPORT void AddConstraints(const AdvApp2Var_Context&   Conditions,
                                      const AdvApp2Var_Framework& Constraints);

  Standard_EXPORT void AddErrors(const AdvApp2Var_Framework& Constraints);

  Standard_EXPORT void ChangeDomain(const double a, const double b, const double c, const double d);

  Standard_EXPORT void ResetApprox();

  Standard_EXPORT void OverwriteApprox();

  Standard_EXPORT double U0() const;

  Standard_EXPORT double U1() const;

  Standard_EXPORT double V0() const;

  Standard_EXPORT double V1() const;

  Standard_EXPORT int UOrder() const;

  Standard_EXPORT int VOrder() const;

  Standard_EXPORT int CutSense() const;

  Standard_EXPORT int CutSense(const AdvApp2Var_Criterion& Crit, const int NumDec) const;

  Standard_EXPORT int NbCoeffInU() const;

  Standard_EXPORT int NbCoeffInV() const;

  Standard_EXPORT void ChangeNbCoeff(const int NbCoeffU, const int NbCoeffV);

  Standard_EXPORT occ::handle<NCollection_HArray2<gp_Pnt>> Poles(
    const int                 SSPIndex,
    const AdvApp2Var_Context& Conditions) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> Coefficients(
    const int                 SSPIndex,
    const AdvApp2Var_Context& Conditions) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> MaxErrors() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> AverageErrors() const;

  Standard_EXPORT occ::handle<NCollection_HArray2<double>> IsoErrors() const;

  Standard_EXPORT double CritValue() const;

  Standard_EXPORT void SetCritValue(const double dist);

private:
  AdvApp2Var_Patch(const AdvApp2Var_Patch& P)                   = delete;
  AdvApp2Var_Patch& operator=(const AdvApp2Var_Patch& theOther) = delete;

private:
  double                                   myU0;
  double                                   myU1;
  double                                   myV0;
  double                                   myV1;
  int                                      myOrdInU;
  int                                      myOrdInV;
  int                                      myNbCoeffInU;
  int                                      myNbCoeffInV;
  bool                                     myApprIsDone;
  bool                                     myHasResult;
  occ::handle<NCollection_HArray1<double>> myEquation;
  occ::handle<NCollection_HArray1<double>> myMaxErrors;
  occ::handle<NCollection_HArray1<double>> myMoyErrors;
  occ::handle<NCollection_HArray2<double>> myIsoErrors;
  int                                      myCutSense;
  bool                                     myDiscIsDone;
  occ::handle<NCollection_HArray1<double>> mySosoTab;
  occ::handle<NCollection_HArray1<double>> myDisoTab;
  occ::handle<NCollection_HArray1<double>> mySodiTab;
  occ::handle<NCollection_HArray1<double>> myDidiTab;
  double                                   myCritValue;
};
