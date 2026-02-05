#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_DataMap.hpp>
#include <TCollection_AsciiString.hpp>
class Geom_Geometry;
class Geom2d_Curve;
class Geom_Curve;
class Geom_Surface;
class gp_Pnt;
class gp_Pnt2d;
class TopoDS_Shape;

//! Defines a receptacle for externally defined variables, each
//! one has a name
//!
//! I.E. a WorkSession for XSTEP is generally used inside a
//! context, which brings variables, especially shapes and
//! geometries. For instance DRAW or an application engine
//!
//! This class provides a common form for this. It also provides
//! a default implementation (locally recorded variables in a
//! dictionary), but which is aimed to be redefined
class XSControl_Vars : public Standard_Transient
{

public:
  Standard_EXPORT XSControl_Vars();

  Standard_EXPORT virtual void Set(const char* name, const occ::handle<Standard_Transient>& val);

  Standard_EXPORT virtual occ::handle<Standard_Transient> Get(const char*& name) const;

  Standard_EXPORT virtual occ::handle<Geom_Geometry> GetGeom(const char*& name) const;

  Standard_EXPORT virtual occ::handle<Geom2d_Curve> GetCurve2d(const char*& name) const;

  Standard_EXPORT virtual occ::handle<Geom_Curve> GetCurve(const char*& name) const;

  Standard_EXPORT virtual occ::handle<Geom_Surface> GetSurface(const char*& name) const;

  Standard_EXPORT virtual void SetPoint(const char* name, const gp_Pnt& val);

  Standard_EXPORT virtual void SetPoint2d(const char* name, const gp_Pnt2d& val);

  Standard_EXPORT virtual bool GetPoint(const char*& name, gp_Pnt& pnt) const;

  Standard_EXPORT virtual bool GetPoint2d(const char*& name, gp_Pnt2d& pnt) const;

  Standard_EXPORT virtual void SetShape(const char* name, const TopoDS_Shape& val);

  Standard_EXPORT virtual TopoDS_Shape GetShape(const char*& name) const;

  DEFINE_STANDARD_RTTIEXT(XSControl_Vars, Standard_Transient)

private:
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>> thevars;
};
