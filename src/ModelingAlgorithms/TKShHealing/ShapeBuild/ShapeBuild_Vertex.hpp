#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class TopoDS_Vertex;
class gp_Pnt;

//! Provides low-level functions used for constructing vertices
class ShapeBuild_Vertex
{
public:
  DEFINE_STANDARD_ALLOC

  //! Combines new vertex from two others. This new one is the
  //! smallest vertex which comprises both of the source vertices.
  //! The function takes into account the positions and tolerances
  //! of the source vertices.
  //! The tolerance of the new vertex will be equal to the minimal
  //! tolerance that is required to comprise source vertices
  //! multiplied by tolFactor (in order to avoid errors because
  //! of discreteness of calculations).
  Standard_EXPORT TopoDS_Vertex CombineVertex(const TopoDS_Vertex& V1,
                                              const TopoDS_Vertex& V2,
                                              const double         tolFactor = 1.0001) const;

  //! The same function as above, except that it accepts two points
  //! and two tolerances instead of vertices
  Standard_EXPORT TopoDS_Vertex CombineVertex(const gp_Pnt& pnt1,
                                              const gp_Pnt& pnt2,
                                              const double  tol1,
                                              const double  tol2,
                                              const double  tolFactor = 1.0001) const;
};

