#pragma once


#include <Graphic3d_Camera.hpp>
#include <Precision.hpp>
#include <gp_Trsf.hpp>
#include <NCollection_Mat4.hpp>
#include <NCollection_Vec3.hpp>
#include <NCollection_Vec4.hpp>

//! The purpose of this class is to provide unified interface for building
//! selecting frustum depending on current camera projection and orientation
//! matrices, window size and viewport parameters.
class SelectMgr_FrustumBuilder : public Standard_Transient
{
public:
  //! Creates new frustum builder with empty matrices
  Standard_EXPORT SelectMgr_FrustumBuilder();

  //! Returns current camera
  const occ::handle<Graphic3d_Camera>& Camera() const { return myCamera; }

  //! Stores current camera
  Standard_EXPORT void SetCamera(const occ::handle<Graphic3d_Camera>& theCamera);

  //! Stores current window width and height
  Standard_EXPORT void SetWindowSize(const int theWidth, const int theHeight);

  //! Stores current viewport coordinates
  Standard_EXPORT void SetViewport(const double theX,
                                   const double theY,
                                   const double theWidth,
                                   const double theHeight);

  Standard_EXPORT void InvalidateViewport();

  Standard_EXPORT void WindowSize(int& theWidth, int& theHeight) const;

  //! Calculates signed distance between plane with equation
  //! theEq and point thePnt
  Standard_EXPORT double SignedPlanePntDist(const NCollection_Vec3<double>& theEq,
                                            const NCollection_Vec3<double>& thePnt) const;

  //! Projects 2d screen point onto view frustum plane:
  //! theZ = 0 - near plane,
  //! theZ = 1 - far plane
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

