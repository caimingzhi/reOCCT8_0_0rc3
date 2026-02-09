

#include <DBRep.hpp>
#include <DrawTrSurf.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Geometry.hpp>
#include <Geom_Surface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>
#include <XSDRAW_Vars.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XSDRAW_Vars, XSControl_Vars)

XSDRAW_Vars::XSDRAW_Vars() = default;

void XSDRAW_Vars::Set(const char* name, const occ::handle<Standard_Transient>& val)
{

  DeclareAndCast(Geom_Geometry, geom, val);
  if (!geom.IsNull())
  {
    DrawTrSurf::Set(name, geom);
    return;
  }
  DeclareAndCast(Geom2d_Curve, g2d, val);
  if (!g2d.IsNull())
  {
    DrawTrSurf::Set(name, geom);
    return;
  }
}

occ::handle<Geom_Geometry> XSDRAW_Vars::GetGeom(const char*& name) const
{
  return DrawTrSurf::Get(name);
}

occ::handle<Geom2d_Curve> XSDRAW_Vars::GetCurve2d(const char*& name) const
{
  return DrawTrSurf::GetCurve2d(name);
}

occ::handle<Geom_Curve> XSDRAW_Vars::GetCurve(const char*& name) const
{
  return DrawTrSurf::GetCurve(name);
}

occ::handle<Geom_Surface> XSDRAW_Vars::GetSurface(const char*& name) const
{
  return DrawTrSurf::GetSurface(name);
}

void XSDRAW_Vars::SetPoint(const char* name, const gp_Pnt& val)
{

  DrawTrSurf::Set(name, val);
}

bool XSDRAW_Vars::GetPoint(const char*& name, gp_Pnt& pnt) const
{
  return DrawTrSurf::GetPoint(name, pnt);
}

void XSDRAW_Vars::SetPoint2d(const char* name, const gp_Pnt2d& val)
{

  DrawTrSurf::Set(name, val);
}

bool XSDRAW_Vars::GetPoint2d(const char*& name, gp_Pnt2d& pnt) const
{

  return DrawTrSurf::GetPoint2d(name, pnt);
}

void XSDRAW_Vars::SetShape(const char* name, const TopoDS_Shape& val)
{
  DBRep::Set(name, val);
}

TopoDS_Shape XSDRAW_Vars::GetShape(const char*& name) const
{

  return DBRep::Get(name);
}
