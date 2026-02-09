#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom2d_Curve.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
class gp_Pnt2d;

class Bisector_Curve : public Geom2d_Curve
{

public:
  Standard_EXPORT virtual double Parameter(const gp_Pnt2d& P) const = 0;

  Standard_EXPORT virtual bool IsExtendAtStart() const = 0;

  Standard_EXPORT virtual bool IsExtendAtEnd() const = 0;

  Standard_EXPORT virtual int NbIntervals() const = 0;

  Standard_EXPORT virtual double IntervalFirst(const int Index) const = 0;

  Standard_EXPORT virtual double IntervalLast(const int Index) const = 0;

  DEFINE_STANDARD_RTTIEXT(Bisector_Curve, Geom2d_Curve)
};
