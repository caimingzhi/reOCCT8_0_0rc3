#pragma once

#include <gp_Ax22d.hpp>
#include <Geom2d_Curve.hpp>

class Geom2d_Conic : public Geom2d_Curve
{
public:
  void SetAxis(const gp_Ax22d& theA) { pos.SetAxis(theA); }

  void SetXAxis(const gp_Ax2d& theAX) { pos.SetXAxis(theAX); }

  void SetYAxis(const gp_Ax2d& theAY) { pos.SetYAxis(theAY); }

  void SetLocation(const gp_Pnt2d& theP) { pos.SetLocation(theP); }

  Standard_EXPORT gp_Ax2d XAxis() const;

  Standard_EXPORT gp_Ax2d YAxis() const;

  Standard_EXPORT virtual double Eccentricity() const = 0;

  const gp_Pnt2d& Location() const { return pos.Location(); }

  const gp_Ax22d& Position() const { return pos; }

  Standard_EXPORT void Reverse() override;

  Standard_EXPORT double ReversedParameter(const double U) const override = 0;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT bool IsCN(const int N) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_Conic, Geom2d_Curve)

protected:
  gp_Ax22d pos;
};
