#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <XSControl_Vars.hpp>
class Standard_Transient;
class Geom_Geometry;
class Geom2d_Curve;
class Geom_Curve;
class Geom_Surface;
class gp_Pnt;
class gp_Pnt2d;
class TopoDS_Shape;

//! Vars for DRAW session (i.e. DBRep and DrawTrSurf)
class XSDRAW_Vars : public XSControl_Vars
{

public:
  Standard_EXPORT XSDRAW_Vars();

  Standard_EXPORT void Set(const char* name, const occ::handle<Standard_Transient>& val) override;

  Standard_EXPORT occ::handle<Geom_Geometry> GetGeom(const char*& name) const override;

  Standard_EXPORT occ::handle<Geom2d_Curve> GetCurve2d(const char*& name) const override;

  Standard_EXPORT occ::handle<Geom_Curve> GetCurve(const char*& name) const override;

  Standard_EXPORT occ::handle<Geom_Surface> GetSurface(const char*& name) const override;

  Standard_EXPORT void SetPoint(const char* name, const gp_Pnt& val) override;

  Standard_EXPORT void SetPoint2d(const char* name, const gp_Pnt2d& val) override;

  Standard_EXPORT bool GetPoint(const char*& name, gp_Pnt& pnt) const override;

  Standard_EXPORT bool GetPoint2d(const char*& name, gp_Pnt2d& pnt) const override;

  Standard_EXPORT void SetShape(const char* name, const TopoDS_Shape& val) override;

  Standard_EXPORT TopoDS_Shape GetShape(const char*& name) const override;

  DEFINE_STANDARD_RTTIEXT(XSDRAW_Vars, XSControl_Vars)
};
