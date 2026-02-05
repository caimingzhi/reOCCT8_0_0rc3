#pragma once

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

#include <GeomAbs_CurveType.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Surface.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>
#include <Bnd_Box2d.hpp>

Standard_EXPORT occ::handle<Geom2d_Curve> BASISCURVE2D(const occ::handle<Geom2d_Curve>& C);
// Standard_EXPORT bool FUN_tool_IsUViso(const occ::handle<Geom2d_Curve>&
// PC,bool& isoU,bool& isoV,gp_Dir2d& d2d,gp_Pnt2d& O2d);
Standard_EXPORT gp_Dir FUN_tool_dirC(const double par, const occ::handle<Geom_Curve>& C);
Standard_EXPORT bool   FUN_tool_onapex(const gp_Pnt2d& p2d, const occ::handle<Geom_Surface>& S);
Standard_EXPORT gp_Dir FUN_tool_ngS(const gp_Pnt2d& p2d, const occ::handle<Geom_Surface>& S);

// ----------------------------------------------------------------------
// curve type,surface type :
// ----------------------------------------------------------------------
Standard_EXPORT bool FUN_tool_line(const occ::handle<Geom_Curve>& C3d);
Standard_EXPORT bool FUN_tool_line(const occ::handle<Geom2d_Curve>& C2d);
Standard_EXPORT bool FUN_quadCT(const GeomAbs_CurveType& CT);
Standard_EXPORT bool FUN_tool_quad(const occ::handle<Geom_Curve>& C3d);
Standard_EXPORT bool FUN_tool_quad(const occ::handle<Geom2d_Curve>& pc);
Standard_EXPORT bool FUN_tool_quad(const occ::handle<Geom_Surface>& S);
Standard_EXPORT bool FUN_tool_closed(const occ::handle<Geom_Surface>& S,
                                     bool&                            uclosed,
                                     double&                          uperiod,
                                     bool&                            vclosed,
                                     double&                          vperiod);
Standard_EXPORT void FUN_tool_UpdateBnd2d(Bnd_Box2d& B2d, const Bnd_Box2d& newB2d);

// ----------------------------------------------------------------------
// oriented vectors :
// ----------------------------------------------------------------------
Standard_EXPORT gp_Dir   FUN_tool_nCinsideS(const gp_Dir& tgC, const gp_Dir& ngS);
Standard_EXPORT gp_Dir2d FUN_tool_nC2dINSIDES(const gp_Dir2d& tgC2d);
