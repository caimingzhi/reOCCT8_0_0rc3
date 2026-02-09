#pragma once

#include <SelectMgr_Frustum.hpp>

class SelectMgr_RectangularFrustum : public SelectMgr_Frustum<4>
{
public:
  struct SelectionRectangle
  {
    SelectionRectangle()
        : myMinPnt(gp_Pnt2d(RealLast(), RealLast())),
          myMaxPnt(gp_Pnt2d(RealLast(), RealLast()))
    {
    }

    const gp_Pnt2d& MousePos() const { return myMinPnt; }

    void SetMousePos(const gp_Pnt2d& thePos)
    {
      myMinPnt = thePos;
      myMaxPnt = thePos;
    }

    const gp_Pnt2d& MinPnt() const { return myMinPnt; }

    void SetMinPnt(const gp_Pnt2d& theMinPnt) { myMinPnt = theMinPnt; }

    const gp_Pnt2d& MaxPnt() const { return myMaxPnt; }

    void SetMaxPnt(const gp_Pnt2d& theMaxPnt) { myMaxPnt = theMaxPnt; }

  private:
    gp_Pnt2d myMinPnt;
    gp_Pnt2d myMaxPnt;
  };

  Standard_EXPORT SelectMgr_RectangularFrustum();

  Standard_EXPORT void Init(const gp_Pnt2d& thePoint);

  Standard_EXPORT void Init(const gp_Pnt2d& theMinPnt, const gp_Pnt2d& theMaxPnt);

  Standard_EXPORT bool isIntersectCircle(const double                      theRadius,
                                         const gp_Pnt&                     theCenter,
                                         const gp_Trsf&                    theTrsf,
                                         const NCollection_Array1<gp_Pnt>& theVertices) const;

  Standard_EXPORT bool isSegmentsIntersect(const gp_Pnt& thePnt1Seg1,
                                           const gp_Pnt& thePnt2Seg1,
                                           const gp_Pnt& thePnt1Seg2,
                                           const gp_Pnt& thePnt2Seg2) const;

  Standard_EXPORT void Build() override;

  Standard_EXPORT bool IsScalable() const override;

  Standard_EXPORT occ::handle<SelectMgr_BaseIntersector> ScaleAndTransform(
    const int                                    theScaleFactor,
    const gp_GTrsf&                              theTrsf,
    const occ::handle<SelectMgr_FrustumBuilder>& theBuilder) const override;

  Standard_EXPORT occ::handle<SelectMgr_BaseIntersector> CopyWithBuilder(
    const occ::handle<SelectMgr_FrustumBuilder>& theBuilder) const override;

  Standard_EXPORT bool OverlapsBox(const NCollection_Vec3<double>& theBoxMin,
                                   const NCollection_Vec3<double>& theBoxMax,
                                   const SelectMgr_ViewClipRange&  theClipRange,
                                   SelectBasics_PickResult&        thePickResult) const override;

  Standard_EXPORT bool OverlapsBox(const NCollection_Vec3<double>& theBoxMin,
                                   const NCollection_Vec3<double>& theBoxMax,
                                   bool*                           theInside) const override;

  Standard_EXPORT bool OverlapsPoint(const gp_Pnt&                  thePnt,
                                     const SelectMgr_ViewClipRange& theClipRange,
                                     SelectBasics_PickResult&       thePickResult) const override;

  Standard_EXPORT bool OverlapsPoint(const gp_Pnt& thePnt) const override;

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

  Standard_EXPORT bool OverlapsSphere(const gp_Pnt&                  theCenter,
                                      const double                   theRadius,
                                      const SelectMgr_ViewClipRange& theClipRange,
                                      SelectBasics_PickResult&       thePickResult) const override;

  Standard_EXPORT bool OverlapsSphere(const gp_Pnt& theCenter,
                                      const double  theRadius,
                                      bool*         theInside) const override;

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

  Standard_EXPORT double DistToGeometryCenter(const gp_Pnt& theCOG) const override;

  Standard_EXPORT gp_Pnt DetectedPoint(const double theDepth) const override;

  const gp_Pnt* GetVertices() const { return myVertices; }

  const gp_Pnt& GetNearPnt() const override { return myNearPickedPnt; }

  const gp_Pnt& GetFarPnt() const override { return myFarPickedPnt; }

  const gp_Dir& GetViewRayDirection() const override { return myViewRayDir; }

  Standard_EXPORT const gp_Pnt2d& GetMousePosition() const override;

  Standard_EXPORT void GetPlanes(
    NCollection_Vector<NCollection_Vec4<double>>& thePlaneEquations) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT void segmentSegmentDistance(const gp_Pnt&            theSegPnt1,
                                              const gp_Pnt&            theSegPnt2,
                                              SelectBasics_PickResult& thePickResult) const;

  Standard_EXPORT bool segmentPlaneIntersection(const gp_Vec&            thePlane,
                                                const gp_Pnt&            thePntOnPlane,
                                                SelectBasics_PickResult& thePickResult) const;

private:
  void cacheVertexProjections(SelectMgr_RectangularFrustum* theFrustum) const;

private:
  enum
  {
    LeftTopNear,
    LeftTopFar,
    LeftBottomNear,
    LeftBottomFar,
    RightTopNear,
    RightTopFar,
    RightBottomNear,
    RightBottomFar
  };

private:
  SelectionRectangle mySelRectangle;
  gp_Pnt             myNearPickedPnt;
  gp_Pnt             myFarPickedPnt;
  gp_Dir             myViewRayDir;
  double             myScale;
};
