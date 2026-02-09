#pragma once

#include <SelectMgr_TriangularFrustum.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class SelectMgr_TriangularFrustumSet : public SelectMgr_BaseFrustum
{
public:
  struct SelectionPolyline
  {
    occ::handle<NCollection_HArray1<gp_Pnt2d>> Points;
  };

public:
  SelectMgr_TriangularFrustumSet();

  Standard_EXPORT ~SelectMgr_TriangularFrustumSet() override;

  Standard_EXPORT void Init(const NCollection_Array1<gp_Pnt2d>& thePoints);

  Standard_EXPORT void Build() override;

  bool IsScalable() const override { return false; }

  Standard_EXPORT occ::handle<SelectMgr_BaseIntersector> ScaleAndTransform(
    const int                                    theScale,
    const gp_GTrsf&                              theTrsf,
    const occ::handle<SelectMgr_FrustumBuilder>& theBuilder) const override;

  Standard_EXPORT occ::handle<SelectMgr_BaseIntersector> CopyWithBuilder(
    const occ::handle<SelectMgr_FrustumBuilder>& theBuilder) const override;

public:
  Standard_EXPORT bool OverlapsBox(const NCollection_Vec3<double>& theMinPnt,
                                   const NCollection_Vec3<double>& theMaxPnt,
                                   const SelectMgr_ViewClipRange&  theClipRange,
                                   SelectBasics_PickResult&        thePickResult) const override;

  Standard_EXPORT bool OverlapsBox(const NCollection_Vec3<double>& theMinPnt,
                                   const NCollection_Vec3<double>& theMaxPnt,
                                   bool*                           theInside) const override;

  Standard_EXPORT bool OverlapsPoint(const gp_Pnt&                  thePnt,
                                     const SelectMgr_ViewClipRange& theClipRange,
                                     SelectBasics_PickResult&       thePickResult) const override;

  bool OverlapsPoint(const gp_Pnt&) const override { return false; }

  Standard_EXPORT bool OverlapsPolygon(const NCollection_Array1<gp_Pnt>& theArrayOfPnts,
                                       Select3D_TypeOfSensitivity        theSensType,
                                       const SelectMgr_ViewClipRange&    theClipRange,
                                       SelectBasics_PickResult& thePickResult) const override;

  Standard_EXPORT bool OverlapsSegment(const gp_Pnt&                  thePnt1,
                                       const gp_Pnt&                  thePnt2,
                                       const SelectMgr_ViewClipRange& theClipRange,
                                       SelectBasics_PickResult&       thePickResult) const override;

  Standard_EXPORT bool OverlapsTriangle(const gp_Pnt&                  thePnt1,
                                        const gp_Pnt&                  thePnt2,
                                        const gp_Pnt&                  thePnt3,
                                        Select3D_TypeOfSensitivity     theSensType,
                                        const SelectMgr_ViewClipRange& theClipRange,
                                        SelectBasics_PickResult& thePickResult) const override;

public:
  Standard_EXPORT gp_Pnt DetectedPoint(const double theDepth) const override;

  Standard_EXPORT bool OverlapsSphere(const gp_Pnt& theCenter,
                                      const double  theRadius,
                                      bool*         theInside = nullptr) const override;

  Standard_EXPORT bool OverlapsSphere(const gp_Pnt&                  theCenter,
                                      const double                   theRadius,
                                      const SelectMgr_ViewClipRange& theClipRange,
                                      SelectBasics_PickResult&       thePickResult) const override;

  Standard_EXPORT bool OverlapsCylinder(const double                   theBottomRad,
                                        const double                   theTopRad,
                                        const double                   theHeight,
                                        const gp_Trsf&                 theTrsf,
                                        const bool                     theIsHollow,
                                        const SelectMgr_ViewClipRange& theClipRange,
                                        SelectBasics_PickResult& thePickResult) const override;

  Standard_EXPORT bool OverlapsCylinder(const double   theBottomRad,
                                        const double   theTopRad,
                                        const double   theHeight,
                                        const gp_Trsf& theTrsf,
                                        const bool     theIsHollow,
                                        bool*          theInside = nullptr) const override;

  Standard_EXPORT bool OverlapsCircle(const double                   theBottomRad,
                                      const gp_Trsf&                 theTrsf,
                                      const bool                     theIsFilled,
                                      const SelectMgr_ViewClipRange& theClipRange,
                                      SelectBasics_PickResult&       thePickResult) const override;

  Standard_EXPORT bool OverlapsCircle(const double   theBottomRad,
                                      const gp_Trsf& theTrsf,
                                      const bool     theIsFilled,
                                      bool*          theInside = nullptr) const override;

  Standard_EXPORT void GetPlanes(
    NCollection_Vector<NCollection_Vec4<double>>& thePlaneEquations) const override;

  Standard_EXPORT virtual void SetAllowOverlapDetection(const bool theIsToAllow);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  Standard_EXPORT bool isIntersectBoundary(const gp_Pnt& thePnt1, const gp_Pnt& thePnt2) const;

  Standard_EXPORT bool isIntersectBoundary(const double   theRadius,
                                           const gp_Trsf& theTrsf,
                                           const bool     theIsFilled) const;

  Standard_EXPORT static bool segmentTriangleIntersection(const gp_Pnt& theOrig,
                                                          const gp_Vec& theDir,
                                                          const gp_Pnt& theV1,
                                                          const gp_Pnt& theV2,
                                                          const gp_Pnt& theV3);

  Standard_EXPORT static bool segmentSegmentIntersection(const gp_Pnt& theStartPnt1,
                                                         const gp_Pnt& theEndPnt1,
                                                         const gp_Pnt& theStartPnt2,
                                                         const gp_Pnt& theEndPnt2);

  Standard_EXPORT static bool pointInTriangle(const gp_Pnt& thePnt,
                                              const gp_Pnt& theV1,
                                              const gp_Pnt& theV2,
                                              const gp_Pnt& theV3);

private:
  NCollection_List<occ::handle<SelectMgr_TriangularFrustum>> myFrustums;

  SelectionPolyline          mySelPolyline;
  NCollection_Array1<gp_Pnt> myBoundaryPoints;

  bool myToAllowOverlap;
};
