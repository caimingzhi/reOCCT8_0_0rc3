#pragma once

#include <gp_GTrsf.hpp>
#include <NCollection_Mat4.hpp>
#include <Standard_TypeDef.hpp>
#include <Graphic3d_WorldViewProjState.hpp>
#include <NCollection_Vector.hpp>
#include <Select3D_TypeOfSensitivity.hpp>
#include <SelectBasics_PickResult.hpp>
#include <SelectMgr_SelectionType.hpp>
#include <gp_Trsf.hpp>
#include <NCollection_Vec3.hpp>
#include <NCollection_Vec4.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt.hpp>

class Graphic3d_Camera;
class SelectMgr_FrustumBuilder;
class SelectMgr_ViewClipRange;

class SelectMgr_BaseIntersector : public Standard_Transient
{
public:
  Standard_EXPORT SelectMgr_BaseIntersector();

  Standard_EXPORT ~SelectMgr_BaseIntersector() override;

  virtual void Build() = 0;

  SelectMgr_SelectionType GetSelectionType() const { return mySelectionType; }

public:
  virtual bool IsScalable() const = 0;

  Standard_EXPORT virtual void SetPixelTolerance(const int theTol);

  virtual occ::handle<SelectMgr_BaseIntersector> ScaleAndTransform(
    const int                                    theScaleFactor,
    const gp_GTrsf&                              theTrsf,
    const occ::handle<SelectMgr_FrustumBuilder>& theBuilder) const = 0;

  virtual occ::handle<SelectMgr_BaseIntersector> CopyWithBuilder(
    const occ::handle<SelectMgr_FrustumBuilder>& theBuilder) const = 0;

public:
  const occ::handle<Graphic3d_Camera>& Camera() const { return myCamera; }

  Standard_EXPORT virtual void SetCamera(const occ::handle<Graphic3d_Camera>& theCamera);

  Standard_EXPORT virtual void WindowSize(int& theWidth, int& theHeight) const;

  Standard_EXPORT virtual void SetWindowSize(const int theWidth, const int theHeight);

  Standard_EXPORT virtual void SetViewport(const double theX,
                                           const double theY,
                                           const double theWidth,
                                           const double theHeight);

  Standard_EXPORT virtual const gp_Pnt& GetNearPnt() const;

  Standard_EXPORT virtual const gp_Pnt& GetFarPnt() const;

  Standard_EXPORT virtual const gp_Dir& GetViewRayDirection() const;

  Standard_EXPORT virtual const gp_Pnt2d& GetMousePosition() const;

  virtual void GetPlanes(NCollection_Vector<NCollection_Vec4<double>>& thePlaneEquations) const
  {
    thePlaneEquations.Clear();
  }

public:
  virtual bool OverlapsBox(const NCollection_Vec3<double>& theBoxMin,
                           const NCollection_Vec3<double>& theBoxMax,
                           const SelectMgr_ViewClipRange&  theClipRange,
                           SelectBasics_PickResult&        thePickResult) const = 0;

  virtual bool OverlapsBox(const NCollection_Vec3<double>& theBoxMin,
                           const NCollection_Vec3<double>& theBoxMax,
                           bool*                           theInside = nullptr) const = 0;

  virtual bool OverlapsPoint(const gp_Pnt&                  thePnt,
                             const SelectMgr_ViewClipRange& theClipRange,
                             SelectBasics_PickResult&       thePickResult) const = 0;

  virtual bool OverlapsPoint(const gp_Pnt& thePnt) const = 0;

  virtual bool OverlapsPolygon(const NCollection_Array1<gp_Pnt>& theArrayOfPnts,
                               Select3D_TypeOfSensitivity        theSensType,
                               const SelectMgr_ViewClipRange&    theClipRange,
                               SelectBasics_PickResult&          thePickResult) const = 0;

  virtual bool OverlapsSegment(const gp_Pnt&                  thePnt1,
                               const gp_Pnt&                  thePnt2,
                               const SelectMgr_ViewClipRange& theClipRange,
                               SelectBasics_PickResult&       thePickResult) const = 0;

  virtual bool OverlapsTriangle(const gp_Pnt&                  thePnt1,
                                const gp_Pnt&                  thePnt2,
                                const gp_Pnt&                  thePnt3,
                                Select3D_TypeOfSensitivity     theSensType,
                                const SelectMgr_ViewClipRange& theClipRange,
                                SelectBasics_PickResult&       thePickResult) const = 0;

  Standard_EXPORT virtual bool OverlapsSphere(const gp_Pnt& theCenter,
                                              const double  theRadius,
                                              bool*         theInside = nullptr) const = 0;

  Standard_EXPORT virtual bool OverlapsSphere(const gp_Pnt&                  theCenter,
                                              const double                   theRadius,
                                              const SelectMgr_ViewClipRange& theClipRange,
                                              SelectBasics_PickResult& thePickResult) const = 0;

  virtual bool OverlapsCylinder(const double                   theBottomRad,
                                const double                   theTopRad,
                                const double                   theHeight,
                                const gp_Trsf&                 theTrsf,
                                const bool                     theIsHollow,
                                const SelectMgr_ViewClipRange& theClipRange,
                                SelectBasics_PickResult&       thePickResult) const = 0;

  virtual bool OverlapsCylinder(const double   theBottomRad,
                                const double   theTopRad,
                                const double   theHeight,
                                const gp_Trsf& theTrsf,
                                const bool     theIsHollow,
                                bool*          theInside = nullptr) const = 0;

  virtual bool OverlapsCircle(const double                   theBottomRad,
                              const gp_Trsf&                 theTrsf,
                              const bool                     theIsFilled,
                              const SelectMgr_ViewClipRange& theClipRange,
                              SelectBasics_PickResult&       thePickResult) const = 0;

  virtual bool OverlapsCircle(const double   theBottomRad,
                              const gp_Trsf& theTrsf,
                              const bool     theIsFilled,
                              bool*          theInside = nullptr) const = 0;

public:
  Standard_EXPORT virtual double DistToGeometryCenter(const gp_Pnt& theCOG) const;

  Standard_EXPORT virtual gp_Pnt DetectedPoint(const double theDepth) const;

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  Standard_EXPORT virtual bool RaySphereIntersection(const gp_Pnt& theCenter,
                                                     const double  theRadius,
                                                     const gp_Pnt& theLoc,
                                                     const gp_Dir& theRayDir,
                                                     double&       theTimeEnter,
                                                     double&       theTimeLeave) const;

  Standard_EXPORT virtual bool RayCylinderIntersection(const double  theBottomRadius,
                                                       const double  theTopRadius,
                                                       const double  theHeight,
                                                       const gp_Pnt& theLoc,
                                                       const gp_Dir& theRayDir,
                                                       const bool    theIsHollow,
                                                       double&       theTimeEnter,
                                                       double&       theTimeLeave) const;

  Standard_EXPORT virtual bool RayCircleIntersection(const double  theRadius,
                                                     const gp_Pnt& theLoc,
                                                     const gp_Dir& theRayDir,
                                                     const bool    theIsFilled,
                                                     double&       theTime) const;

  DEFINE_STANDARD_RTTIEXT(SelectMgr_BaseIntersector, Standard_Transient)

protected:
  occ::handle<Graphic3d_Camera> myCamera;

  SelectMgr_SelectionType mySelectionType;
};
