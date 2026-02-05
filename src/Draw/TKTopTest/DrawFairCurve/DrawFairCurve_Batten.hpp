#pragma once

#include <Standard.hpp>

#include <DrawTrSurf_BSplineCurve2d.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>
class gp_Pnt2d;

//! Interactive Draw object of type "Batten"
class DrawFairCurve_Batten : public DrawTrSurf_BSplineCurve2d
{

public:
  Standard_EXPORT DrawFairCurve_Batten(void* const TheBatten);

  Standard_EXPORT void Compute();

  Standard_EXPORT void SetPoint(const int Side, const gp_Pnt2d& Point);

  Standard_EXPORT void SetAngle(const int Side, const double Angle);

  Standard_EXPORT void SetSliding(const double Length);

  Standard_EXPORT void SetHeight(const double Heigth);

  Standard_EXPORT void SetSlope(const double Slope);

  Standard_EXPORT double GetAngle(const int Side) const;

  Standard_EXPORT double GetSliding() const;

  Standard_EXPORT void FreeSliding();

  Standard_EXPORT void FreeAngle(const int Side);

  //! For variable dump.
  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  DEFINE_STANDARD_RTTIEXT(DrawFairCurve_Batten, DrawTrSurf_BSplineCurve2d)

protected:
  void* MyBatten;
};
