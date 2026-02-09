#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepLib_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <Standard_Real.hpp>
#include <BRepBuilderAPI_EdgeError.hpp>
class TopoDS_Vertex;
class gp_Pnt;
class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Hypr;
class gp_Parab;
class Geom_Curve;
class Geom2d_Curve;
class Geom_Surface;
class TopoDS_Edge;

class BRepBuilderAPI_MakeEdge : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBuilderAPI_MakeEdge();

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const TopoDS_Vertex& V1, const TopoDS_Vertex& V2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Lin& L);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Lin& L, const double p1, const double p2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Lin& L, const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Lin&        L,
                                          const TopoDS_Vertex& V1,
                                          const TopoDS_Vertex& V2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Circ& L);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Circ& L, const double p1, const double p2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Circ& L, const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Circ&       L,
                                          const TopoDS_Vertex& V1,
                                          const TopoDS_Vertex& V2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Elips& L);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Elips& L, const double p1, const double p2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Elips& L, const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Elips&      L,
                                          const TopoDS_Vertex& V1,
                                          const TopoDS_Vertex& V2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Hypr& L);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Hypr& L, const double p1, const double p2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Hypr& L, const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Hypr&       L,
                                          const TopoDS_Vertex& V1,
                                          const TopoDS_Vertex& V2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Parab& L);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Parab& L, const double p1, const double p2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Parab& L, const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const gp_Parab&      L,
                                          const TopoDS_Vertex& V1,
                                          const TopoDS_Vertex& V2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const occ::handle<Geom_Curve>& L);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const occ::handle<Geom_Curve>& L,
                                          const double                   p1,
                                          const double                   p2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const occ::handle<Geom_Curve>& L,
                                          const gp_Pnt&                  P1,
                                          const gp_Pnt&                  P2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const occ::handle<Geom_Curve>& L,
                                          const TopoDS_Vertex&           V1,
                                          const TopoDS_Vertex&           V2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const occ::handle<Geom_Curve>& L,
                                          const gp_Pnt&                  P1,
                                          const gp_Pnt&                  P2,
                                          const double                   p1,
                                          const double                   p2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const occ::handle<Geom_Curve>& L,
                                          const TopoDS_Vertex&           V1,
                                          const TopoDS_Vertex&           V2,
                                          const double                   p1,
                                          const double                   p2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const occ::handle<Geom2d_Curve>& L,
                                          const occ::handle<Geom_Surface>& S);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const occ::handle<Geom2d_Curve>& L,
                                          const occ::handle<Geom_Surface>& S,
                                          const double                     p1,
                                          const double                     p2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const occ::handle<Geom2d_Curve>& L,
                                          const occ::handle<Geom_Surface>& S,
                                          const gp_Pnt&                    P1,
                                          const gp_Pnt&                    P2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const occ::handle<Geom2d_Curve>& L,
                                          const occ::handle<Geom_Surface>& S,
                                          const TopoDS_Vertex&             V1,
                                          const TopoDS_Vertex&             V2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const occ::handle<Geom2d_Curve>& L,
                                          const occ::handle<Geom_Surface>& S,
                                          const gp_Pnt&                    P1,
                                          const gp_Pnt&                    P2,
                                          const double                     p1,
                                          const double                     p2);

  Standard_EXPORT BRepBuilderAPI_MakeEdge(const occ::handle<Geom2d_Curve>& L,
                                          const occ::handle<Geom_Surface>& S,
                                          const TopoDS_Vertex&             V1,
                                          const TopoDS_Vertex&             V2,
                                          const double                     p1,
                                          const double                     p2);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& C);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& C, const double p1, const double p2);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& C, const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& C,
                            const TopoDS_Vertex&           V1,
                            const TopoDS_Vertex&           V2);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& C,
                            const gp_Pnt&                  P1,
                            const gp_Pnt&                  P2,
                            const double                   p1,
                            const double                   p2);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& C,
                            const TopoDS_Vertex&           V1,
                            const TopoDS_Vertex&           V2,
                            const double                   p1,
                            const double                   p2);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C, const occ::handle<Geom_Surface>& S);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C,
                            const occ::handle<Geom_Surface>& S,
                            const double                     p1,
                            const double                     p2);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C,
                            const occ::handle<Geom_Surface>& S,
                            const gp_Pnt&                    P1,
                            const gp_Pnt&                    P2);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C,
                            const occ::handle<Geom_Surface>& S,
                            const TopoDS_Vertex&             V1,
                            const TopoDS_Vertex&             V2);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C,
                            const occ::handle<Geom_Surface>& S,
                            const gp_Pnt&                    P1,
                            const gp_Pnt&                    P2,
                            const double                     p1,
                            const double                     p2);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C,
                            const occ::handle<Geom_Surface>& S,
                            const TopoDS_Vertex&             V1,
                            const TopoDS_Vertex&             V2,
                            const double                     p1,
                            const double                     p2);

  Standard_EXPORT bool IsDone() const override;

  Standard_EXPORT BRepBuilderAPI_EdgeError Error() const;

  Standard_EXPORT const TopoDS_Edge& Edge();
  Standard_EXPORT                    operator TopoDS_Edge();

  Standard_EXPORT const TopoDS_Vertex& Vertex1() const;

  Standard_EXPORT const TopoDS_Vertex& Vertex2() const;

private:
  BRepLib_MakeEdge myMakeEdge;
};
