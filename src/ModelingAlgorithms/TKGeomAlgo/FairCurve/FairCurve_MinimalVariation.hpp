#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <FairCurve_Batten.hpp>
#include <FairCurve_AnalysisCode.hpp>
#include <Standard_OStream.hpp>
class gp_Pnt2d;
class gp_Vec2d;

//! Computes a 2D curve using an algorithm which
//! minimizes tension, sagging, and jerk energy. As in
//! FairCurve_Batten, two reference points are used.
//! Unlike that class, FairCurve_MinimalVariation
//! requires curvature settings at the first and second
//! reference points. These are defined by the rays of
//! curvature desired at each point.
class FairCurve_MinimalVariation : public FairCurve_Batten
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs the two contact points P1 and P2 and the geometrical
  //! characteristics of the batten (elastic beam)
  //! These include the real number values for height of
  //! deformation Height, slope value Slope, and kind of
  //! energy PhysicalRatio. The kinds of energy include:
  //! -   Jerk (0)
  //! -   Sagging (1).
  //! Note that the default setting for Physical Ration is in FairCurve_Batten
  //! Other parameters are initialized as follow :
  //! - FreeSliding = False
  //! - ConstraintOrder1 = 1
  //! - ConstraintOrder2 = 1
  //! - Angle1 = 0
  //! - Angle2 = 0
  //! - Curvature1 = 0
  //! - Curvature2 = 0
  //! - SlidingFactor = 1
  //! Warning
  //! If PhysicalRatio equals 1, you cannot impose constraints on curvature.
  //! Exceptions
  //! NegativeValue if Height is less than or equal to 0.
  //! NullValue if the distance between P1 and P2 is less
  //! than or equal to the tolerance value for distance in
  //! Precision::Confusion: P1.IsEqual(P2,
  //! Precision::Confusion()). The function
  //! gp_Pnt2d::IsEqual tests to see if this is the case.
  //! Definition of the geometricals constraints
  Standard_EXPORT FairCurve_MinimalVariation(const gp_Pnt2d& P1,
                                             const gp_Pnt2d& P2,
                                             const double    Heigth,
                                             const double    Slope         = 0,
                                             const double    PhysicalRatio = 0);

  //! Allows you to set a new constraint on curvature at the first point.
  void SetCurvature1(const double Curvature);

  //! Allows you to set a new constraint on curvature at the second point.
  void SetCurvature2(const double Curvature);

  //! Allows you to set the physical ratio Ratio.
  //! The kinds of energy which you can specify include:
  //! 0 is only "Jerk" Energy
  //! 1 is only "Sagging" Energy like batten
  //! Warning: if Ratio is 1 it is impossible to impose curvature constraints.
  //! Raises DomainError if Ratio < 0 or Ratio > 1
  void SetPhysicalRatio(const double Ratio);

  //! Computes the curve with respect to the constraints,
  //! NbIterations and Tolerance. The tolerance setting
  //! allows you to control the precision of computation, and
  //! the maximum number of iterations allows you to set a limit on computation time.
  Standard_EXPORT bool Compute(FairCurve_AnalysisCode& ACode,
                               const int               NbIterations = 50,
                               const double            Tolerance    = 1.0e-3) override;

  //! Returns the first established curvature.
  double GetCurvature1() const;

  //! Returns the second established curvature.
  double GetCurvature2() const;

  //! Returns the physical ratio, or kind of energy.
  double GetPhysicalRatio() const;

  //! Prints on the stream o information on the current state
  //! of the object.
  //! Is used to redefine the operator <<.
  Standard_EXPORT void Dump(Standard_OStream& o) const override;

private:
  //! compute the curve with respect of the delta-constraints.
  Standard_EXPORT bool Compute(const gp_Vec2d&         DeltaP1,
                               const gp_Vec2d&         DeltaP2,
                               const double            DeltaAngle1,
                               const double            DeltaAngle2,
                               const double            DeltaCurvature1,
                               const double            DeltaCurvature2,
                               FairCurve_AnalysisCode& ACode,
                               const int               NbIterations,
                               const double            Tolerance);

  double OldCurvature1;
  double OldCurvature2;
  double OldPhysicalRatio;
  double NewCurvature1;
  double NewCurvature2;
  double NewPhysicalRatio;
};

inline Standard_OStream& operator<<(Standard_OStream& o, const FairCurve_MinimalVariation& MVC)
{
  MVC.Dump(o);
  return o;
}

inline void FairCurve_MinimalVariation::SetCurvature1(const double Curvature)
{
  NewCurvature1 = Curvature;
}

inline void FairCurve_MinimalVariation::SetCurvature2(const double Curvature)
{
  NewCurvature2 = Curvature;
}

inline void FairCurve_MinimalVariation::SetPhysicalRatio(const double Ratio)
{
  Standard_DomainError_Raise_if(Ratio < 0 || Ratio > 1,
                                "FairCurve_MinimalVariation::SetPhysicalRatio");
  NewPhysicalRatio = Ratio;
}

inline double FairCurve_MinimalVariation::GetCurvature1() const
{
  return OldCurvature1;
}

inline double FairCurve_MinimalVariation::GetCurvature2() const
{
  return OldCurvature2;
}

inline double FairCurve_MinimalVariation::GetPhysicalRatio() const
{
  return OldPhysicalRatio;
}
