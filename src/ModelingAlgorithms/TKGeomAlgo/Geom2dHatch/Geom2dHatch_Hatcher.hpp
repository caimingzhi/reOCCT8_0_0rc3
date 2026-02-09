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

#ifdef Status
  #undef Status
#endif

class Geom2dHatch_Hatcher
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dHatch_Hatcher(const Geom2dHatch_Intersector& Intersector,
                                      const double                   Confusion2d,
                                      const double                   Confusion3d,
                                      const bool                     KeepPnt = false,
                                      const bool                     KeepSeg = false);

  Standard_EXPORT void Intersector(const Geom2dHatch_Intersector& Intersector);

  const Geom2dHatch_Intersector& Intersector();

  Geom2dHatch_Intersector& ChangeIntersector();

  Standard_EXPORT void Confusion2d(const double Confusion);

  double Confusion2d() const;

  Standard_EXPORT void Confusion3d(const double Confusion);

  double Confusion3d() const;

  Standard_EXPORT void KeepPoints(const bool Keep);

  bool KeepPoints() const;

  Standard_EXPORT void KeepSegments(const bool Keep);

  bool KeepSegments() const;

  void Clear();

  const Geom2dAdaptor_Curve& ElementCurve(const int IndE) const;

  Standard_EXPORT int AddElement(const Geom2dAdaptor_Curve& Curve,
                                 const TopAbs_Orientation   Orientation = TopAbs_FORWARD);

  int AddElement(const occ::handle<Geom2d_Curve>& Curve,
                 const TopAbs_Orientation         Orientation = TopAbs_FORWARD)
  {
    Geom2dAdaptor_Curve aGAC(Curve);
    return AddElement(aGAC, Orientation);
  }

  Standard_EXPORT void RemElement(const int IndE);

  Standard_EXPORT void ClrElements();

  const Geom2dAdaptor_Curve& HatchingCurve(const int IndH) const;

  Standard_EXPORT int AddHatching(const Geom2dAdaptor_Curve& Curve);

  Standard_EXPORT void RemHatching(const int IndH);

  Standard_EXPORT void ClrHatchings();

  int NbPoints(const int IndH) const;

  const HatchGen_PointOnHatching& Point(const int IndH, const int IndP) const;

  Standard_EXPORT void Trim();

  Standard_EXPORT int Trim(const Geom2dAdaptor_Curve& Curve);

  Standard_EXPORT void Trim(const int IndH);

  Standard_EXPORT void ComputeDomains();

  Standard_EXPORT void ComputeDomains(const int IndH);

  bool TrimDone(const int IndH) const;

  bool TrimFailed(const int IndH) const;

  bool IsDone() const;

  bool IsDone(const int IndH) const;

  HatchGen_ErrorStatus Status(const int IndH) const;

  int NbDomains(const int IndH) const;

  Standard_EXPORT const HatchGen_Domain& Domain(const int IndH, const int IDom) const;

  Standard_EXPORT void Dump() const;

protected:
  Geom2dHatch_Element& Element(const int IndE);

  Geom2dHatch_Hatching& Hatching(const int IndH);

private:
  Standard_EXPORT bool Trim(const int IndH, const int IndE);

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

#define RAISE_IF_NOSUCHOBJECT 0
#define TRACE 0

#include <StdFail_NotDone.hpp>

#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dHatch_Intersector.hpp>
#include <Geom2dHatch_Hatching.hpp>
#include <Geom2dHatch_Element.hpp>

inline const Geom2dHatch_Intersector& Geom2dHatch_Hatcher::Intersector()
{
  return myIntersector;
}

inline Geom2dHatch_Intersector& Geom2dHatch_Hatcher::ChangeIntersector()
{
  return myIntersector;
}

inline double Geom2dHatch_Hatcher::Confusion2d() const
{
  return myConfusion2d;
}

inline double Geom2dHatch_Hatcher::Confusion3d() const
{
  return myConfusion3d;
}

inline bool Geom2dHatch_Hatcher::KeepPoints() const
{
  return myKeepPoints;
}

inline bool Geom2dHatch_Hatcher::KeepSegments() const
{
  return myKeepSegments;
}

inline void Geom2dHatch_Hatcher::Clear()
{
  if (myNbHatchings != 0)
    ClrHatchings();
  if (myNbElements != 0)
    ClrElements();
}

inline Geom2dHatch_Element& Geom2dHatch_Hatcher::Element(const int IndE)
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myElements.IsBound(IndE), "");
#endif
  Geom2dHatch_Element& Element = myElements.ChangeFind(IndE);
  return Element;
}

inline const Geom2dAdaptor_Curve& Geom2dHatch_Hatcher::ElementCurve(const int IndE) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myElements.IsBound(IndE), "");
#endif
  const Geom2dHatch_Element& Element = myElements.Find(IndE);
  return Element.Curve();
}

inline Geom2dHatch_Hatching& Geom2dHatch_Hatcher::Hatching(const int IndH)
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  Geom2dHatch_Hatching& Hatching = myHatchings.ChangeFind(IndH);
  return Hatching;
}

inline const Geom2dAdaptor_Curve& Geom2dHatch_Hatcher::HatchingCurve(const int IndH) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  const Geom2dHatch_Hatching& Hatching = myHatchings.Find(IndH);
  return Hatching.Curve();
}

inline int Geom2dHatch_Hatcher::NbPoints(const int IndH) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  const Geom2dHatch_Hatching& Hatching = myHatchings.Find(IndH);
  return Hatching.NbPoints();
}

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

inline bool Geom2dHatch_Hatcher::TrimDone(const int IndH) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  const Geom2dHatch_Hatching& Hatching = myHatchings.Find(IndH);
  return Hatching.TrimDone();
}

inline bool Geom2dHatch_Hatcher::TrimFailed(const int IndH) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  const Geom2dHatch_Hatching& Hatching = myHatchings.Find(IndH);
  return Hatching.TrimFailed();
}

inline bool Geom2dHatch_Hatcher::IsDone(const int IndH) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  const Geom2dHatch_Hatching& Hatching = myHatchings.Find(IndH);
  return Hatching.IsDone();
}

inline HatchGen_ErrorStatus Geom2dHatch_Hatcher::Status(const int IndH) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  const Geom2dHatch_Hatching& Hatching = myHatchings.Find(IndH);
  return Hatching.Status();
}

inline int Geom2dHatch_Hatcher::NbDomains(const int IndH) const
{
#if RAISE_IF_NOSUCHOBJECT
  Standard_NoSuchObject_Raise_if(!myHatchings.IsBound(IndH), "");
#endif
  const Geom2dHatch_Hatching& Hatching = myHatchings.Find(IndH);
  StdFail_NotDone_Raise_if(!Hatching.IsDone(), "Geom2dHatch_Hatcher::NbDomains");
  return Hatching.NbDomains();
}
