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
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>

#ifdef OCCT_DEBUG
extern void FUN_REINIT();
// extern int FUN_addepc(const TopoDS_Shape& ed,const TopoDS_Shape& f);
#endif

// ----------------------------------------------------------------------
// TopOpeBRepTool_faulty.cxx
// ----------------------------------------------------------------------
// Standard_IMPORT gp_Pnt2d FUN_GetVParonF(const TopoDS_Edge& E, const TopoDS_Face& F, const
// int Index); Standard_IMPORT double FUN_toluv(const GeomAdaptor_Surface& GAS,
// const double& tol3d); Standard_IMPORT void FUN_tool_Vertices(const TopoDS_Edge& E,
// NCollection_Array1<TopoDS_Shape>& vertices); Standard_IMPORT void FUN_mapVloe(const TopoDS_Shape&
// F, NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>,
// TopTools_ShapeMapHasher>& mapVloe);

// Standard_IMPORT bool FUN_DetectEdgeswithfaultyUV(const TopoDS_Face& Fin, const
// TopoDS_Shape& fF, const NCollection_List<TopoDS_Shape>& ISOEds, 						const
// bool has2fybounds,
// NCollection_List<TopoDS_Shape>& lfyE, int& Ivfaulty, 						const
// bool& stopatfirst=false); Standard_IMPORT bool
// FUN_DetectEdgewithfaultyUV(const
// TopoDS_Face& Fin, const TopoDS_Shape& fF, const NCollection_List<TopoDS_Shape>& ISOEds, const
// bool has2fybounds, TopoDS_Shape& fyE, int& Ivfaulty); Standard_IMPORT
// bool FUN_DetectFaultyClosingEdge(const TopoDS_Face& Fin,const NCollection_List<TopoDS_Shape>&
// Eds,const NCollection_List<TopoDS_Shape>& cEds,NCollection_List<TopoDS_Shape>& fyE);
// Standard_IMPORT bool FUN_isUVClosed(const TopoDS_Face& F, const TopoDS_Face& fF);

// ----------------------------------------------------------------------
// TopOpeBRepTool_PURGE.cxx
// ----------------------------------------------------------------------
// Standard_IMPORT void FUN_tool_ttranslate(const gp_Vec2d& tvector, const TopoDS_Face& fF,
// TopoDS_Edge& fyE);
