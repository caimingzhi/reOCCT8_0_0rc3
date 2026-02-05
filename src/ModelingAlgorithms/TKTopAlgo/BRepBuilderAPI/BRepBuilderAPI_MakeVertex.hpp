#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepLib_MakeVertex.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
class gp_Pnt;
class TopoDS_Vertex;

//! Describes functions to build BRepBuilder vertices directly
//! from 3D geometric points. A vertex built using a
//! MakeVertex object is only composed of a 3D point and
//! a default precision value (Precision::Confusion()).
//! Later on, 2D representations can be added, for example,
//! when inserting a vertex in an edge.
//! A MakeVertex object provides a framework for:
//! -   defining and implementing the construction of a vertex, and
//! -   consulting the result.
class BRepBuilderAPI_MakeVertex : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a vertex from point P.
  //! Example create a vertex from a 3D point.
  //! gp_Pnt P(0,0,10);
  //! TopoDS_Vertex V = BRepBuilderAPI_MakeVertex(P);
  Standard_EXPORT BRepBuilderAPI_MakeVertex(const gp_Pnt& P);

  //! Returns the constructed vertex.
  Standard_EXPORT const TopoDS_Vertex& Vertex();
  Standard_EXPORT                      operator TopoDS_Vertex();

private:
  BRepLib_MakeVertex myMakeVertex;
};
