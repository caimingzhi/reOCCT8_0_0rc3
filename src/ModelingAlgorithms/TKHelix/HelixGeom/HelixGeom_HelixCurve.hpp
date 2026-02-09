#pragma once

#include <Adaptor3d_Curve.hpp>
#include <GeomAbs_Shape.hpp>

class gp_Pnt;
class gp_Vec;

class HelixGeom_HelixCurve : public Adaptor3d_Curve
{
  DEFINE_STANDARD_RTTIEXT(HelixGeom_HelixCurve, Adaptor3d_Curve)
public:
  Standard_EXPORT HelixGeom_HelixCurve();

  Standard_EXPORT void Load();

  Standard_EXPORT void Load(const double aT1,
                            const double aT2,
                            const double aPitch,
                            const double aRStart,
                            const double aTaperAngle,
                            const bool   aIsCW);

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT double Resolution(const double R3d) const override;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT double Period() const override;

  Standard_EXPORT gp_Pnt Value(const double U) const override;

  Standard_EXPORT void D0(const double U, gp_Pnt& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt& P, gp_Vec& V1) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const override;

  Standard_EXPORT gp_Vec DN(const double U, const int N) const override;

protected:
  double myFirst;
  double myLast;
  double myPitch;
  double myRStart;
  double myTaperAngle;
  bool   myIsClockWise;
  double myC1;
  double myTgBeta;
  double myTolAngle;
};
