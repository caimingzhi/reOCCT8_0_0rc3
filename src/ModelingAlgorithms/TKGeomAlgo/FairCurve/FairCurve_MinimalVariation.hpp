#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <FairCurve_Batten.hpp>
#include <FairCurve_AnalysisCode.hpp>
#include <Standard_OStream.hpp>
class gp_Pnt2d;
class gp_Vec2d;

class FairCurve_MinimalVariation : public FairCurve_Batten
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT FairCurve_MinimalVariation(const gp_Pnt2d& P1,
                                             const gp_Pnt2d& P2,
                                             const double    Heigth,
                                             const double    Slope         = 0,
                                             const double    PhysicalRatio = 0);

  void SetCurvature1(const double Curvature);

  void SetCurvature2(const double Curvature);

  void SetPhysicalRatio(const double Ratio);

  Standard_EXPORT bool Compute(FairCurve_AnalysisCode& ACode,
                               const int               NbIterations = 50,
                               const double            Tolerance    = 1.0e-3) override;

  double GetCurvature1() const;

  double GetCurvature2() const;

  double GetPhysicalRatio() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const override;

private:
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
