#pragma once

#include <SelectBasics_SelectingVolumeManager.hpp>

#include <SelectMgr_BaseIntersector.hpp>
#include <gp_Trsf.hpp>
#include <NCollection_Mat4.hpp>
#include <NCollection_Vec3.hpp>
#include <NCollection_Vec4.hpp>
#include <SelectMgr_ViewClipRange.hpp>

class SelectMgr_SelectingVolumeManager : public SelectBasics_SelectingVolumeManager
{
public:
  Standard_EXPORT SelectMgr_SelectingVolumeManager();

  ~SelectMgr_SelectingVolumeManager() override = default;

  Standard_EXPORT void InitPointSelectingVolume(const gp_Pnt2d& thePoint);

  Standard_EXPORT void InitBoxSelectingVolume(const gp_Pnt2d& theMinPt, const gp_Pnt2d& theMaxPt);

  Standard_EXPORT void InitPolylineSelectingVolume(const NCollection_Array1<gp_Pnt2d>& thePoints);

  Standard_EXPORT void InitAxisSelectingVolume(const gp_Ax1& theAxis);

  Standard_EXPORT void InitSelectingVolume(const occ::handle<SelectMgr_BaseIntersector>& theVolume);

  Standard_EXPORT void BuildSelectingVolume();

  const occ::handle<SelectMgr_BaseIntersector>& ActiveVolume() const
  {
    return myActiveSelectingVolume;
  }

  Standard_EXPORT int GetActiveSelectionType() const override;

  Standard_EXPORT virtual SelectMgr_SelectingVolumeManager ScaleAndTransform(
    const int                                    theScaleFactor,
    const gp_GTrsf&                              theTrsf,
    const occ::handle<SelectMgr_FrustumBuilder>& theBuilder) const;

  Standard_EXPORT virtual SelectMgr_SelectingVolumeManager CopyWithBuilder(
    const occ::handle<SelectMgr_FrustumBuilder>& theBuilder) const;

public:
  Standard_EXPORT const occ::handle<Graphic3d_Camera>& Camera() const;

  Standard_EXPORT void SetCamera(const occ::handle<Graphic3d_Camera>& theCamera);

  Standard_EXPORT void SetViewport(const double theX,
                                   const double theY,
                                   const double theWidth,
                                   const double theHeight);

  Standard_EXPORT void SetPixelTolerance(const int theTolerance);

  Standard_EXPORT void WindowSize(int& theWidth, int& theHeight) const;

  Standard_EXPORT void SetWindowSize(const int theWidth, const int theHeight);

  Standard_EXPORT bool OverlapsBox(const NCollection_Vec3<double>& theBoxMin,
                                   const NCollection_Vec3<double>& theBoxMax,
                                   SelectBasics_PickResult&        thePickResult) const override;

  Standard_EXPORT bool OverlapsBox(const NCollection_Vec3<double>& theBoxMin,
                                   const NCollection_Vec3<double>& theBoxMax,
                                   bool* theInside = nullptr) const override;

  Standard_EXPORT bool OverlapsPoint(const gp_Pnt&            thePnt,
                                     SelectBasics_PickResult& thePickResult) const override;

  Standard_EXPORT bool OverlapsPoint(const gp_Pnt& thePnt) const override;

  Standard_EXPORT bool OverlapsPolygon(const NCollection_Array1<gp_Pnt>& theArrayOfPts,
                                       int                               theSensType,
                                       SelectBasics_PickResult& thePickResult) const override;

  Standard_EXPORT bool OverlapsSegment(const gp_Pnt&            thePnt1,
                                       const gp_Pnt&            thePnt2,
                                       SelectBasics_PickResult& thePickResult) const override;

  Standard_EXPORT bool OverlapsTriangle(const gp_Pnt&            thePnt1,
                                        const gp_Pnt&            thePnt2,
                                        const gp_Pnt&            thePnt3,
                                        int                      theSensType,
                                        SelectBasics_PickResult& thePickResult) const override;

  Standard_EXPORT bool OverlapsSphere(const gp_Pnt&            theCenter,
                                      const double             theRadius,
                                      SelectBasics_PickResult& thePickResult) const override;

  Standard_EXPORT bool OverlapsSphere(const gp_Pnt& theCenter,
                                      const double  theRadius,
                                      bool*         theInside = nullptr) const override;

  Standard_EXPORT bool OverlapsCylinder(const double             theBottomRad,
                                        const double             theTopRad,
                                        const double             theHeight,
                                        const gp_Trsf&           theTrsf,
                                        const bool               theIsHollow,
                                        SelectBasics_PickResult& thePickResult) const override;

  Standard_EXPORT bool OverlapsCylinder(const double   theBottomRad,
                                        const double   theTopRad,
                                        const double   theHeight,
                                        const gp_Trsf& theTrsf,
                                        const bool     theIsHollow,
                                        bool*          theInside = nullptr) const override;

  Standard_EXPORT bool OverlapsCircle(const double             theBottomRad,
                                      const gp_Trsf&           theTrsf,
                                      const bool               theIsFilled,
                                      SelectBasics_PickResult& thePickResult) const override;

  Standard_EXPORT bool OverlapsCircle(const double   theBottomRad,
                                      const gp_Trsf& theTrsf,
                                      const bool     theIsFilled,
                                      bool*          theInside = nullptr) const override;

  Standard_EXPORT double DistToGeometryCenter(const gp_Pnt& theCOG) const override;

  Standard_EXPORT gp_Pnt DetectedPoint(const double theDepth) const override;

  Standard_EXPORT virtual void AllowOverlapDetection(const bool theIsToAllow);

  Standard_EXPORT bool IsOverlapAllowed() const override;

  const occ::handle<Graphic3d_SequenceOfHClipPlane>& ViewClipping() const
  {
    return myViewClipPlanes;
  }

  const occ::handle<Graphic3d_SequenceOfHClipPlane>& ObjectClipping() const
  {
    return myObjectClipPlanes;
  }

  Standard_EXPORT void SetViewClipping(
    const occ::handle<Graphic3d_SequenceOfHClipPlane>& theViewPlanes,
    const occ::handle<Graphic3d_SequenceOfHClipPlane>& theObjPlanes,
    const SelectMgr_SelectingVolumeManager*            theWorldSelMgr);

  Standard_EXPORT void SetViewClipping(const SelectMgr_SelectingVolumeManager& theOther);

  const SelectMgr_ViewClipRange& ViewClipRanges() const { return myViewClipRange; }

  void SetViewClipRanges(const SelectMgr_ViewClipRange& theRange) { myViewClipRange = theRange; }

  Standard_EXPORT const gp_Pnt* GetVertices() const;

  Standard_EXPORT gp_Pnt GetNearPickedPnt() const override;

  Standard_EXPORT gp_Pnt GetFarPickedPnt() const override;

  Standard_EXPORT gp_Dir GetViewRayDirection() const override;

  Standard_EXPORT bool IsScalableActiveVolume() const override;

  Standard_EXPORT gp_Pnt2d GetMousePosition() const override;

  Standard_EXPORT void GetPlanes(
    NCollection_Vector<NCollection_Vec4<double>>& thePlaneEquations) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

public:
  Standard_DEPRECATED(
    "Deprecated method - InitPointSelectingVolume() and Build() methods should be used instead")
  Standard_EXPORT void BuildSelectingVolume(const gp_Pnt2d& thePoint);

  Standard_DEPRECATED(
    "Deprecated method - InitBoxSelectingVolume() and Build() should be used instead")
  Standard_EXPORT void BuildSelectingVolume(const gp_Pnt2d& theMinPt, const gp_Pnt2d& theMaxPt);

  Standard_DEPRECATED(
    "Deprecated method - InitPolylineSelectingVolume() and Build() should be used instead")
  Standard_EXPORT void BuildSelectingVolume(const NCollection_Array1<gp_Pnt2d>& thePoints);

private:
  occ::handle<SelectMgr_BaseIntersector> myActiveSelectingVolume;

  occ::handle<Graphic3d_SequenceOfHClipPlane> myViewClipPlanes;
  occ::handle<Graphic3d_SequenceOfHClipPlane> myObjectClipPlanes;
  SelectMgr_ViewClipRange                     myViewClipRange;
  bool                                        myToAllowOverlap;
};
