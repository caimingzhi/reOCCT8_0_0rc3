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

#include <Geom_Surface.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Curve2d.hpp>
#include <Extrema_ExtPC.hpp>
#include <Extrema_ExtPC2d.hpp>
#include <Extrema_ExtFlag.hpp>
#include <Extrema_ExtAlgo.hpp>

// ----------------------------------------------------------------------
//  project point <P> on geometries (curve <C>,surface <S>)
// ----------------------------------------------------------------------
Standard_EXPORT void FUN_tool_bounds(const TopoDS_Edge& E, double& f, double& l);
Standard_EXPORT int  FUN_tool_getindex(const Extrema_ExtPC& ponc);
Standard_EXPORT int  FUN_tool_getindex(const Extrema_ExtPC2d& ponc);
Standard_EXPORT bool FUN_tool_projPonC(const gp_Pnt&            P,
                                       const double             tole,
                                       const BRepAdaptor_Curve& BAC,
                                       const double             pmin,
                                       const double             pmax,
                                       double&                  param,
                                       double&                  dist);
Standard_EXPORT bool FUN_tool_projPonC(const gp_Pnt&            P,
                                       const BRepAdaptor_Curve& BAC,
                                       const double             pmin,
                                       const double             pmax,
                                       double&                  param,
                                       double&                  dist);
Standard_EXPORT bool FUN_tool_projPonC(const gp_Pnt&            P,
                                       const BRepAdaptor_Curve& BAC,
                                       double&                  param,
                                       double&                  dist);
Standard_EXPORT bool FUN_tool_projPonC2D(const gp_Pnt&              P,
                                         const double               tole,
                                         const BRepAdaptor_Curve2d& BAC2D,
                                         const double               pmin,
                                         const double               pmax,
                                         double&                    param,
                                         double&                    dist);
Standard_EXPORT bool FUN_tool_projPonC2D(const gp_Pnt&              P,
                                         const BRepAdaptor_Curve2d& BAC2D,
                                         const double               pmin,
                                         const double               pmax,
                                         double&                    param,
                                         double&                    dist);
Standard_EXPORT bool FUN_tool_projPonC2D(const gp_Pnt&              P,
                                         const BRepAdaptor_Curve2d& BAC2D,
                                         double&                    param,
                                         double&                    dist);
Standard_EXPORT bool FUN_tool_projPonS(const gp_Pnt&                    P,
                                       const occ::handle<Geom_Surface>& S,
                                       gp_Pnt2d&                        UV,
                                       double&                          dist,
                                       const Extrema_ExtFlag anExtFlag = Extrema_ExtFlag_MINMAX,
                                       const Extrema_ExtAlgo anExtAlgo = Extrema_ExtAlgo_Grad);

// ----------------------------------------------------------------------
//  project point <P> on topologies (edge <E>,face <F>)
// ----------------------------------------------------------------------
Standard_EXPORT bool FUN_tool_projPonE(const gp_Pnt&      P,
                                       const double       tole,
                                       const TopoDS_Edge& E,
                                       double&            param,
                                       double&            dist);
Standard_EXPORT bool FUN_tool_projPonE(const gp_Pnt&      P,
                                       const TopoDS_Edge& E,
                                       double&            param,
                                       double&            dist);
Standard_EXPORT bool FUN_tool_projPonboundedF(const gp_Pnt&      P,
                                              const TopoDS_Face& F,
                                              gp_Pnt2d&          UV,
                                              double&            dist);
Standard_EXPORT bool FUN_tool_projPonF(const gp_Pnt&         P,
                                       const TopoDS_Face&    F,
                                       gp_Pnt2d&             UV,
                                       double&               dist,
                                       const Extrema_ExtFlag anExtFlag = Extrema_ExtFlag_MINMAX,
                                       const Extrema_ExtAlgo anExtAlgo = Extrema_ExtAlgo_Grad);

