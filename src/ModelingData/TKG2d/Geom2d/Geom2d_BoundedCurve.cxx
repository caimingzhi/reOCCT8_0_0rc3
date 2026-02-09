#include <Geom2d_BoundedCurve.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom2d_BoundedCurve, Geom2d_Curve)

void Geom2d_BoundedCurve::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom2d_Curve)
}
