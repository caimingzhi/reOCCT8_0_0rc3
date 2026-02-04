#pragma once


#include <IntPolyh_Array.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

//! Auxiliary structure to represent pair of point and
//! normal vector in this point on the surface.
struct IntPolyh_PointNormal
{
  gp_Pnt Point;
  gp_Vec Normal;
};

typedef IntPolyh_Array<IntPolyh_PointNormal> IntPolyh_ArrayOfPointNormal;

