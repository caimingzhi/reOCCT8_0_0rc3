#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Bnd_Box2d.hpp>
#include <Standard_Boolean.hpp>
class gp_Pnt2d;

class Intf_Polygon2d
{
public:
  DEFINE_STANDARD_ALLOC

  const Bnd_Box2d& Bounding() const;

  Standard_EXPORT virtual bool Closed() const;

  virtual ~Intf_Polygon2d() = default;

  Standard_EXPORT virtual double DeflectionOverEstimation() const = 0;

  Standard_EXPORT virtual int NbSegments() const = 0;

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
