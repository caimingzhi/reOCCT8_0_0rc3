#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRep_Builder.hpp>
class TopoDS_Shell;
class TopoDS_Face;
class gp_Pln;
class TopoDS_Wire;
class TopoDS_Edge;
class gp_Lin;
class gp_Circ;
class gp_Lin2d;
class gp_Circ2d;
class TopoDS_Vertex;
class gp_Pnt;

class BRepPrim_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrim_Builder();

  Standard_EXPORT BRepPrim_Builder(const BRep_Builder& B);

  const BRep_Builder& Builder() const;

  Standard_EXPORT void MakeShell(TopoDS_Shell& S) const;

  Standard_EXPORT void MakeFace(TopoDS_Face& F, const gp_Pln& P) const;

  Standard_EXPORT void MakeWire(TopoDS_Wire& W) const;

  Standard_EXPORT void MakeDegeneratedEdge(TopoDS_Edge& E) const;

  Standard_EXPORT void MakeEdge(TopoDS_Edge& E, const gp_Lin& L) const;

  Standard_EXPORT void MakeEdge(TopoDS_Edge& E, const gp_Circ& C) const;

  Standard_EXPORT void SetPCurve(TopoDS_Edge& E, const TopoDS_Face& F, const gp_Lin2d& L) const;

  Standard_EXPORT void SetPCurve(TopoDS_Edge&       E,
                                 const TopoDS_Face& F,
                                 const gp_Lin2d&    L1,
                                 const gp_Lin2d&    L2) const;

  Standard_EXPORT void SetPCurve(TopoDS_Edge& E, const TopoDS_Face& F, const gp_Circ2d& C) const;

  Standard_EXPORT void MakeVertex(TopoDS_Vertex& V, const gp_Pnt& P) const;

  Standard_EXPORT void ReverseFace(TopoDS_Face& F) const;

  Standard_EXPORT void AddEdgeVertex(TopoDS_Edge&         E,
                                     const TopoDS_Vertex& V,
                                     const double         P,
                                     const bool           direct) const;

  Standard_EXPORT void AddEdgeVertex(TopoDS_Edge&         E,
                                     const TopoDS_Vertex& V,
                                     const double         P1,
                                     const double         P2) const;

  Standard_EXPORT void SetParameters(TopoDS_Edge&         E,
                                     const TopoDS_Vertex& V,
                                     const double         P1,
                                     const double         P2) const;

  Standard_EXPORT void AddWireEdge(TopoDS_Wire& W, const TopoDS_Edge& E, const bool direct) const;

  Standard_EXPORT void AddFaceWire(TopoDS_Face& F, const TopoDS_Wire& W) const;

  Standard_EXPORT void AddShellFace(TopoDS_Shell& Sh, const TopoDS_Face& F) const;

  Standard_EXPORT void CompleteEdge(TopoDS_Edge& E) const;

  Standard_EXPORT void CompleteWire(TopoDS_Wire& W) const;

  Standard_EXPORT void CompleteFace(TopoDS_Face& F) const;

  Standard_EXPORT void CompleteShell(TopoDS_Shell& S) const;

private:
  BRep_Builder myBuilder;
};

inline const BRep_Builder& BRepPrim_Builder::Builder() const
{
  return myBuilder;
}
