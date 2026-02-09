#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_Curve.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
class gp_Trsf;
class gp_Pnt;
class gp_Vec;

class ShapeExtend_ComplexCurve : public Geom_Curve
{

public:
  Standard_EXPORT virtual int NbCurves() const = 0;

  Standard_EXPORT virtual const occ::handle<Geom_Curve>& Curve(const int index) const = 0;

  Standard_EXPORT virtual int LocateParameter(const double U, double& UOut) const = 0;

  Standard_EXPORT virtual double LocalToGlobal(const int index, const double Ulocal) const = 0;

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  double ReversedParameter(const double U) const override;

  double FirstParameter() const override;

  double LastParameter() const override;

  bool IsClosed() const override;

  bool IsPeriodic() const override;

  GeomAbs_Shape Continuity() const override;

  bool IsCN(const int N) const override;

  Standard_EXPORT void D0(const double U, gp_Pnt& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt& P, gp_Vec& V1) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt&      P,
                          gp_Vec&      V1,
                          gp_Vec&      V2,
                          gp_Vec&      V3) const override;

  Standard_EXPORT gp_Vec DN(const double U, const int N) const override;

  Standard_EXPORT virtual double GetScaleFactor(const int ind) const = 0;

  Standard_EXPORT bool CheckConnectivity(const double Preci);

  DEFINE_STANDARD_RTTIEXT(ShapeExtend_ComplexCurve, Geom_Curve)

protected:
  Standard_EXPORT ShapeExtend_ComplexCurve();

  Standard_EXPORT void TransformDN(gp_Vec& V, const int ind, const int N) const;

  bool myClosed;
};

inline double ShapeExtend_ComplexCurve::ReversedParameter(const double U) const
{
  return (1 - U);
}

inline double ShapeExtend_ComplexCurve::FirstParameter() const
{
  return 0;
}

inline double ShapeExtend_ComplexCurve::LastParameter() const
{
  return 1;
}

inline bool ShapeExtend_ComplexCurve::IsClosed() const
{
  return myClosed;
}

inline bool ShapeExtend_ComplexCurve::IsPeriodic() const
{
  return false;
}

inline GeomAbs_Shape ShapeExtend_ComplexCurve::Continuity() const
{
  return GeomAbs_C0;
}

inline bool ShapeExtend_ComplexCurve::IsCN(const int N) const
{
  return N <= 0;
}
