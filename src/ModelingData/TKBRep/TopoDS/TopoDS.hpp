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

//! Provides methods to cast objects of class TopoDS_Shape to more specialized
//! sub-classes. The types are not verified before casting. If the type does
//! not match, a Standard_TypeMismatch exception is thrown. Below are examples
//! of correct and incorrect casts:
//!
//! Correct:
//! @code
//! TopoDS_Shape aShape = ...; // aShape->ShapeType() == TopAbs_VERTEX
//! const TopoDS_Vertex& aVertex = TopoDS::Vertex(aShape);
//! @endcode
//!
//! Incorrect (will throw a Standard_TypeMismatch exception):
//! @code
//! TopoDS_Shape aShape = ...; // aShape->ShapeType() == TopAbs_VERTEX
//! const TopoDS_Face& face = TopoDS::Edge(aShape);
//! @endcode
namespace TopoDS
{
  //! Casts shape theShape to the more specialized return type, Vertex.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_Vertex
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline const TopoDS_Vertex& Vertex(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false
                                                     : theShape.ShapeType() != TopAbs_VERTEX,
                                   "TopoDS::Vertex");
    return *(TopoDS_Vertex*)&theShape;
  }

  //! Casts shape theShape to the more specialized return type, Vertex.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_Vertex
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline TopoDS_Vertex& Vertex(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false
                                                     : theShape.ShapeType() != TopAbs_VERTEX,
                                   "TopoDS::Vertex");
    return *(TopoDS_Vertex*)&theShape;
  }

  //! Casts shape theShape to the more specialized return type, Edge.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_Edge
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline const TopoDS_Edge& Edge(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_EDGE,
                                   "TopoDS::Edge");
    return *(TopoDS_Edge*)&theShape;
  }

  //! Casts shape theShape to the more specialized return type, Edge.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_Edge
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline TopoDS_Edge& Edge(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_EDGE,
                                   "TopoDS::Edge");
    return *(TopoDS_Edge*)&theShape;
  }

  //! Casts shape theShape to the more specialized return type, Wire.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_Wire
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline const TopoDS_Wire& Wire(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_WIRE,
                                   "TopoDS::Wire");
    return *(TopoDS_Wire*)&theShape;
  }

  //! Casts shape theShape to the more specialized return type, Wire.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_Wire
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline TopoDS_Wire& Wire(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_WIRE,
                                   "TopoDS::Wire");
    return *(TopoDS_Wire*)&theShape;
  }

  //! Casts shape theShape to the more specialized return type, Face.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_Face
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline const TopoDS_Face& Face(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_FACE,
                                   "TopoDS::Face");
    return *(TopoDS_Face*)&theShape;
  }

  //! Casts shape theShape to the more specialized return type, Face.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_Face
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline TopoDS_Face& Face(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_FACE,
                                   "TopoDS::Face");
    return *(TopoDS_Face*)&theShape;
  }

  //! Casts shape theShape to the more specialized return type, Shell.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_Shell
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline const TopoDS_Shell& Shell(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_SHELL,
                                   "TopoDS::Shell");
    return *(TopoDS_Shell*)&theShape;
  }

  //! Casts shape theShape to the more specialized return type, Shell.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_Shell
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline TopoDS_Shell& Shell(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_SHELL,
                                   "TopoDS::Shell");
    return *(TopoDS_Shell*)&theShape;
  }

  //! Casts shape theShape to the more specialized return type, Solid.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_Solid
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline const TopoDS_Solid& Solid(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_SOLID,
                                   "TopoDS::Solid");
    return *(TopoDS_Solid*)&theShape;
  }

  //! Casts shape theShape to the more specialized return type, Solid.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_Solid
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline TopoDS_Solid& Solid(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false : theShape.ShapeType() != TopAbs_SOLID,
                                   "TopoDS::Solid");
    return *(TopoDS_Solid*)&theShape;
  }

  //! Casts shape theShape to the more specialized return type, CompSolid.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_CompSolid
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline const TopoDS_CompSolid& CompSolid(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false
                                                     : theShape.ShapeType() != TopAbs_COMPSOLID,
                                   "TopoDS::CompSolid");
    return *(TopoDS_CompSolid*)&theShape;
  }

  //! Casts shape theShape to the more specialized return type, CompSolid.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_CompSolid
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline TopoDS_CompSolid& CompSolid(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false
                                                     : theShape.ShapeType() != TopAbs_COMPSOLID,
                                   "TopoDS::CompSolid");
    return *(TopoDS_CompSolid*)&theShape;
  }

  //! Casts shape theShape to the more specialized return type, Compound.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_Compound
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline const TopoDS_Compound& Compound(const TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false
                                                     : theShape.ShapeType() != TopAbs_COMPOUND,
                                   "TopoDS::Compound");
    return *(TopoDS_Compound*)&theShape;
  }

  //! Casts shape theShape to the more specialized return type, Compound.
  //! @param theShape the shape to be cast
  //! @return the casted shape as TopoDS_Compound
  //! @throws Standard_TypeMismatch if theShape cannot be cast to this return type.
  inline TopoDS_Compound& Compound(TopoDS_Shape& theShape)
  {
    Standard_TypeMismatch_Raise_if(theShape.IsNull() ? false
                                                     : theShape.ShapeType() != TopAbs_COMPOUND,
                                   "TopoDS::Compound");
    return *(TopoDS_Compound*)&theShape;
  }
} // namespace TopoDS
