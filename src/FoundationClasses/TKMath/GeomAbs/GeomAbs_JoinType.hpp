#pragma once

//! Characterizes the type of a join, built by an algorithm for
//! constructing parallel curves, between two consecutive
//! arcs of a contour parallel to a given contour.
enum GeomAbs_JoinType
{
  GeomAbs_Arc,
  GeomAbs_Tangent,
  GeomAbs_Intersection
};
