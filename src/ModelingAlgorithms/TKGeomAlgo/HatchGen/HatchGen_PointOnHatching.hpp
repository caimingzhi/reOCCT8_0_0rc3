#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HatchGen_PointOnElement.hpp>
#include <NCollection_Sequence.hpp>
#include <HatchGen_IntersectionPoint.hpp>
#include <Standard_Boolean.hpp>
class IntRes2d_IntersectionPoint;
class HatchGen_PointOnElement;

class HatchGen_PointOnHatching : public HatchGen_IntersectionPoint
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an empty point.
  Standard_EXPORT HatchGen_PointOnHatching();

  //! Creates a point from an intersection point.
  Standard_EXPORT HatchGen_PointOnHatching(const IntRes2d_IntersectionPoint& Point);

  //! Adds a point on element to the point.
  Standard_EXPORT void AddPoint(const HatchGen_PointOnElement& Point, const double Confusion);

  //! Returns the number of elements intersecting the
  //! hatching at this point.
  Standard_EXPORT int NbPoints() const;

  //! Returns the Index-th point on element of the point.
  //! The exception OutOfRange is raised if
  //! Index > NbPoints.
  Standard_EXPORT const HatchGen_PointOnElement& Point(const int Index) const;

  //! Removes the Index-th point on element of the point.
  //! The exception OutOfRange is raised if
  //! Index > NbPoints.
  Standard_EXPORT void RemPoint(const int Index);

  //! Removes all the points on element of the point.
  Standard_EXPORT void ClrPoints();

  //! Tests if the point is lower than an other.
  //! A point on hatching P1 is said to be lower than an
  //! other P2 if :
  //! P2.myParam - P1.myParam > Confusion
  Standard_EXPORT bool IsLower(const HatchGen_PointOnHatching& Point, const double Confusion) const;

  //! Tests if the point is equal to an other.
  //! A point on hatching P1 is said to be equal to an
  //! other P2 if :
  //! | P2.myParam - P1.myParam | <= Confusion
  Standard_EXPORT bool IsEqual(const HatchGen_PointOnHatching& Point, const double Confusion) const;

  //! Tests if the point is greater than an other.
  //! A point on hatching P1 is said to be greater than an
  //! other P2 if :
  //! P1.myParam - P2.myParam > Confusion
  Standard_EXPORT bool IsGreater(const HatchGen_PointOnHatching& Point,
                                 const double                    Confusion) const;

  //! Dump of the point.
  Standard_EXPORT void Dump(const int Index = 0) const override;

protected:
  NCollection_Sequence<HatchGen_PointOnElement> myPoints;
};
