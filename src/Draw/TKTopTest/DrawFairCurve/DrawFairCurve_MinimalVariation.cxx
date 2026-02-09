

#include <DrawFairCurve_MinimalVariation.hpp>
#include <FairCurve_MinimalVariation.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DrawFairCurve_MinimalVariation, DrawFairCurve_Batten)

DrawFairCurve_MinimalVariation::DrawFairCurve_MinimalVariation(void* const TheMVC)
    : DrawFairCurve_Batten(TheMVC)

{
  SetColor(Draw_jaune);
}

void DrawFairCurve_MinimalVariation::SetCurvature(const int Side, const double Rho)
{
  if (Side == 1)
  {
    ((FairCurve_MinimalVariation*)MyBatten)->SetCurvature1(Rho);
    ((FairCurve_MinimalVariation*)MyBatten)->SetConstraintOrder1(2);
  }
  else
  {
    ((FairCurve_MinimalVariation*)MyBatten)->SetCurvature2(Rho);
    ((FairCurve_MinimalVariation*)MyBatten)->SetConstraintOrder2(2);
  }
  Compute();
}

void DrawFairCurve_MinimalVariation::FreeCurvature(const int Side)
{
  if (Side == 1)
  {
    if (((FairCurve_MinimalVariation*)MyBatten)->GetConstraintOrder1() > 1)
    {
      ((FairCurve_MinimalVariation*)MyBatten)->SetConstraintOrder1(1);
    }
  }
  else
  {
    if (((FairCurve_MinimalVariation*)MyBatten)->GetConstraintOrder2() > 1)
    {
      ((FairCurve_MinimalVariation*)MyBatten)->SetConstraintOrder2(1);
    }
  }
  Compute();
}

void DrawFairCurve_MinimalVariation::SetPhysicalRatio(const double Ratio)
{
  ((FairCurve_MinimalVariation*)MyBatten)->SetPhysicalRatio(Ratio);
  Compute();
}

double DrawFairCurve_MinimalVariation::GetCurvature(const int Side) const
{
  if (Side == 1)
  {
    return ((FairCurve_MinimalVariation*)MyBatten)->GetCurvature1();
  }
  else
  {
    return ((FairCurve_MinimalVariation*)MyBatten)->GetCurvature2();
  }
}

double DrawFairCurve_MinimalVariation::GetPhysicalRatio() const
{
  return ((FairCurve_MinimalVariation*)MyBatten)->GetPhysicalRatio();
}
