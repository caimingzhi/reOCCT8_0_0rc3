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

// resolve name collisions with X11 headers
#ifdef Status
  #undef Status
#endif

class Geom2dHatch_Hatching
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dHatch_Hatching();

  //! Creates a hatching.
  Standard_EXPORT Geom2dHatch_Hatching(const Geom2dAdaptor_Curve& Curve);

  //! Returns the curve associated to the hatching.
  Standard_EXPORT const Geom2dAdaptor_Curve& Curve() const;

  //! Returns the curve associated to the hatching.
  Standard_EXPORT Geom2dAdaptor_Curve& ChangeCurve();

  //! Sets the flag about the trimming computations to the
  //! given value.
  Standard_EXPORT void TrimDone(const bool Flag);

  //! Returns the flag about the trimming computations.
  Standard_EXPORT bool TrimDone() const;

  //! Sets the flag about the trimming failure to the
  //! given value.
  Standard_EXPORT void TrimFailed(const bool Flag);

  //! Returns the flag about the trimming failure.
  Standard_EXPORT bool TrimFailed() const;

  //! Sets the flag about the domains computation to the
  //! given value.
  Standard_EXPORT void IsDone(const bool Flag);

  //! Returns the flag about the domains computation.
  Standard_EXPORT bool IsDone() const;

  //! Sets the error status.
  Standard_EXPORT void Status(const HatchGen_ErrorStatus theStatus);

  //! Returns the error status.
  Standard_EXPORT HatchGen_ErrorStatus Status() const;

  //! Adds an intersection point to the hatching.
  Standard_EXPORT void AddPoint(const HatchGen_PointOnHatching& Point, const double Confusion);

  //! Returns the number of intersection points
  //! of the hatching.
  Standard_EXPORT int NbPoints() const;

  //! Returns the Index-th intersection point of the
  //! hatching.
  //! The exception OutOfRange is raised if
  //! Index < 1 or Index > NbPoints.
  Standard_EXPORT const HatchGen_PointOnHatching& Point(const int Index) const;

  //! Returns the Index-th intersection point of the
  //! hatching.
  //! The exception OutOfRange is raised if
  //! Index < 1 or Index > NbPoints.
  Standard_EXPORT HatchGen_PointOnHatching& ChangePoint(const int Index);

  //! Removes the Index-th intersection point of the
  //! hatching.
  //! The exception OutOfRange is raised if
  //! Index < 1 or Index > NbPoints.
  Standard_EXPORT void RemPoint(const int Index);

  //! Removes all the intersection points of the hatching.
  Standard_EXPORT void ClrPoints();

  //! Adds a domain to the hatching.
  Standard_EXPORT void AddDomain(const HatchGen_Domain& Domain);

  //! Returns the number of domains of the hatching.
  Standard_EXPORT int NbDomains() const;

  //! Returns the Index-th domain of the hatching.
  //! The exception OutOfRange is raised if
  //! Index < 1 or Index > NbDomains.
  Standard_EXPORT const HatchGen_Domain& Domain(const int Index) const;

  //! Removes the Index-th domain of the hatching.
  //! The exception OutOfRange is raised if
  //! Index < 1 or Index > NbDomains.
  Standard_EXPORT void RemDomain(const int Index);

  //! Removes all the domains of the hatching.
  Standard_EXPORT void ClrDomains();

  //! Returns a point on the curve.
  //! This point will be used for the classification.
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
