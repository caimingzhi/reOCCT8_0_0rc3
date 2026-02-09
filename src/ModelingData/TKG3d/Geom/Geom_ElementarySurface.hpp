#pragma once

#include <gp_Ax3.hpp>
#include <Geom_Surface.hpp>

class Geom_ElementarySurface : public Geom_Surface
{
public:
  void SetAxis(const gp_Ax1& theA1) { pos.SetAxis(theA1); }

  void SetLocation(const gp_Pnt& theLoc) { pos.SetLocation(theLoc); }

  void SetPosition(const gp_Ax3& theAx3) { pos = theAx3; }

  const gp_Ax1& Axis() const { return pos.Axis(); }

  const gp_Pnt& Location() const { return pos.Location(); }

  const gp_Ax3& Position() const { return pos; }

  Standard_EXPORT void UReverse() override;

  Standard_EXPORT double UReversedParameter(const double U) const override = 0;

  Standard_EXPORT void VReverse() override;

  Standard_EXPORT double VReversedParameter(const double V) const override = 0;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT bool IsCNu(const int N) const override;

  Standard_EXPORT bool IsCNv(const int N) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_ElementarySurface, Geom_Surface)

protected:
  gp_Ax3 pos;
};
