#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
class gp_Pnt;
class gp_XYZ;

//! Interference computation between polygons, lines and
//! polyhedra with only triangular facets. These objects
//! are polygonal representations of complex curves and
//! triangulated representations of complex surfaces.
class Intf
{
public:
  DEFINE_STANDARD_ALLOC

  //! Computes the interference between two polygons in 2d.
  //! Result : points of intersections and zones of tangence.
  //! Computes the interference between a polygon or a straight
  //! line and a polyhedron. Points of intersection and zones
  //! of tangence.
  //! Give the plane equation of the triangle <P1> <P2> <P3>.
  Standard_EXPORT static void PlaneEquation(const gp_Pnt& P1,
                                            const gp_Pnt& P2,
                                            const gp_Pnt& P3,
                                            gp_XYZ&       NormalVector,
                                            double&       PolarDistance);

  //! Compute if the triangle <P1> <P2> <P3> contain <ThePnt>.
  Standard_EXPORT static bool Contain(const gp_Pnt& P1,
                                      const gp_Pnt& P2,
                                      const gp_Pnt& P3,
                                      const gp_Pnt& ThePnt);
};

