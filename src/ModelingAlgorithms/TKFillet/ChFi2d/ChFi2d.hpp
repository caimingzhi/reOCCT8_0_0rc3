#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <ChFi2d_ConstructionError.hpp>
class TopoDS_Edge;
class TopoDS_Vertex;
class TopoDS_Face;

//! This package contains the algorithms used to build
//! fillets or chamfers on planar wire.
//!
//! This package provides two algorithms for 2D fillets:
//! ChFi2d_Builder - it constructs a fillet or chamfer
//! for linear and circular edges of a face.
//! ChFi2d_FilletAPI - it encapsulates two algorithms:
//! ChFi2d_AnaFilletAlgo - analytical constructor of the fillet.
//! It works only for linear and circular edges,
//! having a common point.
//! ChFi2d_FilletAlgo - iteration recursive method constructing
//! the fillet edge for any type of edges including
//! ellipses and b-splines.
//! The edges may even have no common point.
//! ChFi2d_ChamferAPI - an algorithm for construction of chamfers
//! between two linear edges of a plane.
//!
//! The algorithms ChFi2d_AnaFilletAlgo and ChFi2d_FilletAlgo may be used directly
//! or via the interface class ChFi2d_FilletAPI.
class ChFi2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool CommonVertex(const TopoDS_Edge& E1,
                                           const TopoDS_Edge& E2,
                                           TopoDS_Vertex&     V);

  Standard_EXPORT static ChFi2d_ConstructionError FindConnectedEdges(const TopoDS_Face&   F,
                                                                     const TopoDS_Vertex& V,
                                                                     TopoDS_Edge&         E1,
                                                                     TopoDS_Edge&         E2);
};

