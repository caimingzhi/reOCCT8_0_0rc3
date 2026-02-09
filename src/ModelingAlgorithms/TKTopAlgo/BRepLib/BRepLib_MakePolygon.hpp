#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Vertex.hpp>
#include <TopoDS_Edge.hpp>
#include <BRepLib_MakeShape.hpp>
class gp_Pnt;
class TopoDS_Wire;

class BRepLib_MakePolygon : public BRepLib_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepLib_MakePolygon();

  Standard_EXPORT BRepLib_MakePolygon(const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT BRepLib_MakePolygon(const gp_Pnt& P1,
                                      const gp_Pnt& P2,
                                      const gp_Pnt& P3,
                                      const bool    Close = false);

  Standard_EXPORT BRepLib_MakePolygon(const gp_Pnt& P1,
                                      const gp_Pnt& P2,
                                      const gp_Pnt& P3,
                                      const gp_Pnt& P4,
                                      const bool    Close = false);

  Standard_EXPORT BRepLib_MakePolygon(const TopoDS_Vertex& V1, const TopoDS_Vertex& V2);

  Standard_EXPORT BRepLib_MakePolygon(const TopoDS_Vertex& V1,
                                      const TopoDS_Vertex& V2,
                                      const TopoDS_Vertex& V3,
                                      const bool           Close = false);

  Standard_EXPORT BRepLib_MakePolygon(const TopoDS_Vertex& V1,
                                      const TopoDS_Vertex& V2,
                                      const TopoDS_Vertex& V3,
                                      const TopoDS_Vertex& V4,
                                      const bool           Close = false);

  Standard_EXPORT void Add(const gp_Pnt& P);

  Standard_EXPORT void Add(const TopoDS_Vertex& V);

  Standard_EXPORT bool Added() const;

  Standard_EXPORT void Close();

  Standard_EXPORT const TopoDS_Vertex& FirstVertex() const;

  Standard_EXPORT const TopoDS_Vertex& LastVertex() const;

  Standard_EXPORT const TopoDS_Edge& Edge() const;
  Standard_EXPORT                    operator TopoDS_Edge() const;

  Standard_EXPORT const TopoDS_Wire& Wire();
  Standard_EXPORT                    operator TopoDS_Wire();

private:
  TopoDS_Vertex myFirstVertex;
  TopoDS_Vertex myLastVertex;
  TopoDS_Edge   myEdge;
};
