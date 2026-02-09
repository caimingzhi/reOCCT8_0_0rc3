#include <Geom_ElementarySurface.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_ElementarySurface, Geom_Surface)

GeomAbs_Shape Geom_ElementarySurface::Continuity() const
{
  return GeomAbs_CN;
}

bool Geom_ElementarySurface::IsCNu(const int) const
{
  return true;
}

bool Geom_ElementarySurface::IsCNv(const int) const
{
  return true;
}

void Geom_ElementarySurface::UReverse()
{
  pos.YReverse();
}

void Geom_ElementarySurface::VReverse()
{
  pos.ZReverse();
}

void Geom_ElementarySurface::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom_Surface)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &pos)
}
