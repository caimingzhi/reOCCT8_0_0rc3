#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Real.hpp>
#include <AdvApp2Var_Context.hpp>
#include <AdvApp2Var_Network.hpp>
#include <AdvApp2Var_Framework.hpp>
#include <Standard_Boolean.hpp>
#include <Geom_Surface.hpp>
#include <AdvApp2Var_EvaluatorFunc2Var.hpp>
#include <Standard_OStream.hpp>
class AdvApprox_Cutting;
class AdvApp2Var_Criterion;
class Geom_BSplineSurface;

class AdvApp2Var_ApproxAFunc2Var
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AdvApp2Var_ApproxAFunc2Var(
    const int                                       Num1DSS,
    const int                                       Num2DSS,
    const int                                       Num3DSS,
    const occ::handle<NCollection_HArray1<double>>& OneDTol,
    const occ::handle<NCollection_HArray1<double>>& TwoDTol,
    const occ::handle<NCollection_HArray1<double>>& ThreeDTol,
    const occ::handle<NCollection_HArray2<double>>& OneDTolFr,
    const occ::handle<NCollection_HArray2<double>>& TwoDTolFr,
    const occ::handle<NCollection_HArray2<double>>& ThreeDTolFr,
    const double                                    FirstInU,
    const double                                    LastInU,
    const double                                    FirstInV,
    const double                                    LastInV,
    const GeomAbs_IsoType                           FavorIso,
    const GeomAbs_Shape                             ContInU,
    const GeomAbs_Shape                             ContInV,
    const int                                       PrecisCode,
    const int                                       MaxDegInU,
    const int                                       MaxDegInV,
    const int                                       MaxPatch,
    const AdvApp2Var_EvaluatorFunc2Var&             Func,
    AdvApprox_Cutting&                              UChoice,
    AdvApprox_Cutting&                              VChoice);

  Standard_EXPORT AdvApp2Var_ApproxAFunc2Var(
    const int                                       Num1DSS,
    const int                                       Num2DSS,
    const int                                       Num3DSS,
    const occ::handle<NCollection_HArray1<double>>& OneDTol,
    const occ::handle<NCollection_HArray1<double>>& TwoDTol,
    const occ::handle<NCollection_HArray1<double>>& ThreeDTol,
    const occ::handle<NCollection_HArray2<double>>& OneDTolFr,
    const occ::handle<NCollection_HArray2<double>>& TwoDTolFr,
    const occ::handle<NCollection_HArray2<double>>& ThreeDTolFr,
    const double                                    FirstInU,
    const double                                    LastInU,
    const double                                    FirstInV,
    const double                                    LastInV,
    const GeomAbs_IsoType                           FavorIso,
    const GeomAbs_Shape                             ContInU,
    const GeomAbs_Shape                             ContInV,
    const int                                       PrecisCode,
    const int                                       MaxDegInU,
    const int                                       MaxDegInV,
    const int                                       MaxPatch,
    const AdvApp2Var_EvaluatorFunc2Var&             Func,
    const AdvApp2Var_Criterion&                     Crit,
    AdvApprox_Cutting&                              UChoice,
    AdvApprox_Cutting&                              VChoice);

  bool IsDone() const;

  bool HasResult() const;

  occ::handle<Geom_BSplineSurface> Surface(const int Index) const;

  int UDegree() const;

  int VDegree() const;

  int NumSubSpaces(const int Dimension) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> MaxError(const int Dimension) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> AverageError(const int Dimension) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> UFrontError(const int Dimension) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> VFrontError(const int Dimension) const;

  Standard_EXPORT double MaxError(const int Dimension, const int Index) const;

  Standard_EXPORT double AverageError(const int Dimension, const int Index) const;

  Standard_EXPORT double UFrontError(const int Dimension, const int Index) const;

  Standard_EXPORT double VFrontError(const int Dimension, const int Index) const;

  Standard_EXPORT double CritError(const int Dimension, const int Index) const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  Standard_EXPORT void Init();

  Standard_EXPORT void InitGrid(const int NbInt);

  Standard_EXPORT void Perform(const AdvApprox_Cutting&            UChoice,
                               const AdvApprox_Cutting&            VChoice,
                               const AdvApp2Var_EvaluatorFunc2Var& Func);

  Standard_EXPORT void Perform(const AdvApprox_Cutting&            UChoice,
                               const AdvApprox_Cutting&            VChoice,
                               const AdvApp2Var_EvaluatorFunc2Var& Func,
                               const AdvApp2Var_Criterion&         Crit);

  Standard_EXPORT void ComputePatches(const AdvApprox_Cutting&            UChoice,
                                      const AdvApprox_Cutting&            VChoice,
                                      const AdvApp2Var_EvaluatorFunc2Var& Func);

  Standard_EXPORT void ComputePatches(const AdvApprox_Cutting&            UChoice,
                                      const AdvApprox_Cutting&            VChoice,
                                      const AdvApp2Var_EvaluatorFunc2Var& Func,
                                      const AdvApp2Var_Criterion&         Crit);

  Standard_EXPORT void ComputeConstraints(const AdvApprox_Cutting&            UChoice,
                                          const AdvApprox_Cutting&            VChoice,
                                          const AdvApp2Var_EvaluatorFunc2Var& Func);

  Standard_EXPORT void ComputeConstraints(const AdvApprox_Cutting&            UChoice,
                                          const AdvApprox_Cutting&            VChoice,
                                          const AdvApp2Var_EvaluatorFunc2Var& Func,
                                          const AdvApp2Var_Criterion&         Crit);

  Standard_EXPORT void Compute3DErrors();

  Standard_EXPORT void ComputeCritError();

  Standard_EXPORT void ConvertBS();

  int                                                         myNumSubSpaces[3];
  occ::handle<NCollection_HArray1<double>>                    my1DTolerances;
  occ::handle<NCollection_HArray1<double>>                    my2DTolerances;
  occ::handle<NCollection_HArray1<double>>                    my3DTolerances;
  occ::handle<NCollection_HArray2<double>>                    my1DTolOnFront;
  occ::handle<NCollection_HArray2<double>>                    my2DTolOnFront;
  occ::handle<NCollection_HArray2<double>>                    my3DTolOnFront;
  double                                                      myFirstParInU;
  double                                                      myLastParInU;
  double                                                      myFirstParInV;
  double                                                      myLastParInV;
  GeomAbs_IsoType                                             myFavoriteIso;
  GeomAbs_Shape                                               myContInU;
  GeomAbs_Shape                                               myContInV;
  int                                                         myPrecisionCode;
  int                                                         myMaxDegInU;
  int                                                         myMaxDegInV;
  int                                                         myMaxPatches;
  AdvApp2Var_Context                                          myConditions;
  AdvApp2Var_Network                                          myResult;
  AdvApp2Var_Framework                                        myConstraints;
  bool                                                        myDone;
  bool                                                        myHasResult;
  occ::handle<NCollection_HArray1<occ::handle<Geom_Surface>>> mySurfaces;
  int                                                         myDegreeInU;
  int                                                         myDegreeInV;
  occ::handle<NCollection_HArray1<double>>                    my1DMaxError;
  occ::handle<NCollection_HArray1<double>>                    my1DAverageError;
  occ::handle<NCollection_HArray1<double>>                    my1DUFrontError;
  occ::handle<NCollection_HArray1<double>>                    my1DVFrontError;
  occ::handle<NCollection_HArray1<double>>                    my2DMaxError;
  occ::handle<NCollection_HArray1<double>>                    my2DAverageError;
  occ::handle<NCollection_HArray1<double>>                    my2DUFrontError;
  occ::handle<NCollection_HArray1<double>>                    my2DVFrontError;
  occ::handle<NCollection_HArray1<double>>                    my3DMaxError;
  occ::handle<NCollection_HArray1<double>>                    my3DAverageError;
  occ::handle<NCollection_HArray1<double>>                    my3DUFrontError;
  occ::handle<NCollection_HArray1<double>>                    my3DVFrontError;
  double                                                      myCriterionError;
};

#include <Geom_Surface.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Geom_BSplineSurface.hpp>

inline bool AdvApp2Var_ApproxAFunc2Var::IsDone() const
{
  return myDone;
}

inline bool AdvApp2Var_ApproxAFunc2Var::HasResult() const
{
  return myHasResult;
}

inline occ::handle<Geom_BSplineSurface> AdvApp2Var_ApproxAFunc2Var::Surface(
  const int SSPIndex) const
{
  return occ::down_cast<Geom_BSplineSurface>(mySurfaces->Value(SSPIndex));
}

inline int AdvApp2Var_ApproxAFunc2Var::UDegree() const
{
  return myDegreeInU;
}

inline int AdvApp2Var_ApproxAFunc2Var::VDegree() const
{
  return myDegreeInV;
}

inline int AdvApp2Var_ApproxAFunc2Var::NumSubSpaces(const int Dimension) const
{
  return myNumSubSpaces[Dimension - 1];
}
