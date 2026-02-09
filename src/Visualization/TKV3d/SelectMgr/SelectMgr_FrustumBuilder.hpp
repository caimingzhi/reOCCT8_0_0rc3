#pragma once

#include <Graphic3d_Camera.hpp>
#include <Precision.hpp>
#include <gp_Trsf.hpp>
#include <NCollection_Mat4.hpp>
#include <NCollection_Vec3.hpp>
#include <NCollection_Vec4.hpp>

class SelectMgr_FrustumBuilder : public Standard_Transient
{
public:
  Standard_EXPORT SelectMgr_FrustumBuilder();

  const occ::handle<Graphic3d_Camera>& Camera() const { return myCamera; }

  Standard_EXPORT void SetCamera(const occ::handle<Graphic3d_Camera>& theCamera);

  Standard_EXPORT void SetWindowSize(const int theWidth, const int theHeight);

  Standard_EXPORT void SetViewport(const double theX,
                                   const double theY,
                                   const double theWidth,
                                   const double theHeight);

  Standard_EXPORT void InvalidateViewport();

  Standard_EXPORT void WindowSize(int& theWidth, int& theHeight) const;

  Standard_EXPORT double SignedPlanePntDist(const NCollection_Vec3<double>& theEq,
                                            const NCollection_Vec3<double>& thePnt) const;

  Standard_EXPORT gp_Pnt ProjectPntOnViewPlane(const double& theX,
                                               const double& theY,
                                               const double& theZ) const;

  DEFINE_STANDARD_RTTIEXT(SelectMgr_FrustumBuilder, Standard_Transient)

private:
  occ::handle<Graphic3d_Camera> myCamera;
  int                           myWidth;
  int                           myHeight;
  NCollection_Vec4<double>      myViewport;
  bool                          myIsViewportSet;
};
