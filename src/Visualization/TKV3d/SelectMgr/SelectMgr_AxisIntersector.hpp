#pragma once

#include <SelectMgr_BaseIntersector.hpp>

#include <gp_Ax1.hpp>

class SelectMgr_AxisIntersector : public SelectMgr_BaseIntersector
{
public:
  Standard_EXPORT SelectMgr_AxisIntersector();

  Standard_EXPORT ~SelectMgr_AxisIntersector() override;

  Standard_EXPORT void Init(const gp_Ax1& theAxis);

  Standard_EXPORT void Build() override;

  Standard_EXPORT void SetCamera(const occ::handle<Graphic3d_Camera>& theCamera) override;

  bool IsScalable() const override { return false; }

  Standard_EXPORT occ::handle<SelectMgr_BaseIntersector> ScaleAndTransform(
    const int                                    theScaleFactor,
    const gp_GTrsf&                              theTrsf,
    const occ::handle<SelectMgr_FrustumBuilder>& theBuilder) const override;

  Standard_EXPORT occ::handle<SelectMgr_BaseIntersector> CopyWithBuilder(
    const occ::handle<SelectMgr_FrustumBuilder>& theBuilder) const override;

public:
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

  Standard_EXPORT bool OverlapsCircle(const double                   theRadius,
                                      const gp_Trsf&                 theTrsf,
                                      const bool                     theIsFilled,
                                      const SelectMgr_ViewClipRange& theClipRange,
                                      SelectBasics_PickResult&       thePickResult) const override;

  Standard_EXPORT bool OverlapsCircle(const double   theRadius,
                                      const gp_Trsf& theTrsf,
                                      const bool     theIsFilled,
                                      bool*          theInside = nullptr) const override;

public:
  Standard_EXPORT double DistToGeometryCenter(const gp_Pnt& theCOG) const override;

  Standard_EXPORT gp_Pnt DetectedPoint(const double theDepth) const override;

  Standard_EXPORT const gp_Pnt& GetNearPnt() const override;

  Standard_EXPORT const gp_Pnt& GetFarPnt() const override;

  Standard_EXPORT const gp_Dir& GetViewRayDirection() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT bool hasIntersection(const NCollection_Vec3<double>& theBoxMin,
                                       const NCollection_Vec3<double>& theBoxMax,
                                       double&                         theTimeEnter,
                                       double&                         theTimeLeave) const;

  Standard_EXPORT bool hasIntersection(const gp_Pnt& thePnt, double& theDepth) const;

  Standard_EXPORT bool raySegmentDistance(const gp_Pnt&            theSegPnt1,
                                          const gp_Pnt&            theSegPnt2,
                                          SelectBasics_PickResult& thePickResult) const;

  Standard_EXPORT bool rayPlaneIntersection(const gp_Vec&            thePlane,
                                            const gp_Pnt&            thePntOnPlane,
                                            SelectBasics_PickResult& thePickResult) const;

private:
  gp_Ax1 myAxis;
};
