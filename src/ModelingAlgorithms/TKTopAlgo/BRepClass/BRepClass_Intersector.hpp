#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Geom2dInt_IntConicCurveOfGInter.hpp>
class gp_Lin2d;
class BRepClass_Edge;
class gp_Dir2d;

//! Intersect an Edge with a segment.
//! Implement the Intersector2d required by the classifier.
class BRepClass_Intersector : public Geom2dInt_IntConicCurveOfGInter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepClass_Intersector();

  //! Intersect the line segment and the edge.
  Standard_EXPORT void Perform(const gp_Lin2d&       L,
                               const double          P,
                               const double          Tol,
                               const BRepClass_Edge& E);

  //! Returns in <T>, <N> and <C> the tangent, normal
  //! and curvature of the edge <E> at parameter value
  //! <U>.
  Standard_EXPORT void LocalGeometry(const BRepClass_Edge& E,
                                     const double          U,
                                     gp_Dir2d&             T,
                                     gp_Dir2d&             N,
                                     double&               C) const;
};
