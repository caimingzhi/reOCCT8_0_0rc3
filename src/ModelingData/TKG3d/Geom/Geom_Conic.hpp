#pragma once

#include <gp_Ax2.hpp>
#include <Geom_Curve.hpp>

class Geom_Conic : public Geom_Curve
{
public:
  void SetAxis(const gp_Ax1& theA1) { pos.SetAxis(theA1); }

  void SetLocation(const gp_Pnt& theP) { pos.SetLocation(theP); }

  void SetPosition(const gp_Ax2& theA2) { pos = theA2; }

  const gp_Ax1& Axis() const { return pos.Axis(); }

  const gp_Pnt& Location() const { return pos.Location(); }

  const gp_Ax2& Position() const { return pos; }

  virtual double Eccentricity() const = 0;

  Standard_EXPORT gp_Ax1 XAxis() const;

  Standard_EXPORT gp_Ax1 YAxis() const;

  Standard_EXPORT void Reverse() override;

  Standard_EXPORT double ReversedParameter(const double U) const override = 0;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT bool IsCN(const int N) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_Conic, Geom_Curve)

protected:
  gp_Ax2 pos;
};
