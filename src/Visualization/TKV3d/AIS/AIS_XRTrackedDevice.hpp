#pragma once


#include <AIS_InteractiveObject.hpp>
#include <Aspect_XRTrackedDeviceRole.hpp>

class Graphic3d_ArrayOfTriangles;
class Image_Texture;

//! Auxiliary textured mesh presentation of tracked XR device.
class AIS_XRTrackedDevice : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_XRTrackedDevice, AIS_InteractiveObject)
public:
  //! Main constructor.
  Standard_EXPORT AIS_XRTrackedDevice(const occ::handle<Graphic3d_ArrayOfTriangles>& theTris,
                                      const occ::handle<Image_Texture>&              theTexture);

  //! Empty constructor.
  Standard_EXPORT AIS_XRTrackedDevice();

  //! Return device role.
  Aspect_XRTrackedDeviceRole Role() const { return myRole; }

  //! Set device role.
  void SetRole(Aspect_XRTrackedDeviceRole theRole) { myRole = theRole; }

  //! Return laser color.
  const Quantity_Color& LaserColor() const { return myLaserColor; }

  //! Set laser color.
  Standard_EXPORT void SetLaserColor(const Quantity_Color& theColor);

  //! Return laser length.
  float LaserLength() const { return myLaserLength; }

  //! Set laser length.
  Standard_EXPORT void SetLaserLength(float theLength);

  //! Return unit scale factor.
  float UnitFactor() const { return myUnitFactor; }

  //! Set unit scale factor.
  void SetUnitFactor(float theFactor) { myUnitFactor = theFactor; }

protected:
  //! Returns true for 0 mode.
  bool AcceptDisplayMode(const int theMode) const override { return theMode == 0; }

  //! Compute presentation.
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  //! Compute selection.
  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  //! Compute laser ray presentation.
  Standard_EXPORT void computeLaserRay();

private:
  //! Texture holder.
  class XRTexture;

private:
  occ::handle<Graphic3d_Group> myRayGroup;

  occ::handle<Graphic3d_ArrayOfTriangles> myTris;
  Quantity_Color                          myLaserColor;
  float                                   myLaserLength;
  float                                   myUnitFactor;
  Aspect_XRTrackedDeviceRole              myRole;
  bool                                    myToShowAxes;
};

