#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Dir.hpp>
#include <GeomAbs_Shape.hpp>
#include <Geom_Surface.hpp>
class Geom_Curve;

class Geom_SweptSurface : public Geom_Surface
{

public:
  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT const gp_Dir& Direction() const;

  Standard_EXPORT occ::handle<Geom_Curve> BasisCurve() const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_SweptSurface, Geom_Surface)

protected:
  occ::handle<Geom_Curve> basisCurve;
  gp_Dir                  direction;
  GeomAbs_Shape           smooth;
};
