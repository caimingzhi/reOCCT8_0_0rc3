#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Vertex.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <Standard_Integer.hpp>
class BRep_Builder;
class Geom_Surface;

class BRepPrim_FaceBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrim_FaceBuilder();

  Standard_EXPORT BRepPrim_FaceBuilder(const BRep_Builder& B, const occ::handle<Geom_Surface>& S);

  Standard_EXPORT BRepPrim_FaceBuilder(const BRep_Builder&              B,
                                       const occ::handle<Geom_Surface>& S,
                                       const double                     UMin,
                                       const double                     UMax,
                                       const double                     VMin,
                                       const double                     VMax);

  Standard_EXPORT void Init(const BRep_Builder& B, const occ::handle<Geom_Surface>& S);

  Standard_EXPORT void Init(const BRep_Builder&              B,
                            const occ::handle<Geom_Surface>& S,
                            const double                     UMin,
                            const double                     UMax,
                            const double                     VMin,
                            const double                     VMax);

  Standard_EXPORT const TopoDS_Face& Face() const;
  Standard_EXPORT                    operator TopoDS_Face();

  Standard_EXPORT const TopoDS_Edge& Edge(const int I) const;

  Standard_EXPORT const TopoDS_Vertex& Vertex(const int I) const;

private:
  TopoDS_Vertex myVertex[4];
  TopoDS_Edge   myEdges[4];
  TopoDS_Face   myFace;
};
