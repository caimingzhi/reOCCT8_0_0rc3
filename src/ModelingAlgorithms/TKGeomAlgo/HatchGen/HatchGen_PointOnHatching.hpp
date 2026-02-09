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

  Standard_EXPORT HatchGen_PointOnHatching();

  Standard_EXPORT HatchGen_PointOnHatching(const IntRes2d_IntersectionPoint& Point);

  Standard_EXPORT void AddPoint(const HatchGen_PointOnElement& Point, const double Confusion);

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT const HatchGen_PointOnElement& Point(const int Index) const;

  Standard_EXPORT void RemPoint(const int Index);

  Standard_EXPORT void ClrPoints();

  Standard_EXPORT bool IsLower(const HatchGen_PointOnHatching& Point, const double Confusion) const;

  Standard_EXPORT bool IsEqual(const HatchGen_PointOnHatching& Point, const double Confusion) const;

  Standard_EXPORT bool IsGreater(const HatchGen_PointOnHatching& Point,
                                 const double                    Confusion) const;

  Standard_EXPORT void Dump(const int Index = 0) const override;

protected:
  NCollection_Sequence<HatchGen_PointOnElement> myPoints;
};
