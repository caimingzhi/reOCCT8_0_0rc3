#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Intf_Interference.hpp>
class Intf_Polygon2d;
class gp_Pnt2d;

//! Computes the interference between two polygons or
//! the self intersection of a polygon in two
//! dimensions.
class Intf_InterferencePolygon2d : public Intf_Interference
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs an empty interference of Polygon.
  Standard_EXPORT Intf_InterferencePolygon2d();

  //! Constructs and computes an interference between two Polygons.
  Standard_EXPORT Intf_InterferencePolygon2d(const Intf_Polygon2d& Obje1,
                                             const Intf_Polygon2d& Obje2);

  //! Constructs and computes the auto interference of a Polygon.
  Standard_EXPORT Intf_InterferencePolygon2d(const Intf_Polygon2d& Obje);

  //! Computes an interference between two Polygons.
  Standard_EXPORT void Perform(const Intf_Polygon2d& Obje1, const Intf_Polygon2d& Obje2);

  //! Computes the self interference of a Polygon.
  Standard_EXPORT void Perform(const Intf_Polygon2d& Obje);

  //! Gives the geometrical 2d point of the intersection
  //! point at address <Index> in the interference.
  Standard_EXPORT gp_Pnt2d Pnt2dValue(const int Index) const;

private:
  Standard_EXPORT void Interference(const Intf_Polygon2d& Obje1, const Intf_Polygon2d& Obje2);

  Standard_EXPORT void Interference(const Intf_Polygon2d& Obje);

  Standard_EXPORT void Clean();

  //! Computes the intersection between two segments
  //! <BegO><EndO> et <BegT><EndT>.
  Standard_EXPORT void Intersect(const int       iO,
                                 const int       iT,
                                 const gp_Pnt2d& BegO,
                                 const gp_Pnt2d& EndO,
                                 const gp_Pnt2d& BegT,
                                 const gp_Pnt2d& EndT);

  bool oClos;
  bool tClos;
  int  nbso;
};
