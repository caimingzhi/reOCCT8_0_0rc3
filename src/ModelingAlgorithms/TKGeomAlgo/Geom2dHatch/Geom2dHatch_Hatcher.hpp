#pragma once


#include <Standard.hpp>

#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dHatch_Intersector.hpp>
#include <Geom2dHatch_Elements.hpp>
#include <Standard_Integer.hpp>
#include <Geom2dHatch_Hatching.hpp>
#include <NCollection_DataMap.hpp>
#include <TopAbs_Orientation.hpp>
#include <HatchGen_ErrorStatus.hpp>

class HatchGen_PointOnHatching;
class HatchGen_Domain;

// resolve name collisions with X11 headers
#ifdef Status
  #undef Status
#endif

class Geom2dHatch_Hatcher
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns an empty hatcher.
  Standard_EXPORT Geom2dHatch_Hatcher(const Geom2dHatch_Intersector& Intersector,
                                      const double                   Confusion2d,
                                      const double                   Confusion3d,
                                      const bool                     KeepPnt = false,
                                      const bool                     KeepSeg = false);

  //! Sets the associated intersector.
  Standard_EXPORT void Intersector(const Geom2dHatch_Intersector& Intersector);

  //! Returns the associated intersector.
  const Geom2dHatch_Intersector& Intersector();

  //! Returns the associated intersector.
  Geom2dHatch_Intersector& ChangeIntersector();

  //! Sets the confusion tolerance.
  Standard_EXPORT void Confusion2d(const double Confusion);

  //! Returns the 2d confusion tolerance, i.e. the value under
  //! which two points are considered identical in the
  //! parametric space of the hatching.
  double Confusion2d() const;

  //! Sets the confusion tolerance.
  Standard_EXPORT void Confusion3d(const double Confusion);

  //! Returns the 3d confusion tolerance, i.e. the value under
  //! which two points are considered identical in the
  //! 3d space of the hatching.
  double Confusion3d() const;

  //! Sets the above flag.
  Standard_EXPORT void KeepPoints(const bool Keep);

  //! Returns the flag about the points consideration.
  bool KeepPoints() const;

  //! Sets the above flag.
  Standard_EXPORT void KeepSegments(const bool Keep);

  //! Returns the flag about the segments consideration.
  bool KeepSegments() const;

  //! Removes all the hatchings and all the elements.
  void Clear();

  //! Returns the curve associated to the IndE-th element.
  const Geom2dAdaptor_Curve& ElementCurve(const int IndE) const;

  //! Adds an element to the hatcher and returns its index.
  Standard_EXPORT int AddElement(const Geom2dAdaptor_Curve& Curve,
                                 const TopAbs_Orientation   Orientation = TopAbs_FORWARD);

  //! Adds an element to the hatcher and returns its index.
  int AddElement(const occ::handle<Geom2d_Curve>& Curve,
                 const TopAbs_Orientation         Orientation = TopAbs_FORWARD)
  {
    Geom2dAdaptor_Curve aGAC(Curve);
    return AddElement(aGAC, Orientation);
  }

  //! Removes the IndE-th element from the hatcher.
  Standard_EXPORT void RemElement(const int IndE);

  //! Removes all the elements from the hatcher.
  Standard_EXPORT void ClrElements();

  //! Returns the curve associated to the IndH-th hatching.
  const Geom2dAdaptor_Curve& HatchingCurve(const int IndH) const;

  //! Adds a hatching to the hatcher and returns its index.
  Standard_EXPORT int AddHatching(const Geom2dAdaptor_Curve& Curve);

  //! Removes the IndH-th hatching from the hatcher.
  Standard_EXPORT void RemHatching(const int IndH);

  //! Removes all the hatchings from the hatcher.
  Standard_EXPORT void ClrHatchings();

  //! Returns the number of intersection points of
  //! the IndH-th hatching.
  int NbPoints(const int IndH) const;

  //! Returns the IndP-th intersection point of the
  //! IndH-th hatching.
  const HatchGen_PointOnHatching& Point(const int IndH, const int IndP) const;

  //! Trims all the hatchings of the hatcher by all the
  //! elements of the hatcher.
  Standard_EXPORT void Trim();

  //! Adds a hatching to the hatcher and trims it by
  //! the elements already given and returns its index.
  Standard_EXPORT int Trim(const Geom2dAdaptor_Curve& Curve);

  //! Trims the IndH-th hatching by the elements
  //! already given.
  Standard_EXPORT void Trim(const int IndH);

  //! Computes the domains of all the hatchings.
  Standard_EXPORT void ComputeDomains();

  //! Computes the domains of the IndH-th hatching.
  Standard_EXPORT void ComputeDomains(const int IndH);

  //! Returns the fact that the intersections were computed
  //! for the IndH-th hatching.
  bool TrimDone(const int IndH) const;

  //! Returns the fact that the intersections failed
  //! for the IndH-th hatching.
  bool TrimFailed(const int IndH) const;

  //! Returns the fact that the domains were computed
  //! for all the hatchings.
  bool IsDone() const;

  //! Returns the fact that the domains were computed
  //! for the IndH-th hatching.
  bool IsDone(const int IndH) const;

  //! Returns the status about the IndH-th hatching.
  HatchGen_ErrorStatus Status(const int IndH) const;

  //! Returns the number of domains of the IndH-th hatching.
  //! Only ONE "INFINITE" domain means that the hatching is
  //! fully included in the contour defined by the elements.
  int NbDomains(const int IndH) const;

  //! Returns the IDom-th domain of the IndH-th hatching.
  Standard_EXPORT const HatchGen_Domain& Domain(const int IndH, const int IDom) const;

  //! Dump the hatcher.
  Standard_EXPORT void Dump() const;

protected:
  //! Returns the IndE-th element.
  Geom2dHatch_Element& Element(const int IndE);

  //! Returns the IndH-th hatching.
  Geom2dHatch_Hatching& Hatching(const int IndH);

private:
  //! Trims the IndH-th hatching of the hatcher by the
  //! IndE-th element.
  Standard_EXPORT bool Trim(const int IndH, const int IndE);

  //! Sets the global transition (the before and after
  //! states and segment extremities flags) of the point.
  Standard_EXPORT bool GlobalTransition(HatchGen_PointOnHatching& Point);

  Geom2dHatch_Intersector                        myIntersector;
  double                                         myConfusion2d;
  double                                         myConfusion3d;
  bool                                           myKeepPoints;
  bool                                           myKeepSegments;
  int                                            myNbElements;
  Geom2dHatch_Elements                           myElements;
  int                                            myNbHatchings;
  NCollection_DataMap<int, Geom2dHatch_Hatching> myHatchings;
};
// Created on: 1995-01-03
// Created by: Laurent BUCHARD
// Copyright (c) 1995-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#define RAISE_IF_NOSUCHOBJECT 0
#define TRACE 0

#include <StdFail_NotDone.hpp>

#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dHatch_Intersector.hpp>
#include <Geom2dHatch_Hatching.hpp>
#include <Geom2dHatch_Element.hpp>

//=======================================================================
// Function : Intersector
// Purpose  : Returns the associated intersector.
//=======================================================================

inline const Geom2dHatch_Intersector& Geom2dHatch_Hatcher::Intersector()
{
  return myIntersector;
}

//=======================================================================
// Function : ChangeIntersector
// Purpose  : Returns the associated intersector.
//=======================================================================

inline Geom2dHatch_Intersector& Geom2dHatch_Hatcher::ChangeIntersector()
{
  return myIntersector;
}

//=======================================================================
// Function : Confusion2d
// Purpose  : Returns the 2d confusion tolerance.
//=======================================================================

inline double Geom2dHatch_Hatcher::Confusion2d() const
{
  return myConfusion2d;
}

//=======================================================================
// Function : Confusion3d
// Purpose  : Returns the 3d confusion tolerance.
//=======================================================================

inline double Geom2dHatch_Hatcher::Confusion3d() const
{
  return myConfusion3d;
}

//=======================================================================
// Function : KeepPoints
// Purpose  : Returns the flag about the points consideration.
//=======================================================================

inline bool Geom2dHatch_Hatcher::KeepPoints() const
{
  return myKeepPoints;
}

//=======================================================================
// Function : KeepSegments
// Purpose  : Returns the flag about the segments consideration.
//=======================================================================

inline bool Geom2dHatch_Hatcher::KeepSegments() const
{
  return myKeepSegments;
}

//=======================================================================
// Function : Clear
// Purpose  : Removes all the hatchings and all the elements.
//=======================================================================

inline void Geom2dHatch_Hatcher::Clear()
{
  if (myNbHatchings != 0)
    ClrHatchings();
  if (myNbElements != 0)
    ClrElements();
}

//=======================================================================
// Function : Element
// Purpose  : Returns the IndE-th element.
//=======================================================================

inline Geom2dHatch_Element& Geom2dHatch_Hatcher::Element(const int IndE)
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myElements.IsBound(IndE), "");
#endif
  Geom2dHatch_Element& Element = myElements.ChangeFind(IndE);
  return Element;
}

//=======================================================================
// Function : ElementCurve
// Purpose  : Returns the curve associated to the IndE-th element.
//=======================================================================

inline const Geom2dAdaptor_Curve& Geom2dHatch_Hatcher::ElementCurve(const int IndE) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myElements.IsBound(IndE), "");
#endif
  const Geom2dHatch_Element& Element = myElements.Find(IndE);
  return Element.Curve();
}

//=======================================================================
// Function : Hatching
// Purpose  : Returns the IndH-th hatching.
//=======================================================================

inline Geom2dHatch_Hatching& Geom2dHatch_Hatcher::Hatching(const int IndH)
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  Geom2dHatch_Hatching& Hatching = myHatchings.ChangeFind(IndH);
  return Hatching;
}

//=======================================================================
// Function : HatchingCurve
// Purpose  : Returns the curve associated to the IndH-th hatching.
//=======================================================================

inline const Geom2dAdaptor_Curve& Geom2dHatch_Hatcher::HatchingCurve(const int IndH) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  const Geom2dHatch_Hatching& Hatching = myHatchings.Find(IndH);
  return Hatching.Curve();
}

//=======================================================================
// Function : NbPoints
// Purpose  : Returns the number of intersection points of the IndH-th
//            hatching.
//=======================================================================

inline int Geom2dHatch_Hatcher::NbPoints(const int IndH) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  const Geom2dHatch_Hatching& Hatching = myHatchings.Find(IndH);
  return Hatching.NbPoints();
}

//=======================================================================
// Function : Point
// Purpose  : Returns the IndP-th intersection point of the IndH-th
//            hatching.
//=======================================================================

inline const HatchGen_PointOnHatching& Geom2dHatch_Hatcher::Point(const int IndH,
                                                                  const int IndP) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  const Geom2dHatch_Hatching& Hatching = myHatchings.Find(IndH);
#if RAISE_IF_NOSUCHOBJECT
  Standard_OutOfRange_Raise_if(IndP < 0 || IndP > Hatching.NbPoints(), "");
#endif
  const HatchGen_PointOnHatching& PntH = Hatching.Point(IndP);
  return PntH;
}

//=======================================================================
// Function : TrimDone
// Purpose  : Returns the fact that all the intersections were computed
//            for the IndH-th hatching.
//=======================================================================

inline bool Geom2dHatch_Hatcher::TrimDone(const int IndH) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  const Geom2dHatch_Hatching& Hatching = myHatchings.Find(IndH);
  return Hatching.TrimDone();
}

//=======================================================================
// Function : TrimFailed
// Purpose  : Returns the fact that all the intersections failed
//            for the IndH-th hatching.
//=======================================================================

inline bool Geom2dHatch_Hatcher::TrimFailed(const int IndH) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  const Geom2dHatch_Hatching& Hatching = myHatchings.Find(IndH);
  return Hatching.TrimFailed();
}

//=======================================================================
// Function : IsDone
// Purpose  : Returns the fact that all the domains were computed
//            for the IndH-th hatching.
//=======================================================================

inline bool Geom2dHatch_Hatcher::IsDone(const int IndH) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  const Geom2dHatch_Hatching& Hatching = myHatchings.Find(IndH);
  return Hatching.IsDone();
}

//=======================================================================
// Function : Status
// Purpose  : Returns the status about the IndH-th hatching.
//=======================================================================

inline HatchGen_ErrorStatus Geom2dHatch_Hatcher::Status(const int IndH) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  const Geom2dHatch_Hatching& Hatching = myHatchings.Find(IndH);
  return Hatching.Status();
}

//=======================================================================
// Function : NbDomains
// Purpose  : Returns the number of domains of the IndH-th hatching.
//=======================================================================

inline int Geom2dHatch_Hatcher::NbDomains(const int IndH) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  const Geom2dHatch_Hatching& Hatching = myHatchings.Find(IndH);
  StdFail_NotDone_Raise_if(!Hatching.IsDone(), "Geom2dHatch_Hatcher::NbDomains");
  return Hatching.NbDomains();
}


