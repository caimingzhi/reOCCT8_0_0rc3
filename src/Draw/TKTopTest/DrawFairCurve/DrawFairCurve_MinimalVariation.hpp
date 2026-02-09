#pragma once

#include <Standard.hpp>

#include <DrawFairCurve_Batten.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>

class DrawFairCurve_MinimalVariation : public DrawFairCurve_Batten
{

public:
  Standard_EXPORT DrawFairCurve_MinimalVariation(void* const TheMVC);

  Standard_EXPORT void SetCurvature(const int Side, const double Rho);

  Standard_EXPORT void SetPhysicalRatio(const double Ratio);

  Standard_EXPORT double GetCurvature(const int Side) const;

  Standard_EXPORT double GetPhysicalRatio() const;

  Standard_EXPORT void FreeCurvature(const int Side);

  DEFINE_STANDARD_RTTIEXT(DrawFairCurve_MinimalVariation, DrawFairCurve_Batten)
};
