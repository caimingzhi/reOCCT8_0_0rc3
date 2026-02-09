#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

enum HatchGen_IntersectionType
{
  HatchGen_TRUE,
  HatchGen_TOUCH,
  HatchGen_TANGENT,
  HatchGen_UNDETERMINED
};

#include <HatchGen_IntersectionPoint.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
class IntRes2d_IntersectionPoint;

class HatchGen_PointOnElement : public HatchGen_IntersectionPoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HatchGen_PointOnElement();

  Standard_EXPORT HatchGen_PointOnElement(const IntRes2d_IntersectionPoint& Point);

  void SetIntersectionType(const HatchGen_IntersectionType Type);

  HatchGen_IntersectionType IntersectionType() const;

  Standard_EXPORT bool IsIdentical(const HatchGen_PointOnElement& Point,
                                   const double                   Confusion) const;

  Standard_EXPORT bool IsDifferent(const HatchGen_PointOnElement& Point,
                                   const double                   Confusion) const;

  Standard_EXPORT void Dump(const int Index = 0) const override;

protected:
  HatchGen_IntersectionType myType;
};

inline void HatchGen_PointOnElement::SetIntersectionType(const HatchGen_IntersectionType Type)
{
  myType = Type;
}

inline HatchGen_IntersectionType HatchGen_PointOnElement::IntersectionType() const
{
  return myType;
}
