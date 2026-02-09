#include <Geom_Curve.hpp>
#include <Geom_SweptSurface.hpp>
#include <gp_Dir.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_SweptSurface, Geom_Surface)

GeomAbs_Shape Geom_SweptSurface::Continuity() const
{
  return smooth;
}

const gp_Dir& Geom_SweptSurface::Direction() const
{
  return direction;
}

occ::handle<Geom_Curve> Geom_SweptSurface::BasisCurve() const
{
  return basisCurve;
}

void Geom_SweptSurface::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom_Surface)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, basisCurve.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &direction)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, smooth)
}
