#pragma once

#include <IntPolyh_Array.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

struct IntPolyh_PointNormal
{
  gp_Pnt Point;
  gp_Vec Normal;
};

typedef IntPolyh_Array<IntPolyh_PointNormal> IntPolyh_ArrayOfPointNormal;
