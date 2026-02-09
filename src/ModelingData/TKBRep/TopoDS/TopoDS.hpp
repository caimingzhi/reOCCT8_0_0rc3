#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_TypeMismatch.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_Shape.hpp>

class TopoDS_Vertex;
class TopoDS_Shape;
class TopoDS_Edge;
class TopoDS_Wire;
class TopoDS_Face;
class TopoDS_Shell;
class TopoDS_Solid;
class TopoDS_CompSolid;
class TopoDS_Compound;
class TopoDS_HShape;
class TopoDS_TShape;
class TopoDS_TVertex;
class TopoDS_TEdge;
class TopoDS_TWire;
class TopoDS_TFace;
class TopoDS_TShell;
class TopoDS_TSolid;
class TopoDS_TCompSolid;
class TopoDS_TCompound;
class TopoDS_Builder;
class TopoDS_Iterator;

namespace TopoDS
{

  inline const TopoDS_Vertex& Vertex(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false
                                                     : theShape.ShapeType() != TopAbs_VERTEX,
                                   "TopoDS::Vertex");
    return *(TopoDS_Vertex*)&theShape;
  }

  inline TopoDS_Vertex& Vertex(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false
                                                     : theShape.ShapeType() != TopAbs_VERTEX,
                                   "TopoDS::Vertex");
    return *(TopoDS_Vertex*)&theShape;
  }

  inline const TopoDS_Edge& Edge(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_EDGE,
                                   "TopoDS::Edge");
    return *(TopoDS_Edge*)&theShape;
  }

  inline TopoDS_Edge& Edge(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_EDGE,
                                   "TopoDS::Edge");
    return *(TopoDS_Edge*)&theShape;
  }

  inline const TopoDS_Wire& Wire(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_WIRE,
                                   "TopoDS::Wire");
    return *(TopoDS_Wire*)&theShape;
  }

  inline TopoDS_Wire& Wire(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_WIRE,
                                   "TopoDS::Wire");
    return *(TopoDS_Wire*)&theShape;
  }

  inline const TopoDS_Face& Face(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_FACE,
                                   "TopoDS::Face");
    return *(TopoDS_Face*)&theShape;
  }

  inline TopoDS_Face& Face(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_FACE,
                                   "TopoDS::Face");
    return *(TopoDS_Face*)&theShape;
  }

  inline const TopoDS_Shell& Shell(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_SHELL,
                                   "TopoDS::Shell");
    return *(TopoDS_Shell*)&theShape;
  }

  inline TopoDS_Shell& Shell(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_SHELL,
                                   "TopoDS::Shell");
    return *(TopoDS_Shell*)&theShape;
  }

  inline const TopoDS_Solid& Solid(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_SOLID,
                                   "TopoDS::Solid");
    return *(TopoDS_Solid*)&theShape;
  }

  inline TopoDS_Solid& Solid(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_SOLID,
                                   "TopoDS::Solid");
    return *(TopoDS_Solid*)&theShape;
  }

  inline const TopoDS_CompSolid& CompSolid(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false
                                                     : theShape.ShapeType() != TopAbs_COMPSOLID,
                                   "TopoDS::CompSolid");
    return *(TopoDS_CompSolid*)&theShape;
  }

  inline TopoDS_CompSolid& CompSolid(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false
                                                     : theShape.ShapeType() != TopAbs_COMPSOLID,
                                   "TopoDS::CompSolid");
    return *(TopoDS_CompSolid*)&theShape;
  }

  inline const TopoDS_Compound& Compound(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false
                                                     : theShape.ShapeType() != TopAbs_COMPOUND,
                                   "TopoDS::Compound");
    return *(TopoDS_Compound*)&theShape;
  }

  inline TopoDS_Compound& Compound(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false
                                                     : theShape.ShapeType() != TopAbs_COMPOUND,
                                   "TopoDS::Compound");
    return *(TopoDS_Compound*)&theShape;
  }
} // namespace TopoDS
