#pragma once

#include <Standard.hpp>

#include <AppDef_MultiLine.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <AppDef_SmoothCriterion.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <math_Vector.hpp>
class FEmTool_ElementaryCriterion;
class FEmTool_Curve;
class math_Matrix;

//! defined an Linear Criteria to used in variational
//! Smoothing of points.
class AppDef_LinearCriteria : public AppDef_SmoothCriterion
{

public:
  Standard_EXPORT AppDef_LinearCriteria(const AppDef_MultiLine& SSP,
                                        const int               FirstPoint,
                                        const int               LastPoint);

  Standard_EXPORT void SetParameters(
    const occ::handle<NCollection_HArray1<double>>& Parameters) override;

  Standard_EXPORT void SetCurve(const occ::handle<FEmTool_Curve>& C) override;

  Standard_EXPORT void GetCurve(occ::handle<FEmTool_Curve>& C) const override;

  Standard_EXPORT void SetEstimation(const double E1, const double E2, const double E3) override;

  Standard_EXPORT double& EstLength() override;

  Standard_EXPORT void GetEstimation(double& E1, double& E2, double& E3) const override;

  Standard_EXPORT occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<int>>>>
                  AssemblyTable() const override;

  Standard_EXPORT occ::handle<NCollection_HArray2<int>> DependenceTable() const override;

  Standard_EXPORT int QualityValues(const double J1min,
                                    const double J2min,
                                    const double J3min,
                                    double&      J1,
                                    double&      J2,
                                    double&      J3) override;

  Standard_EXPORT void ErrorValues(double& MaxError,
                                   double& QuadraticError,
                                   double& AverageError) override;

  Standard_EXPORT void Hessian(const int    Element,
                               const int    Dimension1,
                               const int    Dimension2,
                               math_Matrix& H) override;

  Standard_EXPORT void Gradient(const int Element, const int Dimension, math_Vector& G) override;

  //! Convert the assembly Vector in an Curve;
  Standard_EXPORT void InputVector(
    const math_Vector&                                                             X,
    const occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<int>>>>& AssTable)
    override;

  Standard_EXPORT void SetWeight(const double QuadraticWeight,
                                 const double QualityWeight,
                                 const double percentJ1,
                                 const double percentJ2,
                                 const double percentJ3) override;

  Standard_EXPORT void GetWeight(double& QuadraticWeight, double& QualityWeight) const override;

  Standard_EXPORT void SetWeight(const NCollection_Array1<double>& Weight) override;

  DEFINE_STANDARD_RTTIEXT(AppDef_LinearCriteria, AppDef_SmoothCriterion)

private:
  Standard_EXPORT void BuildCache(const int E);

  AppDef_MultiLine                         mySSP;
  occ::handle<NCollection_HArray1<double>> myParameters;
  occ::handle<NCollection_HArray1<double>> myCache;
  occ::handle<FEmTool_ElementaryCriterion> myCriteria[3];
  double                                   myEstimation[3];
  double                                   myQuadraticWeight;
  double                                   myQualityWeight;
  double                                   myPercent[3];
  NCollection_Array1<double>               myPntWeight;
  occ::handle<FEmTool_Curve>               myCurve;
  double                                   myLength;
  int                                      myE;
  int                                      IF;
  int                                      IL;
};
