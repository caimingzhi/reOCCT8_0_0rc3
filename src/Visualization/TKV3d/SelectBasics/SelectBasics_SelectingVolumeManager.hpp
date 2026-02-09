#pragma once

#include <BVH_Box.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <SelectBasics_PickResult.hpp>
#include <SelectMgr_SelectionType.hpp>

class gp_Pnt;

class SelectBasics_SelectingVolumeManager
{
public:
  SelectBasics_SelectingVolumeManager();

  Standard_EXPORT virtual ~SelectBasics_SelectingVolumeManager();

  virtual int GetActiveSelectionType() const = 0;

public:
  virtual bool OverlapsBox(const NCollection_Vec3<double>& theBoxMin,
                           const NCollection_Vec3<double>& theBoxMax,
                           SelectBasics_PickResult&        thePickResult) const = 0;

  virtual bool OverlapsBox(const NCollection_Vec3<double>& theBoxMin,
                           const NCollection_Vec3<double>& theBoxMax,
                           bool*                           theInside = nullptr) const = 0;

  virtual bool OverlapsPoint(const gp_Pnt&            thePnt,
                             SelectBasics_PickResult& thePickResult) const = 0;

  virtual bool OverlapsPoint(const gp_Pnt& thePnt) const = 0;

  virtual bool OverlapsPolygon(const NCollection_Array1<gp_Pnt>& theArrayOfPts,
                               int                               theSensType,
                               SelectBasics_PickResult&          thePickResult) const = 0;

  virtual bool OverlapsSegment(const gp_Pnt&            thePt1,
                               const gp_Pnt&            thePt2,
                               SelectBasics_PickResult& thePickResult) const = 0;

  virtual bool OverlapsTriangle(const gp_Pnt&            thePt1,
                                const gp_Pnt&            thePt2,
                                const gp_Pnt&            thePt3,
                                int                      theSensType,
                                SelectBasics_PickResult& thePickResult) const = 0;

  virtual bool OverlapsSphere(const gp_Pnt&            theCenter,
                              const double             theRadius,
                              SelectBasics_PickResult& thePickResult) const = 0;

  virtual bool OverlapsSphere(const gp_Pnt& theCenter,
                              const double  theRadius,
                              bool*         theInside = nullptr) const = 0;

  virtual bool OverlapsCylinder(const double             theBottomRad,
                                const double             theTopRad,
                                const double             theHeight,
                                const gp_Trsf&           theTrsf,
                                const bool               theIsHollow,
                                SelectBasics_PickResult& thePickResult) const = 0;

  virtual bool OverlapsCylinder(const double   theBottomRad,
                                const double   theTopRad,
                                const double   theHeight,
                                const gp_Trsf& theTrsf,
                                const bool     theIsHollow,
                                bool*          theInside = nullptr) const = 0;

  virtual bool OverlapsCircle(const double             theRadius,
                              const gp_Trsf&           theTrsf,
                              const bool               theIsFilled,
                              SelectBasics_PickResult& thePickResult) const = 0;

  virtual bool OverlapsCircle(const double   theRadius,
                              const gp_Trsf& theTrsf,
                              const bool     theIsFilled,
                              bool*          theInside = nullptr) const = 0;

public:
  virtual double DistToGeometryCenter(const gp_Pnt& theCOG) const = 0;

  virtual gp_Pnt DetectedPoint(const double theDepth) const = 0;

  virtual bool IsOverlapAllowed() const = 0;

  virtual gp_Pnt GetNearPickedPnt() const = 0;

  virtual gp_Pnt GetFarPickedPnt() const = 0;

  virtual gp_Dir GetViewRayDirection() const = 0;

  virtual bool IsScalableActiveVolume() const = 0;

  virtual gp_Pnt2d GetMousePosition() const = 0;

  virtual void GetPlanes(NCollection_Vector<NCollection_Vec4<double>>& thePlaneEquations) const = 0;

  virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
  {
    (void)theOStream;
    (void)theDepth;
  }

public:
  Standard_DEPRECATED("Deprecated alias for OverlapsBox()")

  bool Overlaps(const NCollection_Vec3<double>& theBoxMin,
                const NCollection_Vec3<double>& theBoxMax,
                SelectBasics_PickResult&        thePickResult) const
  {
    return OverlapsBox(theBoxMin, theBoxMax, thePickResult);
  }

  Standard_DEPRECATED("Deprecated alias for OverlapsBox()")

  bool Overlaps(const NCollection_Vec3<double>& theBoxMin,
                const NCollection_Vec3<double>& theBoxMax,
                bool*                           theInside = nullptr) const
  {
    return OverlapsBox(theBoxMin, theBoxMax, theInside);
  }

  Standard_DEPRECATED("Deprecated alias for OverlapsPoint()")

  bool Overlaps(const gp_Pnt& thePnt, SelectBasics_PickResult& thePickResult) const
  {
    return OverlapsPoint(thePnt, thePickResult);
  }

  Standard_DEPRECATED("Deprecated alias for OverlapsPoint()")

  bool Overlaps(const gp_Pnt& thePnt) const { return OverlapsPoint(thePnt); }

  Standard_DEPRECATED("Deprecated alias for OverlapsPolygon()")
  Standard_EXPORT bool Overlaps(const occ::handle<NCollection_HArray1<gp_Pnt>>& theArrayOfPts,
                                int                                             theSensType,
                                SelectBasics_PickResult& thePickResult) const;

  Standard_DEPRECATED("Deprecated alias for OverlapsPolygon()")

  bool Overlaps(const NCollection_Array1<gp_Pnt>& theArrayOfPts,
                int                               theSensType,
                SelectBasics_PickResult&          thePickResult) const
  {
    return OverlapsPolygon(theArrayOfPts, theSensType, thePickResult);
  }

  Standard_DEPRECATED("Deprecated alias for OverlapsSegment()")

  bool Overlaps(const gp_Pnt&            thePnt1,
                const gp_Pnt&            thePnt2,
                SelectBasics_PickResult& thePickResult) const
  {
    return OverlapsSegment(thePnt1, thePnt2, thePickResult);
  }

  Standard_DEPRECATED("Deprecated alias for OverlapsTriangle()")

  bool Overlaps(const gp_Pnt&            thePnt1,
                const gp_Pnt&            thePnt2,
                const gp_Pnt&            thePnt3,
                int                      theSensType,
                SelectBasics_PickResult& thePickResult) const
  {
    return OverlapsTriangle(thePnt1, thePnt2, thePnt3, theSensType, thePickResult);
  }

#if (!defined(_MSC_VER) || (_MSC_VER >= 1900))                                                     \
  && (!defined(__GNUC__) || (__GNUC__ != 5 && (__GNUC__ != 6 || __GNUC_MINOR__ >= 3)))
  Standard_DEPRECATED("Deprecated alias - SelectMgr_SelectionType should be used instead")
  static const SelectMgr_SelectionType Point = SelectMgr_SelectionType_Point;

  Standard_DEPRECATED("Deprecated alias - SelectMgr_SelectionType should be used instead")
  static const SelectMgr_SelectionType Box = SelectMgr_SelectionType_Box;

  Standard_DEPRECATED("Deprecated alias - SelectMgr_SelectionType should be used instead")
  static const SelectMgr_SelectionType Polyline = SelectMgr_SelectionType_Polyline;

  Standard_DEPRECATED("Deprecated alias - SelectMgr_SelectionType should be used instead")
  static const SelectMgr_SelectionType Unknown = SelectMgr_SelectionType_Unknown;
#endif
};
