#pragma once

#include <SelectMgr_Frustum.hpp>

class SelectMgr_TriangularFrustum : public SelectMgr_Frustum<3>
{
public:
  struct SelectionTriangle
  {
    gp_Pnt2d Points[3];
  };

public:
  Standard_EXPORT ~SelectMgr_TriangularFrustum() override;

  Standard_EXPORT void Init(const gp_Pnt2d& theP1, const gp_Pnt2d& theP2, const gp_Pnt2d& theP3);

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

  Standard_EXPORT bool OverlapsBox(const NCollection_Vec3<double>& theMinPt,
                                   const NCollection_Vec3<double>& theMaxPt,
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
  Standard_EXPORT void Clear();

  Standard_EXPORT void GetPlanes(
    NCollection_Vector<NCollection_Vec4<double>>& thePlaneEquations) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT SelectMgr_TriangularFrustum();

private:
  void cacheVertexProjections(SelectMgr_TriangularFrustum* theFrustum) const;

protected:
  SelectionTriangle mySelTriangle;

public:
  DEFINE_STANDARD_RTTIEXT(SelectMgr_TriangularFrustum, SelectMgr_Frustum<3>)
  friend class SelectMgr_TriangularFrustumSet;
};
