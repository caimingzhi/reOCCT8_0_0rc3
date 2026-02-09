#include <Geom2d_Conic.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom2d_Conic, Geom2d_Curve)

gp_Ax2d Geom2d_Conic::XAxis() const
{
  return gp_Ax2d(pos.Location(), pos.XDirection());
}

gp_Ax2d Geom2d_Conic::YAxis() const
{
  return gp_Ax2d(pos.Location(), pos.YDirection());
}

void Geom2d_Conic::Reverse()
{
  gp_Dir2d Temp = pos.YDirection();
  Temp.Reverse();
  pos.SetAxis(gp_Ax22d(pos.Location(), pos.XDirection(), Temp));
}

GeomAbs_Shape Geom2d_Conic::Continuity() const
{
  return GeomAbs_CN;
}

bool Geom2d_Conic::IsCN(const int) const
{
  return true;
}

void Geom2d_Conic::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom2d_Curve)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &pos)
}
