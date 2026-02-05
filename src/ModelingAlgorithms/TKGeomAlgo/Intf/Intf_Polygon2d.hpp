#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Bnd_Box2d.hpp>
#include <Standard_Boolean.hpp>
class gp_Pnt2d;

//! Describes the necessary polygon information to compute
//! the interferences.
class Intf_Polygon2d
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns the bounding box of the polygon.
  const Bnd_Box2d& Bounding() const;

  //! Returns True if the polyline is closed.
  Standard_EXPORT virtual bool Closed() const;

  virtual ~Intf_Polygon2d() = default;

  //! Returns the tolerance of the polygon.
  Standard_EXPORT virtual double DeflectionOverEstimation() const = 0;

  //! Returns the number of Segments in the polyline.
  Standard_EXPORT virtual int NbSegments() const = 0;

  //! Returns the points of the segment <Index> in the Polygon.
  Standard_EXPORT virtual void Segment(const int theIndex,
                                       gp_Pnt2d& theBegin,
                                       gp_Pnt2d& theEnd) const = 0;

protected:
  Bnd_Box2d myBox;
};

inline const Bnd_Box2d& Intf_Polygon2d::Bounding() const
{
  return myBox;
}
