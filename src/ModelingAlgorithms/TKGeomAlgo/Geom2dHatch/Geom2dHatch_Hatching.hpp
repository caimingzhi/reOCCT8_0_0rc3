#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2dAdaptor_Curve.hpp>
#include <Standard_Boolean.hpp>
#include <HatchGen_PointOnHatching.hpp>
#include <NCollection_Sequence.hpp>
#include <HatchGen_ErrorStatus.hpp>
#include <HatchGen_Domain.hpp>

class gp_Pnt2d;

#ifdef Status
  #undef Status
#endif

class Geom2dHatch_Hatching
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dHatch_Hatching();

  Standard_EXPORT Geom2dHatch_Hatching(const Geom2dAdaptor_Curve& Curve);

  Standard_EXPORT const Geom2dAdaptor_Curve& Curve() const;

  Standard_EXPORT Geom2dAdaptor_Curve& ChangeCurve();

  Standard_EXPORT void TrimDone(const bool Flag);

  Standard_EXPORT bool TrimDone() const;

  Standard_EXPORT void TrimFailed(const bool Flag);

  Standard_EXPORT bool TrimFailed() const;

  Standard_EXPORT void IsDone(const bool Flag);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT void Status(const HatchGen_ErrorStatus theStatus);

  Standard_EXPORT HatchGen_ErrorStatus Status() const;

  Standard_EXPORT void AddPoint(const HatchGen_PointOnHatching& Point, const double Confusion);

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT const HatchGen_PointOnHatching& Point(const int Index) const;

  Standard_EXPORT HatchGen_PointOnHatching& ChangePoint(const int Index);

  Standard_EXPORT void RemPoint(const int Index);

  Standard_EXPORT void ClrPoints();

  Standard_EXPORT void AddDomain(const HatchGen_Domain& Domain);

  Standard_EXPORT int NbDomains() const;

  Standard_EXPORT const HatchGen_Domain& Domain(const int Index) const;

  Standard_EXPORT void RemDomain(const int Index);

  Standard_EXPORT void ClrDomains();

  Standard_EXPORT gp_Pnt2d ClassificationPoint() const;

private:
  Geom2dAdaptor_Curve                            myCurve;
  bool                                           myTrimDone;
  bool                                           myTrimFailed;
  NCollection_Sequence<HatchGen_PointOnHatching> myPoints;
  bool                                           myIsDone;
  HatchGen_ErrorStatus                           myStatus;
  NCollection_Sequence<HatchGen_Domain>          myDomains;
};
