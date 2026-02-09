#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <HatchGen_PointOnHatching.hpp>

class HatchGen_Domain
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HatchGen_Domain();

  Standard_EXPORT HatchGen_Domain(const HatchGen_PointOnHatching& P1,
                                  const HatchGen_PointOnHatching& P2);

  Standard_EXPORT HatchGen_Domain(const HatchGen_PointOnHatching& P, const bool First);

  void SetPoints(const HatchGen_PointOnHatching& P1, const HatchGen_PointOnHatching& P2);

  void SetPoints();

  void SetFirstPoint(const HatchGen_PointOnHatching& P);

  void SetFirstPoint();

  void SetSecondPoint(const HatchGen_PointOnHatching& P);

  void SetSecondPoint();

  bool HasFirstPoint() const;

  const HatchGen_PointOnHatching& FirstPoint() const;

  bool HasSecondPoint() const;

  const HatchGen_PointOnHatching& SecondPoint() const;

  Standard_EXPORT void Dump(const int Index = 0) const;

private:
  bool                     myHasFirstPoint;
  HatchGen_PointOnHatching myFirstPoint;
  bool                     myHasSecondPoint;
  HatchGen_PointOnHatching mySecondPoint;
};

#include <Standard_DomainError.hpp>

inline void HatchGen_Domain::SetPoints(const HatchGen_PointOnHatching& P1,
                                       const HatchGen_PointOnHatching& P2)
{
  myHasFirstPoint  = true;
  myFirstPoint     = P1;
  myHasSecondPoint = true;
  mySecondPoint    = P2;
}

inline void HatchGen_Domain::SetPoints()
{
  myHasFirstPoint  = false;
  myHasSecondPoint = false;
}

inline void HatchGen_Domain::SetFirstPoint(const HatchGen_PointOnHatching& P)
{
  myHasFirstPoint = true;
  myFirstPoint    = P;
}

inline void HatchGen_Domain::SetFirstPoint()
{
  myHasFirstPoint = false;
}

inline void HatchGen_Domain::SetSecondPoint(const HatchGen_PointOnHatching& P)
{
  myHasSecondPoint = true;
  mySecondPoint    = P;
}

inline void HatchGen_Domain::SetSecondPoint()
{
  myHasSecondPoint = false;
}

inline bool HatchGen_Domain::HasFirstPoint() const
{
  return myHasFirstPoint;
}

inline const HatchGen_PointOnHatching& HatchGen_Domain::FirstPoint() const
{
  Standard_DomainError_Raise_if(!myHasFirstPoint, "HatchGen_Domain::FirstPoint");
  return myFirstPoint;
}

inline bool HatchGen_Domain::HasSecondPoint() const
{
  return myHasSecondPoint;
}

inline const HatchGen_PointOnHatching& HatchGen_Domain::SecondPoint() const
{
  Standard_DomainError_Raise_if(!myHasSecondPoint, "HatchGen_Domain::SecondPoint");
  return mySecondPoint;
}
