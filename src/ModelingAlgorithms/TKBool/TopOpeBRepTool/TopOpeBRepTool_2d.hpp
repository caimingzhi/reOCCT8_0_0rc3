// Created on: 1998-03-23
// Created by: Jean Yves LEBEY
// Copyright (c) 1998-1999 Matra Datavision
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

#ifndef _TopOpeBRepTool_2d_HeaderFile
#define _TopOpeBRepTool_2d_HeaderFile
#include <Geom2d_Curve.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_List.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <TCollection_AsciiString.hpp>

Standard_EXPORT int  FC2D_Prepare(const TopoDS_Shape& S1, const TopoDS_Shape& S2);
Standard_EXPORT bool FC2D_HasC3D(const TopoDS_Edge& E);
Standard_EXPORT bool FC2D_HasCurveOnSurface(const TopoDS_Edge& E, const TopoDS_Face& F);
Standard_EXPORT bool FC2D_HasOldCurveOnSurface(const TopoDS_Edge&         E,
                                               const TopoDS_Face&         F,
                                               occ::handle<Geom2d_Curve>& C2D,
                                               double&                    f,
                                               double&                    l,
                                               double&                    tol);
Standard_EXPORT bool FC2D_HasOldCurveOnSurface(const TopoDS_Edge&         E,
                                               const TopoDS_Face&         F,
                                               occ::handle<Geom2d_Curve>& C2D);
Standard_EXPORT bool FC2D_HasNewCurveOnSurface(const TopoDS_Edge&         E,
                                               const TopoDS_Face&         F,
                                               occ::handle<Geom2d_Curve>& C2D,
                                               double&                    f,
                                               double&                    l,
                                               double&                    tol);
Standard_EXPORT bool FC2D_HasNewCurveOnSurface(const TopoDS_Edge&         E,
                                               const TopoDS_Face&         F,
                                               occ::handle<Geom2d_Curve>& C2D);
Standard_EXPORT occ::handle<Geom2d_Curve> FC2D_CurveOnSurface(const TopoDS_Edge& E,
                                                              const TopoDS_Face& F,
                                                              double&            f,
                                                              double&            l,
                                                              double&            tol,
                                                              const bool         trim3d = false);
Standard_EXPORT occ::handle<Geom2d_Curve> FC2D_CurveOnSurface(const TopoDS_Edge& E,
                                                              const TopoDS_Face& F,
                                                              const TopoDS_Edge& EF,
                                                              double&            f,
                                                              double&            l,
                                                              double&            tol,
                                                              const bool         trim3d = false);
// modified by NIZHNY-MZV
Standard_EXPORT occ::handle<Geom2d_Curve> FC2D_MakeCurveOnSurface(const TopoDS_Edge& E,
                                                                  const TopoDS_Face& F,
                                                                  double&            f,
                                                                  double&            l,
                                                                  double&            tol,
                                                                  const bool trim3d = false);
Standard_EXPORT occ::handle<Geom2d_Curve> FC2D_EditableCurveOnSurface(const TopoDS_Edge& E,
                                                                      const TopoDS_Face& F,
                                                                      double&            f,
                                                                      double&            l,
                                                                      double&            tol,
                                                                      const bool trim3d = false);
Standard_EXPORT int FC2D_AddNewCurveOnSurface(const occ::handle<Geom2d_Curve>& PC,
                                              const TopoDS_Edge&               E,
                                              const TopoDS_Face&               F,
                                              const double&                    f,
                                              const double&                    l,
                                              const double&                    tol);
#endif
