#pragma once

#include <Standard.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <math_Vector.hpp>
class FEmTool_Curve;
class math_Matrix;

//! defined criterion to smooth points in curve
class AppDef_SmoothCriterion : public Standard_Transient
{

public:
  Standard_EXPORT virtual void SetParameters(
    const occ::handle<NCollection_HArray1<double>>& Parameters) = 0;

  Standard_EXPORT virtual void SetCurve(const occ::handle<FEmTool_Curve>& C) = 0;

  Standard_EXPORT virtual void GetCurve(occ::handle<FEmTool_Curve>& C) const = 0;

  Standard_EXPORT virtual void SetEstimation(const double E1, const double E2, const double E3) = 0;

  Standard_EXPORT virtual double& EstLength() = 0;

  Standard_EXPORT virtual void GetEstimation(double& E1, double& E2, double& E3) const = 0;

  Standard_EXPORT virtual occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<int>>>>
    AssemblyTable() const = 0;

  Standard_EXPORT virtual occ::handle<NCollection_HArray2<int>> DependenceTable() const = 0;

  Standard_EXPORT virtual int QualityValues(const double J1min,
                                            const double J2min,
                                            const double J3min,
                                            double&      J1,
                                            double&      J2,
                                            double&      J3) = 0;

  Standard_EXPORT virtual void ErrorValues(double& MaxError,
                                           double& QuadraticError,
                                           double& AverageError) = 0;

  Standard_EXPORT virtual void Hessian(const int    Element,
                                       const int    Dimension1,
                                       const int    Dimension2,
                                       math_Matrix& H) = 0;

  Standard_EXPORT virtual void Gradient(const int Element, const int Dimension, math_Vector& G) = 0;

  //! Convert the assembly Vector in an Curve;
  Standard_EXPORT virtual void InputVector(
    const math_Vector&                                                             X,
    const occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<int>>>>& AssTable) = 0;

  Standard_EXPORT virtual void SetWeight(const double QuadraticWeight,
                                         const double QualityWeight,
                                         const double percentJ1,
                                         const double percentJ2,
                                         const double percentJ3) = 0;

  Standard_EXPORT virtual void GetWeight(double& QuadraticWeight, double& QualityWeight) const = 0;

  Standard_EXPORT virtual void SetWeight(const NCollection_Array1<double>& Weight) = 0;

  DEFINE_STANDARD_RTTIEXT(AppDef_SmoothCriterion, Standard_Transient)
};
