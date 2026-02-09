#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepLib_EdgeError.hpp>
#include <TopoDS_Vertex.hpp>
#include <BRepLib_MakeShape.hpp>
class gp_Pnt2d;
class gp_Lin2d;
class gp_Circ2d;
class gp_Elips2d;
class gp_Hypr2d;
class gp_Parab2d;
class Geom2d_Curve;
class TopoDS_Edge;

class BRepLib_MakeEdge2d : public BRepLib_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepLib_MakeEdge2d(const TopoDS_Vertex& V1, const TopoDS_Vertex& V2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Lin2d& L);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Lin2d& L, const double p1, const double p2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Lin2d& L, const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Lin2d&      L,
                                     const TopoDS_Vertex& V1,
                                     const TopoDS_Vertex& V2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Circ2d& L);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Circ2d& L, const double p1, const double p2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Circ2d& L, const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Circ2d&     L,
                                     const TopoDS_Vertex& V1,
                                     const TopoDS_Vertex& V2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Elips2d& L);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Elips2d& L, const double p1, const double p2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Elips2d& L, const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Elips2d&    L,
                                     const TopoDS_Vertex& V1,
                                     const TopoDS_Vertex& V2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Hypr2d& L);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Hypr2d& L, const double p1, const double p2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Hypr2d& L, const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Hypr2d&     L,
                                     const TopoDS_Vertex& V1,
                                     const TopoDS_Vertex& V2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Parab2d& L);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Parab2d& L, const double p1, const double p2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Parab2d& L, const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  Standard_EXPORT BRepLib_MakeEdge2d(const gp_Parab2d&    L,
                                     const TopoDS_Vertex& V1,
                                     const TopoDS_Vertex& V2);

  Standard_EXPORT BRepLib_MakeEdge2d(const occ::handle<Geom2d_Curve>& L);

  Standard_EXPORT BRepLib_MakeEdge2d(const occ::handle<Geom2d_Curve>& L,
                                     const double                     p1,
                                     const double                     p2);

  Standard_EXPORT BRepLib_MakeEdge2d(const occ::handle<Geom2d_Curve>& L,
                                     const gp_Pnt2d&                  P1,
                                     const gp_Pnt2d&                  P2);

  Standard_EXPORT BRepLib_MakeEdge2d(const occ::handle<Geom2d_Curve>& L,
                                     const TopoDS_Vertex&             V1,
                                     const TopoDS_Vertex&             V2);

  Standard_EXPORT BRepLib_MakeEdge2d(const occ::handle<Geom2d_Curve>& L,
                                     const gp_Pnt2d&                  P1,
                                     const gp_Pnt2d&                  P2,
                                     const double                     p1,
                                     const double                     p2);

  Standard_EXPORT BRepLib_MakeEdge2d(const occ::handle<Geom2d_Curve>& L,
                                     const TopoDS_Vertex&             V1,
                                     const TopoDS_Vertex&             V2,
                                     const double                     p1,
                                     const double                     p2);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C, const double p1, const double p2);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C,
                            const gp_Pnt2d&                  P1,
                            const gp_Pnt2d&                  P2);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C,
                            const TopoDS_Vertex&             V1,
                            const TopoDS_Vertex&             V2);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C,
                            const gp_Pnt2d&                  P1,
                            const gp_Pnt2d&                  P2,
                            const double                     p1,
                            const double                     p2);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C,
                            const TopoDS_Vertex&             V1,
                            const TopoDS_Vertex&             V2,
                            const double                     p1,
                            const double                     p2);

  Standard_EXPORT BRepLib_EdgeError Error() const;

  Standard_EXPORT const TopoDS_Edge& Edge();
  Standard_EXPORT                    operator TopoDS_Edge();

  Standard_EXPORT const TopoDS_Vertex& Vertex1() const;

  Standard_EXPORT const TopoDS_Vertex& Vertex2() const;

private:
  BRepLib_EdgeError myError;
  TopoDS_Vertex     myVertex1;
  TopoDS_Vertex     myVertex2;
};
