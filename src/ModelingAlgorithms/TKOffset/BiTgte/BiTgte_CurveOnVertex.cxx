// Created on: 1997-03-21
// Created by: Bruno DUMORTIER
// Copyright (c) 1997-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <BiTgte_CurveOnVertex.hpp>

#include <Adaptor3d_Curve.hpp>
#include <BRep_Tool.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Lin.hpp>
#include <gp_Parab.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_NotImplemented.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BiTgte_CurveOnVertex, Adaptor3d_Curve)

//=================================================================================================

BiTgte_CurveOnVertex::BiTgte_CurveOnVertex()
    : myFirst(0.0),
      myLast(0.0)
{
}

//=================================================================================================

BiTgte_CurveOnVertex::BiTgte_CurveOnVertex(const TopoDS_Edge&   theEonF,
                                           const TopoDS_Vertex& theVertex)
    : myFirst(0.0),
      myLast(0.0)
{
  Init(theEonF, theVertex);
}

//=================================================================================================

void BiTgte_CurveOnVertex::Init(const TopoDS_Edge& EonF, const TopoDS_Vertex& V)
{
  BRep_Tool::Range(EonF, myFirst, myLast);
  myPnt = BRep_Tool::Pnt(V);
}

//=================================================================================================

double BiTgte_CurveOnVertex::FirstParameter() const
{
  return myFirst;
}

//=================================================================================================

double BiTgte_CurveOnVertex::LastParameter() const
{
  return myLast;
}

//=================================================================================================

GeomAbs_Shape BiTgte_CurveOnVertex::Continuity() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

int BiTgte_CurveOnVertex::NbIntervals(const GeomAbs_Shape) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

void BiTgte_CurveOnVertex::Intervals(NCollection_Array1<double>&, const GeomAbs_Shape) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

occ::handle<Adaptor3d_Curve> BiTgte_CurveOnVertex::Trim(const double,
                                                        const double,
                                                        const double) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

bool BiTgte_CurveOnVertex::IsClosed() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

bool BiTgte_CurveOnVertex::IsPeriodic() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

double BiTgte_CurveOnVertex::Period() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

gp_Pnt BiTgte_CurveOnVertex::Value(const double) const
{
  return myPnt;
}

//=================================================================================================

void BiTgte_CurveOnVertex::D0(const double /*U*/, gp_Pnt& P) const
{
  P = myPnt;
}

//=================================================================================================

void BiTgte_CurveOnVertex::D1(const double, gp_Pnt&, gp_Vec&) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

void BiTgte_CurveOnVertex::D2(const double, gp_Pnt&, gp_Vec&, gp_Vec&) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

void BiTgte_CurveOnVertex::D3(const double, gp_Pnt&, gp_Vec&, gp_Vec&, gp_Vec&) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

gp_Vec BiTgte_CurveOnVertex::DN(const double, const int) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

double BiTgte_CurveOnVertex::Resolution(const double) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

GeomAbs_CurveType BiTgte_CurveOnVertex::GetType() const
{
  return GeomAbs_OtherCurve;
}

//=================================================================================================

gp_Lin BiTgte_CurveOnVertex::Line() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

gp_Circ BiTgte_CurveOnVertex::Circle() const
{
  throw Standard_NoSuchObject("BiTgte_CurveOnVertex::Circle");
}

//=================================================================================================

gp_Elips BiTgte_CurveOnVertex::Ellipse() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

gp_Hypr BiTgte_CurveOnVertex::Hyperbola() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

gp_Parab BiTgte_CurveOnVertex::Parabola() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

int BiTgte_CurveOnVertex::Degree() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

bool BiTgte_CurveOnVertex::IsRational() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

int BiTgte_CurveOnVertex::NbPoles() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

int BiTgte_CurveOnVertex::NbKnots() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

occ::handle<Geom_BezierCurve> BiTgte_CurveOnVertex::Bezier() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}

//=================================================================================================

occ::handle<Geom_BSplineCurve> BiTgte_CurveOnVertex::BSpline() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnVertex");
}
