#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IntCurveSurface_IntersectionPoint.hpp>

//! A IntersectionSegment describes a segment of curve
//! (w1,w2) where distance(C(w),Surface) is less than a
//! given tolerances.
class IntCurveSurface_IntersectionSegment
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntCurveSurface_IntersectionSegment();

  Standard_EXPORT IntCurveSurface_IntersectionSegment(const IntCurveSurface_IntersectionPoint& P1,
                                                      const IntCurveSurface_IntersectionPoint& P2);

  Standard_EXPORT void SetValues(const IntCurveSurface_IntersectionPoint& P1,
                                 const IntCurveSurface_IntersectionPoint& P2);

  Standard_EXPORT void Values(IntCurveSurface_IntersectionPoint& P1,
                              IntCurveSurface_IntersectionPoint& P2) const;

  Standard_EXPORT void FirstPoint(IntCurveSurface_IntersectionPoint& P1) const;

  Standard_EXPORT void SecondPoint(IntCurveSurface_IntersectionPoint& P2) const;

  Standard_EXPORT const IntCurveSurface_IntersectionPoint& FirstPoint() const;

  Standard_EXPORT const IntCurveSurface_IntersectionPoint& SecondPoint() const;

  Standard_EXPORT void Dump() const;

private:
  IntCurveSurface_IntersectionPoint myP1;
  IntCurveSurface_IntersectionPoint myP2;
};
