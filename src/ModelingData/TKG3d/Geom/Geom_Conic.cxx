#include <Geom_Conic.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_Conic, Geom_Curve)

void Geom_Conic::Reverse()
{
  gp_Dir Vz = pos.Direction();
  Vz.Reverse();
  pos.SetDirection(Vz);
}

GeomAbs_Shape Geom_Conic::Continuity() const
{
  return GeomAbs_CN;
}

gp_Ax1 Geom_Conic::XAxis() const
{
  return gp_Ax1(pos.Location(), pos.XDirection());
}

gp_Ax1 Geom_Conic::YAxis() const
{
  return gp_Ax1(pos.Location(), pos.YDirection());
}

bool Geom_Conic::IsCN(const int) const
{
  return true;
}

void Geom_Conic::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom_Curve)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &pos)
}
